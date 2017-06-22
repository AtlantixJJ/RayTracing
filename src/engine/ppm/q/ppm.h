#ifndef PPM_H
#define PPM_H

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
    HitPointMap* m_map;
    bool _find_edge;

    virtual Color _localIllumination(const Collision& coll, const Material* Material, const Color& factor) const override;
};

#endif // PPM_H
