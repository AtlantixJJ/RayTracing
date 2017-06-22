#include "light/light.h"
#include "common/intersection.h"
#include "object/object.h"

Intersection::Intersection()
    : dist(1e9)
{
}

Intersection::Intersection(const Ray& ray, double t, const Vector3& n, const Object* obj, ID idf, bool in)
    : obj(obj), light(nullptr),
      ray(ray.normalize()), p(ray.get(t)), n(n.normalize()),
      dist(t * ray.dir.mod()), isin(in),
      obj_id(idf ? idf : obj->getIdentifier())
{
}

Intersection::Intersection(const Ray& ray, double t, double u, double v, const Vector3& n, const Object* obj, ID idf, bool in)
    : obj(obj), light(nullptr),
      ray(ray.normalize()), p(ray.get(t)), n(n.normalize()),
      dist(t * ray.dir.mod()), u(u), v(v), isin(in),
      obj_id(idf ? idf : obj->getIdentifier())
{
}

Intersection::Intersection(const Ray& ray, double t, const Light* l)
    : obj(nullptr), light(l),
      ray(ray.normalize()), p(ray.get(t)),
      dist(t * ray.dir.mod()), isin(false),
      obj_id(l->getIdentifier())
{
}
