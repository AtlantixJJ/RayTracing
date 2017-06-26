#include "utils/config.h"
#include "common/const.h"
#include "engine/photonmapper/photontracer.h"
#include "engine/ppm/hitpointmap.h"
#include "engine/ppm/ppm.h"
#include "env/camera.h"

void PPM::run(const std::string& outFile)
{
    if (!_scene) return;
    _map = new HitPointMap();

    int i,j,x,y,tot;
    // Multithread here seems to induce bugs
#ifdef MULTITHREAD
    //#pragma omp parallel for num_threads(Config::thread_max_number)
#endif
    for (i = 0; i < _w * _h; i++){
            x = i / _h;
            y = i % _h;
            _camera->setColor(x, y, _DOFTracing(x, y));
        }
    printf("RayTracing Done\n");

    _map->buildKDTree();
    Bmp* f = _camera->copyf();

    printf("PPM Iteration Start...\n");
    PhotonTracer* tracer = new PhotonTracer(_scene, _map);
    for (i = 0, tot = 0; i < Config::ppm_iteration_depth; i++)
    {
        printf("Round [%d]\n", i);
        tracer->emitPhotons(Config::ppm_photo_number);
        _map->update();
        tot += Config::ppm_photo_number;

        _camera->setf(f);
        for (auto p = _map->hitPointBegin(); p != _map->hitPointEnd(); p++)
        {
            if(DEBUG >= 1 && randDouble<0.001)std::cout<<"flux "<<p->flux<<std::endl;
            
            Color color = _camera->getColor(p->x, p->y) + p->color * p->flux * (1 / Const::PI / p->r2 / tot);
            
            _camera->setColor(p->x, p->y, color);
        }

        _camera->print(outFile.c_str());
    }

    delete f;
    delete tracer;
    delete _map;
}


Color PPM::_localIllumination(const Intersection& coll,
     const Material* material, const Color& factor,
     int fx, int fy) const
{
    HitPoint point;

    point.material = material;
    point.pos = coll.p;
    point.n = coll.n;
    point.dir = coll.ray.dir;
    point.color = material->color * 
        coll.getObject()->getTextureColor(coll) * factor * material->diff;
    point.r2 = Config::ppm_search_rad; // default
    point.x = fx; point.y = fy;

    //printf("%d %d\n",point.x,point.y);
    _map->addHitPoint(point);

    if (Config::photon_map_only)
        return Color();
    else
        return RayTracer::_localIllumination(coll, material, factor, fx, fy);
}
