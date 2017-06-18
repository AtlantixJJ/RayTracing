#include "common/const.h"
#include "light/light.h"
#include "object/object.h"
#include "engine/raytracer.h"
#include "scene/camera.h"
#include "scene/scene.h"

void RayTracer::run(Scene* scene, const std::string& outFile)
{
    m_scene = scene;
    Camera* camera = m_scene->getCamera();
    int w = camera->getW(), h = camera->getH();

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            if (!j) cout << "column " << i << endl;
            Vector3 dir = camera->emit(i, j);
            Color color = rayTracing(camera->getEye(), dir, 1, 1, false);
            camera->setColor(i, j, color);
        }

    camera->print(outFile.c_str());
}

Color RayTracer::calcLocalIllumination(const Collision& coll, const Material* material) const
{
    Vector3 r = coll.ray_dir.reflect(coll.n);
    Color color = material->color * coll.object->getTextureColor(coll);
    Color ret = color * m_scene->getAmbientLightColor() * material->diff; // 环境光
    for (auto light = m_scene->lightsBegin(); light != m_scene->lightsEnd(); light++)
    {
        Vector3 l = ((*light)->getSource() - coll.p).unitize();
        double f = l.dot(coll.n);
        if (f < Const::EPS) continue;
        double shade = (*light)->getShadowRatio(m_scene, coll.p);
        if (shade < Const::EPS) continue;

        if (material->diff > Const::EPS) // 漫反射
            ret += color * (*light)->getColor() * (material->diff * f * shade);
        if (material->spec > Const::EPS) // 镜面反射
            ret += color * (*light)->getColor() * (material->spec * pow(l.dot(r), Const::SPEC_POWER));
    }
    return ret;
}

Color RayTracer::rayTracing(const Vector3& start, const Vector3& dir, double weight, int depth, bool isInternal) const
{
    if (weight < Const::MIN_WEIGHT) return m_scene->getAmbientLightColor();
    Collision coll = m_scene->findNearestCollision(start, dir);
    if (!coll.isHit())
        return m_scene->getAmbientLightColor();
    else if (coll.atLight())
        return coll.light->getColor();
    else if (depth <= Const::MAX_DEPTH)
    {
        Color ret;
        const Object* obj = coll.object;
        const Material* material = obj->getMaterial();

        if (material->diff > Const::EPS || material->spec > Const::EPS)
            ret += calcLocalIllumination(coll, material);
        
        if (material->refl > Const::EPS || material->refr > Const::EPS)
        {
            double n = material->rindex;
            if (isInternal) n = 1 / n;
            Vector3 refl = coll.ray_dir.reflect(coll.n);
            Vector3 refr = coll.ray_dir.refract(coll.n, n);
            if (material->refr < Const::EPS) // 全镜面反射
                ret += rayTracing(coll.p, refl, weight * material->refl, depth + 1, isInternal) * (material->color * material->refl);
            else if (refr.mod2() < Const::EPS) // 全反射
            {
                double k = (material->refl + material->refr) / 2;
                ret += rayTracing(coll.p, refl, weight * k, depth + 1, isInternal) * (material->color * k);
            }
            else if (material->refl < Const::EPS) // 全透射
                ret += rayTracing(coll.p, refr, weight * material->refr, depth + 1, !isInternal) * material->refr;
            else
            {
                // Fresnel equations
                double cosI = -coll.ray_dir.dot(coll.n), cosT = sqrt(1 - (1 - cosI * cosI) / n / n);
                double r1 = (cosI * n - cosT) / (cosI * n + cosT),
                       r2 = (cosI - cosT * n) / (cosI + cosT * n);
                double kl = (r1 * r1 + r2 * r2) / 2, kr = 1 - kl;
                kl *= material->refl, kr *= material->refr;

                if (kl > Const::EPS) ret += rayTracing(coll.p, refl, weight * kl, depth + 1, isInternal) * (material->color * kl);
                if (kr > Const::EPS) ret += rayTracing(coll.p, refr, weight * kr, depth + 1, !isInternal) * kr;
            }
        }

        // 透明材质的颜色过滤
        if (isInternal)
            ret *= (material->absorb_color * -coll.dist).exp();

        return ret.confine();
    }
    else
        return Color();
}
