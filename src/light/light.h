#ifndef LIGHT_H
#define LIGHT_H

#include "common/common.h"
#include "common/common.h"
#include "common/intersection.h"

class Scene;
class PointLight;

class Light
{
public:
    Light(const Color& c, double power = 1)
        : _color(c), _power(power), _id(randID) {}
    Light(const Json::Value& light)
        : _color(light["color"]), _power(light["power"].asDouble()), _id(randID) {}
    virtual ~Light() {}

    ID getIdentifier() const { return _id; }
    Color getColor() const { return _color; }
    double getPower() const { return _power; }

    // 发光点
    virtual Vector3 getSource() const = 0;

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const = 0;

    // 计算阴影比例，值越小阴影越深
    virtual double getShadowRatio(const Scene* scene, const Vector3& p) const = 0;

    // 发射光子
    virtual Photon emitPhoton(double power) const = 0;

    // 保存为 JSON 格式
    virtual Json::Value toJson() const;

    // 从 JSON 导入物体
    static Light* fromJson(const Json::Value& value);

protected:
    Color _color;       // 光色
    double _power;      // 光能
    ID _id; // 标识符
};

#endif // LIGHT_H
