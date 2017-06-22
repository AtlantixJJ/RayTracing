#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "common/common.h"

class Light;
class Object;

/**
*   As the result description of an intersection.
*   Could be light source or object
**/
struct Intersection
{
    Intersection();
    Intersection(const Ray& ray, double t, 
        const Vector3& n, const Object* obj,
         ID idf = 0, bool in = false);
    Intersection(const Ray& ray, double t, double u, double v, const Vector3& n, const Object* obj, ID idf = 0, bool in = false);
    Intersection(const Ray& ray, double t, const Light* l);

    /// Information interface
    const Object* getObject()const{ return obj;}
    const Light* getLight()const{return light;}
    ID getID()const{return obj_id;}

    const Object* obj;
    const Light* light;
    Ray ray;
    double u, v;
    Vector3 p, n; // cross and normal
    bool isin;
    ID obj_id;
    double dist;

    bool isInternal()const{return isin;}
    bool isHit() const { return dist < 1e9; }
    bool atObject() const { return obj != nullptr; }
    bool atLight() const { return light != nullptr; }
};

#endif // COLLISION_H
