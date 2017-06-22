#include "utils/config.h"
#include "common/const.h"
#include "engine/raytracer/raytracer.h"
#include "env/camera.h"

#include <algorithm>
#include <ctime>
#include <omp.h>

RayTracer::RayTracer(Scene* scene)
    : Engine(scene){
    if (scene)
    {
        _hash = new ID*[_w];
        _is_edge = new bool*[_w];
        for (int i = 0; i < _w; i++)
        {
            _hash[i] = new ID[_h];
            _is_edge[i] = new bool[_h];
        }
    }
}

RayTracer::~RayTracer(){
    if (!_scene)return;
    for (int i = 0; i < _w; i++) delete[] _hash[i];
    delete[] _hash;
}

void RayTracer::run(const std::string& outFile){
    if (!_scene) return;

    printf("RayTracing Start...\n");
    clock_t last = clock();
    int i,j;
    int tot=0;
    omp_lock_t lock;
    omp_init_lock(&lock);
    int PixelTot = _w*_h;
#ifdef MULTITHREAD
        #pragma omp parallel for num_threads(Config::thread_max_number)
#endif
    for (i = 0; i < PixelTot; i++){
        //printf("Row %d | %d\n",i,Config::thread_max_number);
        int x = i / _h;
        int y = i % _h;

        omp_set_lock(&lock);
        tot++;
        omp_unset_lock(&lock);
        _hash[x][y] = 0;
        Color c = _DOFTracing(x, y);
        _camera->setColor(x, y, c);
        /*
        if (Config::snapshot_interval > 0 &&
            clock() - last > Config::snapshot_interval * CLOCKS_PER_SEC){
            last = clock();
            _camera->print(outFile.c_str());
        }*/
    }
    printf("%d\n",tot);
    _camera->print(outFile.c_str());

}

Color RayTracer::_DOFTracing(double ox, double oy, double f) const
{
    if (!_camera->isDOF()){
        Ray r = _camera->emit(ox, oy);
        return _rayTracing(r, ox, oy, Color(1, 1, 1) * f, 1, 1, false);
    }

    Color color;
    for (int i = 0; i < Config::dof; i++)
        color += _rayTracing(_camera->dofEmit(ox, oy), ox, oy, Color(1, 1, 1) * f / Config::dof, 1, 1, false);
    return color;
}

Color RayTracer::_localIllumination(const Intersection& coll, const Material* material, const Color& factor) const
{
    Color color = material->color * coll.getObject()->getTextureColor(coll);
    Color ret = color * _scene->getAmbientLightColor() * material->diff; // 环境光
    for (auto light = _scene->lightsBegin(); light != _scene->lightsEnd(); light++)
    {
        Vector3 l = ((*light)->getSource() - coll.p).normalize();
        if (l.dot(coll.n) < Const::EPS) continue;

        double shade = (*light)->getShadowRatio(_scene, coll.p);
        if (shade > Const::EPS)
            ret += color * (*light)->getColor() * material->BRDF(l, coll.n, coll.ray.dir) * shade;
    }
    return ret * factor;
}

Color RayTracer::_rayTracing(const Ray& ray, int fx, int fy,
    const Color& factor, double weight, int depth, bool isInternal) const
{
    if (weight < Config::raytracing_min_weight || depth > Config::raytracing_max_depth)
        return Color();

    Intersection coll = _scene->findNearestIntersection(ray);
    if (!coll.isHit())
        return _scene->getAmbientLightColor() * factor;
    else if (coll.atLight())
    {
        (_hash[fx][fy] *= Const::HASH_KEY) += coll.getID();
        return coll.light->getColor() * factor;
    }
    else
    {
        Color ret, absorb(1, 1, 1);
        const Object* obj = coll.getObject();
        const Material* material = obj->getMaterial();
        (_hash[fx][fy] *= Const::HASH_KEY) += coll.getID();

        // 透明材质的颜色过滤
        if (isInternal) absorb = (material->absorb_color * -coll.dist).exp();

        if (material->diff > Const::EPS || material->spec > Const::EPS)
            ret += _localIllumination(coll, material, factor * absorb);
        if (material->refl > Const::EPS || material->refr > Const::EPS)
        {
            double n = material->rindex;
            if (isInternal) n = 1 / n;
            Vector3 refl = coll.ray.dir.reflect(coll.n);
            Vector3 refr = coll.ray.dir.refract(coll.n, n);
            if (material->refr < Const::EPS) // 全镜面反射
                ret += _rayTracing(Ray(coll.p, refl), fx, fy,
                                    factor * absorb * (material->color * material->refl), weight * material->refl,
                                    depth + 1, isInternal);
            else if (refr.mod2() < Const::EPS) // 全反射
            {
                double k = material->refl + material->refr;
                ret += _rayTracing(Ray(coll.p, refl), fx, fy,
                                    factor * absorb * (material->color * k), weight * k,
                                    depth + 1, isInternal);
            }
            else if (material->refl < Const::EPS) // 全透射
                ret += _rayTracing(Ray(coll.p, refr), fx, fy,
                                    factor * absorb * material->refr, weight * material->refr,
                                    depth + 1, !isInternal);
            else
            {
                double kl = material->refl, kr = material->refr;
                if (Config::enable_fresnel) // Fresnel equations
                {
                    double cosI = -coll.ray.dir.dot(coll.n), cosT = sqrt(1 - (1 - cosI * cosI) / n / n);
                    double r1 = (cosI * n - cosT) / (cosI * n + cosT),
                           r2 = (cosI - cosT * n) / (cosI + cosT * n);
                    kl = (r1 * r1 + r2 * r2) / 2, kr = 1 - kl;
                }

                if (kl > Const::EPS) ret += _rayTracing(Ray(coll.p, refl), fx, fy,
                                                         factor * absorb * (material->color * kl), weight * kl,
                                                         depth + 1, isInternal);
                if (kr > Const::EPS) ret += _rayTracing(Ray(coll.p, refr), fx, fy,
                                                         factor * absorb * kr, weight * kr,
                                                         depth + 1, !isInternal);
            }
        }

        return ret;
    }
}
