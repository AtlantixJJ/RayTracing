#include "engine/engine.h"
#include "env/camera.h"
#include "utils/config.h"

Engine::Engine(Scene* scene)
    : _scene(scene), _camera(nullptr), _w(0), _h(0)
{
    if(environCheck()){
        if (_scene)
        {
            _camera = _scene->getCamera();
            _w = _camera->getW();
            _h = _camera->getH();
        }
    }

    printf("MaxThread : %d\n",Config::thread_max_number);
}

bool Engine::environCheck()const{
#ifndef _OPENMP
    printf("OpenMP not supported!\n");
    return false;
#else
    printf("OpenMP supported.\n");
    return true;
#endif
}