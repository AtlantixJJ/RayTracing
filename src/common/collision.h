#ifndef COLLISION_H
#define COLLISION_H

#include "common/vector3.h"
#include "const.h"
class Light;
class Object;

/**
*  The Collision class holds information of a Collision between a ray and
*  an object. Usually we give a pointer to specify a storage and use the
*  function of different type of collision to update the information.
**/

struct Collision
{
    // 不相交
    Collision();
    // 与物体相交
    static void setCollision(Collision* coll,const Vector3& start, 
        const Vector3& dir, double t, const Vector3& n,
              const Object* obj, bool in = false);
    void collide(const Vector3& start, const Vector3& dir, 
        double t, const Vector3& n,const Object* obj, bool in = false);

    // 与物体相交，包含参数
    static void setCollision(Collision* coll,const Vector3& start,
        const Vector3& dir, double t, double u, double v, 
        const Vector3& n, const Object* obj, bool in = false);
    void collide(const Vector3& start, const Vector3& dir, double t,
        double u, double v, const Vector3& n, const Object* obj,
        bool in = false);

    // 与光源相交
    static void setCollision(Collision* coll, const Vector3& start, 
        const Vector3& dir, double t, const Light* l);
    void collide(const Vector3& start, const Vector3& dir, 
        double t, const Light* l);

    // not colliding
    static void setCollision(Collision* coll);
    void collide();

    // 是否有交点
    bool isHit() const { return dist < 1e9; }

    // 是否是与物体相交
    bool atObject() const { return object != nullptr; }

    // 是否是与光源相交
    bool atLight() const { return light != nullptr; }

    void printInfo() const {
        printf("isHit : %d\t atLight : %d\n",isHit(), atLight());
        if(isHit())printf("Dist : %lf\n",dist);
        if(atLight())printf("Light : %d\n",light);
    }

    const Object* object;             // 相交的物体
    const Light* light;               // 相交的光源
    Vector3 ray_start, ray_dir, p, n; // 射线起点，射线方向，交点，交点处物体的法向量(只对与物体相交有效)，自动单位化
    double dist;                      // 交点对应的射线参数，ray_d 单位化后就是交点与射线起点间的距离
    double u, v;                      // 如果是参数曲面，保存交点处的参数
    bool is_internal;                 // 射线起点是否在物体内部（可选）
};

#endif // COLLISION_H
