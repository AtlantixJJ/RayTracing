#ifndef PHOTONTRACER_H
#define PHOTONTRACER_H

struct Photon;
class Scene;
class PhotonMap;
class HitPointMap;
#include "omp.h"

class PhotonTracer
{
public:
    // 用于普通光子映射
    PhotonTracer(Scene* scene, PhotonMap* map)
        : _photon_map(map), _hit_point_map(nullptr), _scene(scene) {
            omp_init_lock(&lock);
            omp_init_lock(&lock2);
        }

    // 用于 PPM
    PhotonTracer(Scene* scene, HitPointMap* map)
        : _photon_map(nullptr), _hit_point_map(map), _scene(scene) {}

    ~PhotonTracer() {
        omp_destroy_lock(&lock);
        omp_destroy_lock(&lock2);
    }

    // 发射光子
    void emitPhotons(int photonNumber);

private:
    PhotonMap* _photon_map;
    HitPointMap* _hit_point_map;
    Scene* _scene;
    omp_lock_t lock,lock2;
    void _photonTracing(Photon& photon, int depth, bool isInternal);
};

#endif // PHOTONTRACER_H
