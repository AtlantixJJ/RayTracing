#ifndef RECTLIGHT_H
#define RECTLIGHT_H

#include "math/vector3.h"
#include "light/light.h"

class RectLight : public Light
{
public:
    RectLight(const Color& c, const Vector3& o, const Vector3& n, const Vector3& dx, const Vector3& dy, double power = 1)
        : Light(c, power), _o(o), _n(n), _dx(dx), _dy(dy) {}
    RectLight(const Json::Value& light)
        : Light(light), _o(light["o"]), _n(light["n"]), _dx(light["dx"]), _dy(light["dy"]) {}

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
    Vector3 _o, _n;   // 矩形中心点、光源朝向
    Vector3 _dx, _dy; // 横向、纵向向量
};

#endif // RECTLIGHT_H
