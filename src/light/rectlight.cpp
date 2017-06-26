#include "utils/config.h"
#include "common/const.h"
#include "light/rectlight.h"
#include "object/object.h"
#include "env/scene.h"

Intersection RectLight::collide(const Ray& ray) const
{
    Vector3 n = _dx * _dy;
    double d = n.dot(ray.dir);
    if (abs(d) < Const::EPS) return Intersection();
    double t = (n.dot(_o) - n.dot(ray.start)) / d;
    if (t < Const::EPS) return Intersection();
    Vector3 p = ray.get(t) - _o;
    if (abs(p.dot(_dx)) + Const::EPS < _dx.mod2() && abs(p.dot(_dy)) + Const::EPS < _dy.mod2())
        return Intersection(ray, t, this);
    else
        return Intersection();
}

double RectLight::getShadowRatio(const Scene* scene, const Vector3& p) const
{
    int samples = Config::soft_shadow_samples, ret = samples * samples;
    for (int i = 0; i < samples; i++)
        for (int j = 0; j < samples; j++)
        {
            double x = (i + 0.5) * 2 / samples - 1,
                   y = (j + 0.5) * 2 / samples - 1;
                   
            Vector3 c = _o + _dx * x + _dy * y, dir = c - p;
            double dist = dir.mod();

            for (auto o = scene->objectsBegin(); o != scene->objectsEnd(); o++)
            {
                Intersection coll = (*o)->collide(Ray(p, dir));
                if (coll.isHit() && coll.dist + Const::EPS < dist)
                {
                    ret--;
                    break;
                }
            }
        }
    return 1.0 * ret / samples / samples;
}

Photon RectLight::emitPhoton(double power) const
{
    return Photon(_o + _dx * (2 * randDouble - 1) + _dy * (2 * randDouble - 1),
                  _n.diffuse(), _color * power);
}

Json::Value RectLight::toJson() const
{
    Json::Value light = Light::toJson();
    light["type"] = "RectLight";
    light["o"] = _o.toJson();
    light["n"] = _n.toJson();
    light["dx"] = _dx.toJson();
    light["dy"] = _dy.toJson();
    return light;
}
