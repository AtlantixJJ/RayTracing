#ifndef BEZIERCURVE3_H
#define BEZIERCURVE3_H

#include "math/vector2.h"

struct BezierCurve3
{
public:
    BezierCurve3(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3);
    BezierCurve3(const Json::Value& curve);

    Point2D P(double t) const;                                                  // 曲线上一点 P(t)
    Point2D dP(double t) const;                                                 // 曲线上一点 P(t) 的切向量 P'(t)
    void getEquation(Point2D& q0, Point2D& q1, Point2D& q2, Point2D& q3) const; // 曲线方程各项的系数

    Json::Value toJson() const;

    Point2D P0, P1, P2, P3;
    double L, R, D, U; // AABB
};

#endif // BEZIERCURVE3_H
