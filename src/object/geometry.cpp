#include "object/geometry.h"

///////////////////////////////////
/////////    Cylinder    //////////
///////////////////////////////////
Cylinder::Cylinder(const Vector3& o, double r, double h, const Material* m)
    : Object(m), _o(o), _r(r), _h(h),
      _arg(0)
{
}

Cylinder::Cylinder(const Json::Value& object)
    : Object(object), _o(object["o"]), _r(object["r"].asDouble()), _h(object["h"].asDouble()),
      _arg(fmod(object["texture_arg"].asDouble() / 180 * Const::PI, 2 * Const::PI))
{
}

Intersection Cylinder::collide(const Ray& ray) const
{
    Ray uray = ray.normalize();
    Vector3 d3 = uray.dir;
    Point2D d2(d3.x, d3.y), oc = Point2D(_o.x - ray.start.x, _o.y - ray.start.y);
    double t = -1;
    bool in = _o.z < ray.start.z + Const::EPS && ray.start.z < _o.z + _h + Const::EPS && oc.mod2() < _r * _r + Const::EPS;

    // 与两个底面求交
    if (abs(d3.z) > -Const::EPS)
    {
        double t1 = (_o.z - ray.start.z) / d3.z, t2 = (_o.z + _h - ray.start.z) / d3.z, u1 = 0, u2 = 1;
        if (t1 > t2) swap(t1, t2), swap(u1, u2);
        if (t1 > Const::EPS) // 若射线和第一个底面相交，直接返回
        {
            Vector3 p = uray.get(t1);
            Point2D q = (p - _o).toPoint2D();
            if (q.mod2() < _r * _r + Const::EPS)
                return Intersection(uray, t1, u1, q.arg(), Vector3(0, 0, -d3.z), this, in);
        }
        else if (t2 > Const::EPS) // 若射线和第二个底面相交，且射线起点在圆柱体内，也直接返回
        {
            Vector3 p = uray.get(t2);
            Point2D q = (p - _o).toPoint2D();
            if (q.mod2() < _r * _r + Const::EPS && in)
                return Intersection(uray, t2, u2, q.arg(), Vector3(0, 0, -d3.z), this, in);
        }
        else
            return Intersection();
    }
    if (d2.mod2() < Const::EPS && t < 0) return Intersection();
    double tca = oc.dot(d2.normalize()), thc2 = _r * _r - oc.mod2() + tca * tca;
    if (thc2 >= 0)
    {
        double thc = sqrt(thc2), t1 = tca - thc, t2 = tca + thc;
        if (t1 > Const::EPS)
            t = t1;
        else
            t = t2;
    }
    if (t > Const::EPS)
    {
        t /= d2.mod();
        Vector3 p = uray.get(t);
        if (_o.z < p.z + Const::EPS && p.z < _o.z + _h + Const::EPS)
            return Intersection(uray, t, (p.z - _o.z) / _h, (p - _o).toPoint2D().arg(),
                             Vector3(p.x - _o.x, p.y - _o.y, 0) * (in ? -1 : 1), this, in);
    }
    return Intersection();
}

Color Cylinder::getTextureColor(const Intersection& coll) const
{
    if (_material->hasTexture())
    {
        double u = fmod(coll.v - _arg + 4 * Const::PI, 2 * Const::PI) / 2 / Const::PI,
               v = 1 - coll.u;
        return _material->getTextureColor(u, v);
    }
    else
        return Color(1, 1, 1);
}

Json::Value Cylinder::toJson() const
{
    Json::Value object = Object::toJson();
    object["type"] = "Cylinder";
    object["o"] = _o.toJson();
    object["r"] = _r;
    object["h"] = _h;
    if (_material->hasTexture()) object["texture_arg"] = _arg * 180 / Const::PI;
    return object;
}

///////////////////////////////////
/////////      Plane     //////////
///////////////////////////////////

Plane::Plane(const Vector3& n, double d, const Material* m)
    : Object(m), _n(n.normalize()), _d(d),
      _o(0, 0, 0), _dx(n.getAnVerticalVector()), _dy((n * _dx).normalize())
{
}

Plane::Plane(const Json::Value& object)
    : Object(object), _n(object["n"]), _d(object["d"].asDouble()),
      _o(object["texture_o"]), _dx(object["texture_dx"]), _dy(object["texture_dy"])
{
}

Intersection Plane::collide(const Ray& ray) const
{
    double n = _n.dot(ray.start) + _d, d = _n.dot(ray.dir);
    if (abs(d) < Const::EPS) return Intersection();
    double t = -n / d;
    if (t < Const::EPS) return Intersection();
    if (n > Const::EPS)
        return Intersection(ray, t, _n, this);
    else
        return Intersection(ray, t, -_n, this);
}

Color Plane::getTextureColor(const Intersection& coll) const
{
    if (_material->hasTexture())
    {
        double u = (coll.p - _o).dot(_dx) / _dx.mod2(),
               v = (coll.p - _o).dot(_dy) / _dy.mod2();
        u -= floor(u), v -= floor(v);
        return _material->getTextureColor(u, v);
    }
    else
        return Color(1, 1, 1);
}

Json::Value Plane::toJson() const
{
    Json::Value object = Object::toJson();
    object["type"] = "Plane";
    object["n"] = _n.toJson();
    object["d"] = _d;
    if (_material->hasTexture())
    {
        object["texture_o"] = _o.toJson();
        object["texture_dx"] = _dx.toJson();
        object["texture_dy"] = _dy.toJson();
    }
    return object;
}

///////////////////////////////////
/////////      Sphere     /////////
///////////////////////////////////

Sphere::Sphere(const Vector3& o, double r, const Material* m)
    : Object(m), _o(o), _r(r),
      _dz(0, 0, 1), _dx(1, 0, 0)
{
}

Sphere::Sphere(const Json::Value& object)
    : Object(object), _o(object["o"]), _r(object["r"].asDouble()),
      _dz(object["texture_dz"]), _dx(object["texture_dx"])
{
}

Intersection Sphere::collide(const Ray& ray) const
{
    Ray uray = ray.normalize();
    Vector3 oc = _o - ray.start;
    double tca = oc.dot(uray.dir), thc2 = _r * _r - oc.mod2() + tca * tca;
    if (thc2 >= 0)
    {
        double thc = sqrt(thc2), t1 = tca - thc, t2 = tca + thc;
        if (t1 > Const::EPS)
        {
            Vector3 p = uray.get(t1);
            return Intersection(uray, t1, p - _o, this, false);
        }
        else if (t2 > Const::EPS)
        {
            Vector3 p = uray.get(t2);
            return Intersection(uray, t2, _o - p, this, true);
        }
    }

    return Intersection();
}

Color Sphere::getTextureColor(const Intersection& coll) const
{
    if (_material->hasTexture())
    {
        double b = acos(coll.n.dot(_dz)), a = acos(std::min(std::max(coll.n.dot(_dx) / sin(b), -1.0), 1.0));
        double v = b / Const::PI, u = a / 2 / Const::PI;
        if (coll.n.dot(_dz * _dx) < 0) u = 1 - u;
        return _material->getTextureColor(u, v);
    }
    else
        return Color(1, 1, 1);
}

Json::Value Sphere::toJson() const
{
    Json::Value object = Object::toJson();
    object["type"] = "Sphere";
    object["o"] = _o.toJson();
    object["r"] = _r;
    if (_material->hasTexture())
    {
        object["texture_dz"] = _dz.toJson();
        object["texture_dx"] = _dx.toJson();
    }
    return object;
}
