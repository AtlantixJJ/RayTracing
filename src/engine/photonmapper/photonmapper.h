#ifndef PHOTONMAPPER_H
#define PHOTONMAPPER_H

#include "engine/raytracer/raytracer.h"

class PhotonMap;
class PhotonTracer;

class PhotonMapper : public RayTracer
{
public:
    PhotonMapper(Scene* scene)
        : RayTracer(scene) {}
    virtual ~PhotonMapper() {}

    virtual void run(const std::string& outFile) override;

private:
    PhotonMap* _map;

    virtual Color _localIllumination(const Intersection& coll, 
        const Material* Material, const Color& factor,
        int fx=-1, int fy=-1) const override;
};

#endif // PHOTONMAPPER_H
