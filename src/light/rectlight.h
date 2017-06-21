#ifndef RECTLIGHT_H
#define RECTLIGHT_H

#include "common/vector3.h"
#include "light/light.h"

class RectLight : public Light
{
public:
    RectLight(const Color& c, const Vector3& o, const Vector3& n, const Vector3& dx, const Vector3& dy)
        : Light(c), n(n), o(o), dx(dx), dy(dy) {}
    RectLight(const Json::Value& light)
        : Light(light), o(light["o"]), dx(light["dx"]), dy(light["dy"]) {}

    // 发光点
    virtual Vector3 getSource() const override { return o; }

    // 与视线相交
    virtual void collide(Collision* coll, const Vector3& start, 
        const Vector3& dir) override;

    virtual Photon emitPhoton(double power) const;

    // 计算阴影比例
    virtual double getShadowRatio(const Scene* scene, const Vector3& p) const override;

    virtual Json::Value toJson() const override;

private:
    Vector3 o, n;        // 矩形中心点
    Vector3 dx, dy; // 横向、纵向向量
};

#endif // RECTLIGHT_H
