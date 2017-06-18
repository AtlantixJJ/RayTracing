#include "common/const.h"
#include "common/vector2.h"

Vector2::Vector2(const Json::Value& vec)
    : x(0), y(0)
{
    if (vec.isString())
    {
        string s = vec.asString();
        sscanf(s.c_str(), "(%lf,%lf)", &x, &y);
    }
}

std::ostream& operator<<(std::ostream& out, const Vector2& v)
{
    return out << '(' << v.x << ' ' << v.y << ')';
}

Vector2 Vector2::unitize() const
{
    double m = mod();
    return *(this) / (m < Const::EPS ? 1 : m);
}

double Vector2::mod() const{return sqrt(x * x + y * y);}
double Vector2::arg() const{return atan2(y, x);}

Json::Value Vector2::toJson() const
{
    char str[256];
    sprintf(str, "(%lf, %lf)", x, y);
    return Json::Value(str);
}
