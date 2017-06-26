#ifndef ROTATIONBODY_H
#define ROTATIONBODY_H

#include "math/vector3.h"
#include "object/object.h"
#include "math/beziercurve.h"

#include <vector>

class RotationBody : public Object
{
public:
    typedef std::vector<BezierCurve> Curves;

    RotationBody(const Vector3& o, const Curves& curves = {}, const Material* m = nullptr);
    RotationBody(const Json::Value& object);
    ~RotationBody();

    virtual std::string getType() const override { return "RotationBody"; }

    // 与视线相交
    virtual Intersection collide(const Ray& ray) const override;

    // 交点处的纹理颜色
    virtual Color getTextureColor(const Intersection& coll) const override;

    virtual Json::Value toJson() const override;

    void setO(const Vector3& o) { _o = o; }

    // 设置纹理起点极角
    void setTextureArg(double a) { _arg = a; }

    // 设置子曲面纹理比例
    void setTextureRatio(const std::vector<double>& ratios) { _texture_ratios = ratios; }

    BezierCurve getCurve(int i) const { return _curves[i]; }

    void addCurve(const BezierCurve& curve) { _curves.push_back(curve); }

    // 曲面上一点 P(u, v)
    Vector3 P(int i, double u, double v) const;

    // 保存为 OBJ 格式
    void save2JsonOBJ(const std::string& file, int density) const;

private:
    Vector3 _o;                                                // 底面中心点
    Curves _curves;                                            // 曲线
    double _r, _h, _arg;                                     // 包围圆柱体的底面半径、高，纹理起点极角
    std::vector<double> _texture_ratios, _texture_ratios_sum; // 每个子曲面纹理的比例，比例前缀和

    Cylinder* _bounding_cylinder;          // 包围圆柱体
    std::vector<Cylinder*> _ssc; // 子旋转面的包围圆柱体
    std::vector<ID> _ids;      // 每个子旋转面都有标识符

    void _init();

    Vector3 _dPdu(int i, double u, double v) const; // 对 u 的偏导数
    Vector3 _dPdv(int i, double u, double v) const; // 对 v 的偏导数
};

#endif // ROTATIONBODY_H