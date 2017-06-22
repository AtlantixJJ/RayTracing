#ifndef ENGINE_H
#define ENGINE_H

#include "env/scene.h"

class RayTracer;
class PhotonMapper;
class PPM;

/**
* Base class of rending engine.
**/
class Engine
{
public:
    Engine(Scene* scene);

    virtual ~Engine() {}
    virtual void run(const std::string& outFile) = 0;
    bool environCheck()const;
protected:
    Scene* _scene;
    Camera* _camera;
    int _w, _h; ///< the size of the camera is duplicated here
};

#endif // ENGINE_H
