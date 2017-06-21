#include "common/const.h"
#include "light/rectlight.h"
#include "object/object.h"
#include "scene/scene.h"

const int SHADOW_SAMPLE = 4;

void RectLight::collide(Collision* coll, const Vector3& start, const Vector3& dir)
{
    Vector3 n = dx * dy;
    double d = n.dot(dir);
    if (abs(d) < Const::EPS){
        coll->collide();
        return;
    }
    double t = (n.dot(o) - n.dot(start)) / d;
    if (t < Const::EPS){
        coll->collide();
        return;
    }

    Vector3 p = start + dir * t - o;
    if (abs(p.dot(dx)) + Const::EPS < dx.mod2() && abs(p.dot(dy)) + Const::EPS < dy.mod2())
        coll->collide(start, dir, t, this);
    else
        coll->collide();
}

double RectLight::getShadowRatio(const Scene* scene, const Vector3& p) const
{
    int ret = SHADOW_SAMPLE * SHADOW_SAMPLE;
    Collision coll;
    for (int i = 0; i < SHADOW_SAMPLE; i++)
        for (int j = 0; j < SHADOW_SAMPLE; j++)
        {
            double x = (i + 0.5) * 2 / SHADOW_SAMPLE - 1,
                   y = (j + 0.5) * 2 / SHADOW_SAMPLE - 1;
            Vector3 c = o + dx * x + dy * y, dir = c - p;
            double dist = dir.mod();

            for (auto o = scene->objectsBegin(); o != scene->objectsEnd(); o++)
            {
                (*o)->collide(&coll, p, dir);
                if (coll.isHit() && coll.dist + Const::EPS < dist)
                {
                    ret--;
                    break;
                }
            }
        }
    return 1.0 * ret / SHADOW_SAMPLE / SHADOW_SAMPLE;
}

Json::Value RectLight::toJson() const
{
    Json::Value light = Light::toJson();
    light["type"] = "RectLight";
    light["o"] = o.toJson();
    light["dx"] = dx.toJson();
    light["dy"] = dy.toJson();
    return light;
}

Photon RectLight::emitPhoton(double power) const
{
    return Photon(o + dx * (2 * Const::randDouble() - 1) + dy * (2 * Const::randDouble() - 1),
                  n.diffuse(), m_color * (power / m_color.power()));
}