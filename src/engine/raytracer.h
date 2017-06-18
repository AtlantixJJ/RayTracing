#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "common/color.h"
#include "common/vector3.h"

class Collision;
class Material;
class Scene;

class RayTracer
{
public:
    RayTracer() {}
    ~RayTracer() {}

    void run(Scene* scene, const std::string& outFile);

private:
    Scene* m_scene;

    Color calcLocalIllumination(const Collision& coll, const Material* Material) const;
    Color calcReflection(const Collision& coll, const Material* Material, double weight, int depth, bool isInternal) const;
    Color calcRefraction(const Collision& coll, const Material* Material, double weight, int depth, bool isInternal) const;
    Color rayTracing(const Vector3& start, const Vector3& dir, double weight, int depth, bool isInternal) const;
};

#endif // RAYTRACER_H
