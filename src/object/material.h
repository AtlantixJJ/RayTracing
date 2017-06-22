#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils/bmp.h"
#include "common/common.h"

struct Vector3;

struct Material
{
public:
    Material();
    Material(const Color& c, double d, double s);
    Material(const Color& c, double d, double s, double rl);
    Material(const Color& c, double d, double s, double rl, double rr, double ri, const Color& absorb);
    Material(const Json::Value material);

    virtual ~Material();

    Color color, absorb_color; // 颜色，透射时吸收的颜色
    double diff, spec;         // 漫反射系数，镜面反射系数
    double refl, refr;         // 反射和折射光的比例
    double rindex;             // 折射率

    bool hasTexture() const { return _texture || _texture_func; }

    void setTexture(Bmp* texture) { _texture_func = nullptr, _texture = texture; }
    void setTexture(Color (*func)(double, double))
    {
        if (_texture) delete _texture;
        _texture = nullptr, _texture_func = func;
    }
    Color getTextureColor(double u, double v) const;
    bool compare(const Material* B) const;
    double BRDF(const Vector3& l, const Vector3& n, const Vector3& v) const;

    virtual Json::Value toJson() const;

private:
    Bmp* _texture; 
    Color (*_texture_func)(double, double);
};

#endif // MATERIAL_H
