#include "engine/photonmapper/photonmapper.h"
#include "engine/ppm/ppm.h"
#include "engine/raytracer/raytracer.h"
#include "omp.h"
#include <cstring>

int main(int argc, char* argv[])
{
    string file(argv[1]);

    Engine* engine;
    Scene* scene = Scene::loadFrom(file);
    switch (atoi(argv[2]))
    {
    case 0:
        engine = new RayTracer(scene);
        break;
    case 1:
        engine = new PhotonMapper(scene);
        break;
    case 2:
        engine = new PPM(scene);
        break;
    }

    engine->run(argv[2]);

    if (scene) delete scene;
    delete engine;
    return 0;
}
