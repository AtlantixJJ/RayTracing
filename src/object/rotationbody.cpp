#include "common/const.h"
#include "object/geometry.h"
#include "object/rotationbody.h"
#include "math/polynomial6.h"

RotationBody::RotationBody(const Vector3& o, const Curves& curves, const Material* m)
    : Object(m), _o(o), _curves(curves),
      _r(0), _h(0), _arg(0)
{
    _init();
}

RotationBody::RotationBody(const Json::Value& object)
    : Object(object), _o(object["o"]), _curves(),
      _r(0), _h(0), _arg(fmod(object["texture_arg"].asDouble() / 180 * Const::PI, 2 * Const::PI))
{
    for (auto c : object["curves"])
        _curves.push_back(BezierCurve3(c));
    _init();
}

RotationBody::~RotationBody()
{
    if (_bounding_cylinder) delete _bounding_cylinder;
    for (auto c : _sub_cylinders) delete c;
    _sub_cylinders.clear();
}

Intersection RotationBody::collide(const Ray& ray) const
{
    Ray uray = ray.normalize();
    Vector3 d = uray.dir;
    int curve_id = 0;
    Point2D res(1e9, 0);

    Intersection coll = _bounding_cylinder->collide(ray);
    if (!coll.isHit()) return Intersection();

    for (size_t i = 0; i < _curves.size(); i++)
    {
        coll = _sub_cylinders[i]->collide(ray);
        if (!coll.isHit() || (!coll.isInternal() && coll.dist > res.x - Const::EPS)) continue;

        Vector3 o = ray.start - _o;
        Point2D w = d.toPoint2D(), q0, q1, q2, q3;
        // A.y^2 + B.y + C + D.x^2 = 0
        long double A = w.mod2(), B = 2 * w.dot(o.toPoint2D()) * d.z - 2 * o.z * A,
                    C = Point2D(o.z * d.x - o.x * d.z, o.z * d.y - o.y * d.z).mod2(), D = -d.z * d.z,
                    a[7];

        // a0 + a1.u + a2.u^2 + a3.u^3 + a4.u^4 + a5.u^5 + a6.u^6 = 0
        _curves[i].getEquation(q0, q1, q2, q3);
        a[0] = A * q0.y * q0.y + D * q0.x * q0.x + C + B * q0.y;
        a[1] = 2 * A * q0.y * q1.y + 2 * D * q0.x * q1.x + B * q1.y;
        a[2] = A * (q1.y * q1.y + 2 * q0.y * q2.y) + D * (q1.x * q1.x + 2 * q0.x * q2.x) + B * q2.y;
        a[3] = 2 * A * (q0.y * q3.y + q1.y * q2.y) + 2 * D * (q0.x * q3.x + q1.x * q2.x) + B * q3.y;
        a[4] = A * (2 * q1.y * q3.y + q2.y * q2.y) + D * (2 * q1.x * q3.x + q2.x * q2.x);
        a[5] = 2 * (A * q2.y * q3.y + D * q2.x * q3.x);
        a[6] = A * q3.y * q3.y + D * q3.x * q3.x;

        Polynomial6 poly(a);
        std::vector<double> roots = poly.findAllRoots(0, 1);
        for (auto u : roots)
        {
            double t = -1;
            Point2D p = _curves[i].P(u);
            if (abs(d.z) > Const::EPS)
                t = (p.y - o.z) / d.z;
            else
            {
                Point2D oc = -o.toPoint2D();
                double tca = oc.dot(w), thc2 = p.x * p.x - oc.mod2() + tca * tca;
                if (thc2 > -Const::EPS)
                {
                    double thc = sqrt(thc2), A = tca - thc, B = tca + thc;
                    if (A > Const::EPS)
                        t = A;
                    else
                        t = B;
                }
            }
            if (t > 1e-4 && t < res.x - Const::EPS)
                res = Point2D(t, u), curve_id = i;
        }
    }
    if (res.x < 1e9)
    {
        Point2D v = (uray.get(res.x) - _o).toPoint2D().normalize(), dp = _curves[curve_id].dP(res.y);
        Vector3 n = Vector3(-dp.y * v.x, -dp.y * v.y, dp.x);
        if (n.dot(d) < Const::EPS)
            return Intersection(uray, res.x, curve_id + res.y, fmod(v.arg(), 2 * Const::PI), n, this, _identifiers[curve_id]);
        else
            return Intersection(uray, res.x, curve_id + res.y, fmod(v.arg(), 2 * Const::PI), -n, this, _identifiers[curve_id]);
    }
    else
        return Intersection();
}

Color RotationBody::getTextureColor(const Intersection& coll) const
{
    if (_material->hasTexture())
    {
        double u = fmod(coll.v - _arg + 4 * Const::PI, 2 * Const::PI) / 2 / Const::PI,
               v = 1 - coll.u / _curves.size();
        return _material->getTextureColor(u, v);
    }
    else
        return Color(1, 1, 1);
}

Vector3 RotationBody::P(int i, double u, double v) const
{
    Point2D p = _curves[i].P(u);
    return Vector3(p.x * cos(v), p.x * sin(v), p.y) + _o;
}

void RotationBody::saveOBJ(const std::string& file, int density) const
{
    std::vector<Vector3> points;
    std::vector<std::vector<int>> meshes;
    double du = 1.0 / density, dv = 2 * Const::PI / density;
    int n = 0;
    for (size_t t = 0; t < _curves.size(); t++)
        for (int i = 0; i <= density; i++)
            for (int j = 0; j <= density; j++)
            {
                double u = i * du, v = j * dv;
                n++;
                points.push_back(P(t, u, v));
                if (i && j) meshes.push_back({n - density - 2, n - density - 1, n, n - 1});
            }

    FILE* f = fopen(file.c_str(), "w");
    for (auto p : points) fprintf(f, "v %lf %lf %lf\n", p.x, p.y, p.z);
    for (auto m : meshes) fprintf(f, "f %d %d %d %d\n", m[0], m[1], m[2], m[3]);
    fclose(f);
}

Json::Value RotationBody::toJson() const
{
    Json::Value object = Object::toJson();
    Json::Value curves;
    for (auto c : _curves) curves.append(c.toJson());
    object["type"] = "RotationBody";
    object["o"] = _o.toJson();
    object["curves"] = curves;
    if (_material->hasTexture()) object["texture_arg"] = _arg * 180 / Const::PI;
    return object;
}

void RotationBody::_init()
{
    for (auto c : _curves)
    {
        double r = std::max(abs(c.L), abs(c.R));
        _r = std::max(_r, r), _h = std::max(_h, c.U);
        _sub_cylinders.push_back(new Cylinder(Vector3(_o.x, _o.y, _o.z + c.D), r, c.U - c.D));
        _identifiers.push_back(randID);
    }
    _bounding_cylinder = new Cylinder(_o, _r, _h);
}

Vector3 RotationBody::_dPdu(int i, double u, double v) const
{
    Point2D p = _curves[i].dP(u);
    return Vector3(p.x * cos(v), p.x * sin(v), p.y);
}

Vector3 RotationBody::_dPdv(int i, double u, double v) const
{
    double x = _curves[i].P(u).x;
    return Vector3(-x * sin(v), x * cos(v), 0);
}
