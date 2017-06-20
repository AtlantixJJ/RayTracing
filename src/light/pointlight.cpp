#include "common/const.h"
#include "light/pointlight.h"
#include "object/object.h"
#include "scene/scene.h"

void PointLight::collide(Collision* coll, const Vector3& start, const Vector3& dir)
{
    coll->collide(); // 点光源永远不会与视线相交
}

double PointLight::getShadowRatio(const Scene* scene, const Vector3& p) const
{
    Vector3 dir = m_o - p;
    double dist = dir.mod();
    Collision coll;
    for (auto o = scene->objectsBegin(); o != scene->objectsEnd(); o++)
    {
        (*o)->collide(&coll, p, dir); // object collision need to pass pointer
        if (coll.isHit() && coll.dist + Const::EPS < dist) return 0;
    }
    return 1;
}

Json::Value PointLight::toJson() const
{
    Json::Value light = Light::toJson();
    light["type"] = "PointLight";
    light["o"] = m_o.toJson();
    return light;
}
