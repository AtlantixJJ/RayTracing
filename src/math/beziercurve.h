#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "math/vector2.h"

struct BezierCurve
{
public:
    BezierCurve(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3);
    BezierCurve(const Json::Value& curve);

    Point2D P(double t) const;     
    Point2D dP(double t) const;                                                 // 曲线上一点 P(t) 的切向量 P'(t)
    void equation(Point2D& q0, Point2D& q1,
         Point2D& q2, Point2D& q3) const;

    Json::Value toJson() const;

    Point2D P0, P1, P2, P3;
    double L, R, D, U;
};

#endif
