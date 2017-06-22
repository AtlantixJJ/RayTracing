#include "utils/config.h"
#include "common/const.h"
#include "math/vector3.h"
#include "object/material.h"

Material::Material()
    : color(1, 1, 1), absorb_color(0, 0, 0), diff(0.8), spec(0.2), refl(0), refr(0), rindex(1),
      _texture(nullptr), _texture_func(nullptr)
{
}

Material::Material(const Color& c, double d, double s)
    : color(c), diff(d), spec(s), refl(0), refr(0), rindex(1),
      _texture(nullptr), _texture_func(nullptr)
{
}

Material::Material(const Color& c, double d, double s, double rl)
    : color(c), diff(d), spec(s), refl(rl), refr(0), rindex(1),
      _texture(nullptr), _texture_func(nullptr)
{
}

Material::Material(const Color& c, double d, double s, double rl, double rr, double ri, const Color& absorb)
    : color(c), absorb_color(absorb), diff(d), spec(s), refl(rl), refr(rr), rindex(ri),
      _texture(nullptr), _texture_func(nullptr)
{
}

Material::Material(const Json::Value material)
    : color(material["color"]), absorb_color(material["absorb_color"]),
      diff(material["diff"].asDouble()), spec(material["spec"].asDouble()), refl(material["refl"].asDouble()),
      refr(material["refr"].asDouble()), rindex(material["refr_index"].isNull() ? 1 : material["refr_index"].asDouble()),
      _texture(nullptr), _texture_func(nullptr)
{
    if (material["texture"].isString())
        _texture = new Bmp(material["texture"].asString());
}

Material::~Material()
{
    if (_texture) delete _texture;
}

Color Material::getTextureColor(double u, double v) const
{
    if (_texture)
        return _texture->getColor(u, v);
    else if (_texture_func)
        return _texture_func(u, v);
    else
        return Color(1, 1, 1);
}

bool Material::compare(const Material* B) const
{
    return this->refl + Const::EPS < B->refl ||
           (abs(this->refl - B->refl) < Const::EPS && this->refr + Const::EPS < B->refr);
}

double Material::BRDF(const Vector3& l, const Vector3& n, const Vector3& v) const
{
    Vector3 r = l.reflect(n);
    return diff * l.dot(n) + spec * pow(v.dot(r), Config::hightlight_exponent);
}

Json::Value Material::toJson() const
{
    Json::Value material;
    material["color"] = color.toJson();
    material["diff"] = diff;
    material["spec"] = spec;
    if (refl > Const::EPS) material["refl"] = refl;
    if (refr > Const::EPS)
    {
        material["refr"] = refr;
        material["refr_index"] = rindex;
        material["absorb_color"] = absorb_color.toJson();
    }
    if (_texture)
        material["texture"] = _texture->getFilename();
    else if (_texture_func)
        material["texture_func"] = "Function";
    return material;
}
