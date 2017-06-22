#ifndef OBJECT_H
#define OBJECT_H

#include "common/intersection.h"
#include "object/material.h"

class Plane;
class Sphere;
class Cylinder;
class RotationBody;

class Object
{
public:
    virtual ~Object();

    ID getIdentifier() const { return _identifier; }
    const Material* getMaterial() const { return _material; }

    virtual std::string getType() const = 0;

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const = 0;

    // 交点处的纹理颜色
    virtual Color getTextureColor(const Intersection& coll) const = 0;

    // 保存为 JSON 格式
    virtual Json::Value toJson() const;

    // 保存 JSON 到文件
    virtual void save(const std::string& file) const;

    // 从 JSON 导入物体
    static Object* loadFromJson(const Json::Value& value);

    // 从文件导入物体
    static Object* loadFrom(const std::string& file);

protected:
    Object(const Material* m);
    Object(const Json::Value& object);

    const Material* _material;
    ID _identifier; // 标识符

private:
    bool _can_delete_material;
};

#endif // OBJECT_H
