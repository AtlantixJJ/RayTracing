#include "light/light.h"
#include "light/pointlight.h"
#include "light/rectlight.h"

Json::Value Light::toJson() const
{
    Json::Value light;
    light["color"] = _color.toJson();
    light["power"] = _power;
    return light;
}

Light* Light::fromJson(const Json::Value& value)
{
    std::string type = value["type"].asString();
    if (type == "PointLight")
        return new PointLight(value);
    else if (type == "RectLight")
        return new RectLight(value);
    else
        return nullptr;
}
