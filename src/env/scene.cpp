#include "utils/config.h"
#include "common/const.h"
#include "light/light.h"
#include "light/pointlight.h"
#include "light/rectlight.h"
#include "object/object.h"
#include "object/geometry.h"
#include "env/camera.h"
#include "env/scene.h"

#include <algorithm>
#include <fstream>
#include <json/reader.h>
#include <json/writer.h>

std::string Scene::_scene_file_dir = "";

Scene::Scene(Camera* camera, const Color& ambient)
    : _camera(camera), _ambient_color(ambient)
{
    _init();
}

Scene::Scene(const Json::Value& scene)
    : _camera(new Camera(scene["camera"])), _ambient_color(scene["ambient_color"])
{
    for (auto l : scene["lights"])
    {
        Light* light = Light::loadFromJson(l);
        if (light) _lights.push_back(light);
    }
    for (auto o : scene["objects"])
    {
        Object* object;
        if (o.isString())
            object = Object::loadFrom(_scene_file_dir + "/" + o.asString());
        else
            object = Object::loadFromJson(o);
        if (object) _objects.push_back(object);
    }

    Json::Value config = scene["config"];
    if (config.isString())
        Config::loadFrom(_scene_file_dir + "/" + config.asString());
    else if (!config.isNull())
        Config::load(config);

    _init();
}

Scene::~Scene()
{
    if (_camera){
        delete _camera;
        _camera = nullptr;
    }
    for (auto i : _lights){
        delete i;
        i = nullptr;
    }
    for (auto i : _objects){
        delete i;
        i = nullptr;
    }
    _lights.clear();
    _objects.clear();
}

Intersection Scene::findNearestIntersection(const Ray& ray) const
{
    Intersection ret;
    for (auto l : _lights)
    {
        Intersection coll = l->collide(ray);
        if (coll.isHit() && coll.dist + Const::EPS < ret.dist) ret = coll;
    }
    for (auto o : _objects)
    {
        Intersection coll = o->collide(ray);
        if (coll.isHit() && coll.dist + Const::EPS < ret.dist) ret = coll;
    }
    return ret;
}

Json::Value Scene::toJson() const
{
    Json::Value scene, lights, objects;
    for (auto l : _lights) lights.append(l->toJson());
    for (auto o : _objects) objects.append(o->toJson());
    scene["ambient_color"] = _ambient_color.toJson();
    scene["lights"] = lights;
    scene["objects"] = objects;
    scene["camera"] = _camera->toJson();
    scene["config"] = Config::toJson();
    return scene;
}

void Scene::save(const std::string& file) const
{
    std::ofstream fout(file.c_str());
    fout << this->toJson() << std::endl;
    fout.close();
}

Scene* Scene::loadFrom(const std::string& file)
{
    Json::Value scene;
    std::ifstream fin(file.c_str());
    if (!fin)
    {
        std::cerr << "ERROR: No such scene file '" + file + "'" << std::endl;
        return nullptr;
    }
    fin >> scene;
    fin.close();

    _scene_file_dir = file.substr(0, file.find_last_of('/'));
    return new Scene(scene);
}

void Scene::_init()
{
    // 反射光比例小的物体优先，其次折射光
    sort(_objects.begin(), _objects.end(), [](const Object* A, const Object* B) {
        return A->getMaterial()->compare(B->getMaterial());
    });
}
