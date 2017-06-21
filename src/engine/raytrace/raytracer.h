#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "common/color.h"
#include "common/vector3.h"
#include "engine/engine.h"

class Collision;
class Material;
class Scene;

class RayTracer : public Engine
{
public:
    RayTracer(Scene *scene):Engine(scene) {}
    ~RayTracer() {}

    virtual void run(const std::string& outFile);

protected:
    
    Color calcLocalIllumination(const Collision& coll, const Material* Material) const;
    Color calcReflection(const Collision& coll, const Material* Material, double weight, int depth, bool isInternal) const;
    Color calcRefraction(const Collision& coll, const Material* Material, double weight, int depth, bool isInternal) const;
    Color rayTracing(const Vector3& start, const Vector3& dir, double weight, int depth, bool isInternal) const;
};

#endif // RAYTRACER_H
