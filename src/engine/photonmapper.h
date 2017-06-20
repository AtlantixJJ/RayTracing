#ifndef PHOTONMAPPER_H
#define PHOTONMAPPER_H

#include "common/color.h"
#include "common/vector3.h"

class Collision;
class Material;
class Scene;

class PhotonMapper
{
public:
    PhotonMapper() {}
    ~PhotonMapper() {}

    void run(Scene* scene, const std::string& outFile);

private:
    Scene* m_scene;
};

#endif // RAYTRACER_H