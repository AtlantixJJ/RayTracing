#include "engine/engine.h"
#include "engine/raytrace/raytracer.h"
#include "engine/photonmap/photonmapper.h"
#include "scene/scene.h"

int main(int argc, char* argv[])
{
    if (argc <= 1)
        printf("Usage: ./raytracing <SCENE_FILE>\n");
    else
    {
        Scene* scene = Scene::loadFrom(argv[1]);
        
        if (scene)
        {
            Engine* enginer = new RayTracer(scene);
            Engine* enginep = new PhotonMapper(scene);
            enginer->run("output.bmp");
            delete scene;
            delete enginer;
            delete enginep;
        }
        
    }
    return 0;
}
