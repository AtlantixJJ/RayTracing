#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "math/vector3.h"
#include "light/light.h"

class PointLight : public Light
{
public:
    PointLight(const Color& c, const Vector3& o, double power = 1)
        : Light(c, power), _o(o) {}
    PointLight(const Json::Value& light)
        : Light(light), _o(light["o"]) {}

    // 发光点
    virtual Vector3 getSource() const override { return _o; }

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const override;

    // 计算阴影比例
    virtual double getShadowRatio(const Scene* scene, const Vector3& p) const override;

    // 发射光子
    virtual Photon emitPhoton(double power) const override;

    virtual Json::Value toJson() const override;

private:
    Vector3 _o;
};

#endif // POINTLIGHT_H
