#ifndef PP_H
#define PP_H

#include "engine/raytracer/raytracer.h"

class HitPointMap;

class PPM : public RayTracer
{
public:
    PPM(Scene* scene)
        : RayTracer(scene) {}
    virtual ~PPM() {}

    virtual void run(const std::string& outFile) override;

private:
    HitPointMap* _map;
    bool _find_edge;

    virtual Color _localIllumination(const Intersection& coll, const Material* Material, const Color& factor) const override;
};

#endif // PP_H
