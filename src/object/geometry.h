#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "math/vector3.h"
#include "object/object.h"

class Cylinder;
class Sphere;
class Plane;

class Cylinder : public Object
{
public:
    Cylinder(const Vector3& o, double r, double h, const Material* m = nullptr);
    Cylinder(const Json::Value& object);

    virtual std::string getType() const override { return "Cylinder"; }

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const override;

    // 交点处的纹理颜色
    virtual Color getTextureColor(const Intersection& coll) const override;

    virtual Json::Value toJson() const override;

    // 设置纹理起点极角
    void setTextureArg(double a) { _arg = a; }

private:
    Vector3 _o;            // 底面圆心
    double _r, _h, _arg; // 底面半径，高，纹理起点极角
};

class Plane : public Object
{
public:
    Plane(const Vector3& n, double d, const Material* m = nullptr);
    Plane(const Json::Value& object);

    virtual std::string getType() const override { return "Plane"; }

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const override;

    // 交点处的纹理颜色
    virtual Color getTextureColor(const Intersection& coll) const override;

    virtual Json::Value toJson() const override;

    // 设置纹理坐标轴
    void setTextureAxis(const Vector3& o, const Vector3& dx, const Vector3& dy) { _o = o, _dx = dx, _dy = dy; }

private:
    Vector3 _n;             // 法向量
    double _d;              // 直线方程为 n * P + d = 0
    Vector3 _o, _dx, _dy; // 纹理原点和坐标轴向量
};

class Sphere : public Object
{
public:
    Sphere(const Vector3& o, double r, const Material* m = nullptr);
    Sphere(const Json::Value& object);

    virtual std::string getType() const override { return "Sphere"; }

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const override;

    // 交点处的纹理颜色
    virtual Color getTextureColor(const Intersection& coll) const override;

    virtual Json::Value toJson() const override;

    // 设置纹理坐标轴
    void setTextureAxis(const Vector3& dz, const Vector3& dx) { _dz = dz, _dx = dx; }

private:
    Vector3 _o;        // 球心
    double _r;         // 半径
    Vector3 _dz, _dx; // 北极向量和 0 度经线方向
};


#endif