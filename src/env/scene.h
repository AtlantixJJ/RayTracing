#ifndef SCENE_H
#define SCENE_H

#include "light/light.h"
#include "object/object.h"

#include <vector>

class Camera;

class Scene
{
public:
    Scene(Camera* camera, const Color& ambient);
    Scene(const Json::Value& scene);
    ~Scene();

    Camera* getCamera() const { return _camera; }
    Color getAmbientLightColor() const { return _ambient_color; }
    Light* getLight(int i) const { return _lights[i]; }
    Object* getObject(int i) const { return _objects[i]; }

    void addLight(Light* light) { _lights.push_back(light); }
    void addObject(Object* object) { _objects.push_back(object); }

    std::vector<Light*>::const_iterator lightsBegin() const { return _lights.begin(); }
    int getLightSourceNum()const{return _lights.size();}
    Light* getLightbyInd(int i){return _lights[i];}
    std::vector<Light*>::const_iterator lightsEnd() const { return _lights.end(); }
    std::vector<Object*>::const_iterator objectsBegin() const { return _objects.begin(); }
    std::vector<Object*>::const_iterator objectsEnd() const { return _objects.end(); }

    // 寻找视线最先碰到的物体或光源
    Intersection findNearestIntersection(const Ray& ray) const;

    // 保存为 JSON 格式
    Json::Value toJson() const;

    // 保存 JSON 到文件
    void save(const std::string& file) const;

    // 从文件导入场景
    static Scene* loadFrom(const std::string& file);

private:
    Camera* _camera;      // 相机
    Color _ambient_color; // 环境光

    std::vector<Light*> _lights;
    std::vector<Object*> _objects;

    static std::string _scene_file_dir; // 场景文件路径

    void _init();
};

#endif // SCENE_H
