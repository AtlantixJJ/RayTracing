#include "math/vector2.h"

#include <cstdio>

Point2D::Point2D(const Json::Value& vec)
    : x(0), y(0)
{
    if (vec.isString())
    {
        string s = vec.asString();
        sscanf(s.c_str(), "(%lf,%lf)", &x, &y);
    }
}

Json::Value Point2D::toJson() const
{
    char str[256];
    sprintf(str, "(%lf, %lf)", x, y);
    return Json::Value(str);
}
