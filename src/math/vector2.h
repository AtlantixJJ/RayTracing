#ifndef VECTOR2_H
#define VECTOR2_H

#include "common/const.h"

#include <ostream>
#include <json/value.h>

struct Point2D
{
    Point2D()
        : x(0), y(0) {}
    Point2D(double x, double y)
        : x(x), y(y) {}
    Point2D(const Json::Value& vec);

    Point2D operator-() const { return Point2D(-x, -y); }

    Point2D operator*(double k) const { return Point2D(x * k, y * k); }

    Point2D operator/(double k) const { return Point2D(x / k, y / k); }

    // 点积
    double dot(const Point2D& B) const { return x * B.x + y * B.y; }

    // 模长
    double mod() const { return sqrt(x * x + y * y); }

    // 模长平方
    double mod2() const { return x * x + y * y; }

    // 极角
    double arg() const { return atan2(y, x); }

    // 单位化
    Point2D normalize() const
    {
        double m = mod();
        return *(this) / (m < Const::EPS ? 1 : m);
    }

    Json::Value toJson() const;

    double x, y;
};

inline Point2D operator+(const Point2D& A, const Point2D& B)
{
    return Point2D(A.x + B.x, A.y + B.y);
}

inline Point2D operator-(const Point2D& A, const Point2D& B)
{
    return Point2D(A.x - B.x, A.y - B.y);
}

inline double operator*(const Point2D& A, const Point2D& B)
{
    return A.x * B.y - A.y * B.x;
}

inline std::ostream& operator<<(std::ostream& out, const Point2D& v)
{
    return out << '(' << v.x << ' ' << v.y << ')';
}

#endif // VECTOR2_H
