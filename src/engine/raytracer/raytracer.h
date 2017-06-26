#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "common/common.h"
#include "engine/engine.h"

/**
*  Basic Raytracer
**/
class RayTracer : public Engine
{
public:
    RayTracer(Scene* scene);
    virtual ~RayTracer();

    virtual void run(const std::string& outFile) override;
protected:
    bool isbase;
    int _cur_x, _cur_y; ///< the current tracing element
    ID** _hash; ///< using hash to accerlerate inersection

    virtual Color _localIllumination(const Intersection& coll, const Material* Material, const Color& f, int fx=-1, int fy=-1) const;
    
    Color _rayTracing(const Ray& ray, int fx, int fy, 
        const Color& factor, double weight, int depth, bool isInternal) const;
    
    Color _DOFTracing(double ox, double oy, double factor = 1) const; /// depth of field
};

#endif // RAYTRACER_H
