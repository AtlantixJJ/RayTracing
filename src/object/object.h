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

    ID getIdentifier() const { return _id; }
    const Material* getMaterial() const { return _material; }

    virtual std::string getType() const = 0;

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const = 0;

    // 交点处的纹理颜色
    virtual Color getTextureColor(const Intersection& coll) const = 0;

    // 保存为 JSON 格式
    virtual Json::Value toJson() const;

    virtual void save2Json(const std::string& file) const;

    static Object* fromJson(const Json::Value& value);
    static Object* loadFile(const std::string& file);

protected:
    Object(const Material* m);
    Object(const Json::Value& object);

    const Material* _material;
    ID _id; // 标识符

private:
    bool _can_delete_material;
};

#endif // OBJECT_H
