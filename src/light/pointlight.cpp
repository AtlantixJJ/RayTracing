#include "common/const.h"
#include "light/pointlight.h"
#include "object/object.h"
#include "env/scene.h"

Intersection PointLight::collide(const Ray& ray) const
{
    return Intersection(); 
}

double PointLight::getShadowRatio(const Scene* scene, const Vector3& p) const
{
    Vector3 dir = _o - p;
    double dist = dir.mod();
    for (auto o = scene->objectsBegin(); o != scene->objectsEnd(); o++)
    {
        Intersection coll = (*o)->collide(Ray(p, dir));
        if (coll.isHit() && coll.dist + Const::EPS < dist) return 0;
    }
    return 1;
}

Photon PointLight::emitPhoton(double power) const
{
    return Photon(_o, Vector3::randVector(), _color * power);
}

Json::Value PointLight::toJson() const
{
    Json::Value light = Light::toJson();
    light["type"] = "PointLight";
    light["o"] = _o.toJson();
    return light;
}
