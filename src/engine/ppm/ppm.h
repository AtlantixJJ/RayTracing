#ifndef PPM_H
#define PPM_H

#include "engine/raytracer/raytracer.h"
#include "omp.h"
class HitPointMap;

class PPM : public RayTracer
{
public:
    PPM(Scene* scene)
        : RayTracer(scene) {
            isbase=true;
            //omp_init_lock(&lockp);
        }
    virtual ~PPM() {
        //omp_destroy_lock(&lockp);
    }

    virtual void run(const std::string& outFile) override;

private:
    HitPointMap* _map;
    

    virtual Color _localIllumination(const Intersection& coll,
     const Material* Material, const Color& factor,
     int fx, int fy) const override;
};

#endif // PP_H
