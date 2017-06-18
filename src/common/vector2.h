#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>
#include <json/value.h>

struct Vector2
{
public:
    Vector2()
        : x(0), y(0) {}
    Vector2(double x, double y)
        : x(x), y(y) {}
    Vector2(const Json::Value& vec);

    friend Vector2 operator+(const Vector2& A, const Vector2& B){return Vector2(A.x + B.x, A.y + B.y);}
    friend Vector2 operator-(const Vector2& A, const Vector2& B){return Vector2(A.x - B.x, A.y - B.y);}
    friend double operator*(const Vector2& A, const Vector2& B){return A.x * B.y - A.y * B.x;}
    friend std::ostream& operator<<(std::ostream& out, const Vector2& v);
    Vector2 operator-() const{return Vector2(-x, -y);}
    Vector2 operator*(double k) const{return Vector2(x * k, y * k);}
    Vector2 operator/(double k) const{return Vector2(x / k, y / k);}
    double dot(const Vector2& B) const{return x * B.x + y * B.y;}
    double mod() const;//{return sqrt(x * x + y * y);}
    double arg() const;//{return atan2(y, x);}
    double mod2() const{return x * x + y * y;}


    Vector2 unitize() const; // 单位化

    Json::Value toJson() const;

    double x, y;
};

#endif // VECTOR2_H
