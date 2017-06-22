#include "utils/config.h"
#include "common/const.h"
#include "engine/photonmapper/photonmap.h"
#include "engine/photonmapper/photontracer.h"
#include "engine/ppm/hitpointmap.h"
#include "light/light.h"
#include "object/material.h"
#include "object/object.h"
#include "env/scene.h"

#include <mutex>
#include <thread>
/*
void PhotonTracer::emitPhotons(int photonNumber)
{
    double totPower = 0;
    for (auto l = _scene->lightsBegin(); l != _scene->lightsEnd(); l++)
        totPower += (*l)->getPower();
    printf("Power %lf\n",power);
    mutex lock;
    int tot = 0, threads = Config::thread_max_number;
    std::vector<std::thread> threadPool;
    if (_photon_map) threads = 1;
    for (int i = 0; i < threads; i++)
    {
        double deltaPower = totPower / (photonNumber / threads);
        threadPool.push_back(std::thread([this, totPower, deltaPower, &tot, &lock]() {
            for (auto l = _scene->lightsBegin(); l != _scene->lightsEnd(); l++)
            {
                double lightPower = (*l)->getPower();
                for (; lightPower > 0; lightPower -= deltaPower)
                {
                    Photon photon = (*l)->emitPhoton(totPower);
                    _photonTracing(photon, 1, false);

                    lock.lock();
                    if (++tot % 1000 == 0) cout << "Emitted " << tot << " photons." << endl;
                    lock.unlock();
                }
            }
        }));
    }

    for (int i = 0; i < threads; i++) threadPool[i].join();
}
*/

void PhotonTracer::emitPhotons(int photonNumber)
{
    double power = 0, lp = 0;
    int tot = 0;
    Photon ph;

    for( auto l = _scene->lightsBegin(); l != _scene -> lightsEnd(); l++)
    {
        //printf("%d\n",*l);
        power += (*l)->getPower();
    }
    //printf("%d\n",gconf);   
    int i;
    printf("power:%lf",power);


    for( i = 0 ; i < _scene->getLightSourceNum() ; i++)
    {
        //printf("L");
        Light *l = _scene->getLightbyInd(i);
        lp = l->getPower();
        int iter_time = lp * photonNumber / power;
        #pragma omp parallel for num_threads(Config::thread_max_number)
        for (int j = 0 ; j < iter_time ;j ++)
        {
            //printf("E%.10f",lp);
            ph = l->emitPhoton(power);
            //printf("%lf\n",ph.pow.power());
            //printf("P(%d)[%d]",omp_get_thread_num(),j);
            _photonTracing(ph, 1, false);
            //printf("D(%d)[%d]\n",omp_get_thread_num(),j);

            //sleep(1);
            omp_set_lock(&lock);
            //printf("tot%d\n",tot);
            if (++tot % 1000 == 0) printf( "Emitted %d photons.\n",tot);
            omp_unset_lock(&lock);
            //sleep(1);
            
        }
    }
}


void PhotonTracer::_photonTracing(Photon& photon, int depth, bool isInternal)
{
    if (depth > Config::phtrace_max_depth) return;
    //cout<<photon;
    Intersection coll = _scene->findNearestIntersection(Ray(photon.pos, photon.dir));
    if (coll.isHit() && coll.atObject())
    {
        photon.pos = coll.p;
        const Object* obj = coll.getObject();
        const Material* material = obj->getMaterial();
        if (material->diff > Const::EPS)
        {
            omp_set_lock(&lock2);
            if (_photon_map) _photon_map->addPhoton(photon);
            if (_hit_point_map) _hit_point_map->incomingPhoton(photon);
            omp_unset_lock(&lock2);
        }

        Color cd = material->color * obj->getTextureColor(coll), ct(1, 1, 1);
        if (isInternal) // 透明材质的颜色过滤
        {
            Color absorb = (material->absorb_color * -coll.dist).exp();
            cd *= absorb, ct *= absorb;
        }
        double fortune = randDouble;
        double pd = (material->diff + material->spec) * cd.power(), // 漫反射概率
            ps = material->refl * cd.power(),                       // 镜面反射概率
            pt = material->refr * ct.power();                       // 透射概率

        if (fortune < pd) // 漫反射
        {
            photon.dir = coll.n.diffuse();
            photon.pow *= cd / cd.power();
            _photonTracing(photon, depth + 1, isInternal);
        }
        else if (fortune < pd + ps) // 镜面反射
        {
            photon.dir = coll.ray.dir.reflect(coll.n);
            photon.pow *= cd / cd.power();
            _photonTracing(photon, depth + 1, isInternal);
        }
        else if (fortune < pd + ps + pt) // 透射
        {
            double n = material->rindex;
            if (isInternal) n = 1 / n;
            photon.dir = coll.ray.dir.refract(coll.n, n);
            photon.pow *= ct / ct.power();
            _photonTracing(photon, depth + 1, !isInternal);
        }
    }
}
