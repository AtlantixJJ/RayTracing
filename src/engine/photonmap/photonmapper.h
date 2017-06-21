#ifndef PHOTONMAPPER_H
#define PHOTONMAPPER_H

#include "common/color.h"
#include "common/vector3.h"
#include "engine/engine.h"
#include "engine/photonmap/photontracer.h"
class Collision;
class Material;
class Scene;

class PhotonMapper : public Engine
{
public:
    PhotonMapper(Scene * scene) : Engine(scene) {}
    virtual ~PhotonMapper() {}

    virtual void run(const std::string& outFile) override;

};

#endif // RAYTRACER_H