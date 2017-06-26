#include "object/geometry.h"
#include "object/object.h"
#include "object/rotationbody.h"

#include <fstream>
#include <iostream>
#include <json/reader.h>
#include <json/writer.h>

Object::Object(const Material* m)
    : _material(m == nullptr ? new Material() : m),
      _id(randID),
      _can_delete_material(m == nullptr ? true : false)
{
}

Object::Object(const Json::Value& object)
    : _material(object["material"].isNull() ? new Material() : new Material(object["material"])),
      _id(randID),
      _can_delete_material(true)
{
}

Object::~Object()
{
    if (_can_delete_material && _material) delete _material;
}

Json::Value Object::toJson() const
{
    Json::Value object;
    object["material"] = _material->toJson();
    return object;
}

void Object::save2Json(const std::string& file) const
{
    std::ofstream fout(file.c_str());
    fout << this->toJson() << std::endl;
    fout.close();
}

Object* Object::fromJson(const Json::Value& value)
{
    std::string type = value["type"].asString();
    if (type == "Plane")
        return new Plane(value);
    else if (type == "Sphere")
        return new Sphere(value);
    else if (type == "Cylinder")
        return new Cylinder(value);
    else if (type == "RotationBody")
        return new RotationBody(value);
    else
        return nullptr;
}

Object* Object::loadFile(const std::string& file)
{
    Json::Value obj;
    std::ifstream fin(file.c_str());
    if (!fin)
    {
        std::cerr << "ERROR: No such scene file '" + file + "'" << std::endl;
        return nullptr;
    }
    fin >> obj;
    fin.close();

    return fromJson(obj);
}
