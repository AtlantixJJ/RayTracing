#ifndef PHOTONTRACER_H
#define PHOTONTRACER_H

struct Photon;
class Scene;
class PhotonMap;
class HitPointMap;
#include "omp.h"

/**
* This class is shared by PM and PPM
**/
class PhotonTracer
{
public:
    PhotonTracer(Scene* scene, PhotonMap* map)
        : _photon_map(map), _hit_point_map(nullptr), _scene(scene) {
            omp_init_lock(&lock);
            omp_init_lock(&lock2);
        }

    PhotonTracer(Scene* scene, HitPointMap* map)
        : _photon_map(nullptr), _hit_point_map(map), _scene(scene) {
            omp_init_lock(&lock);
            omp_init_lock(&lock2);
        }

    ~PhotonTracer() {
        omp_destroy_lock(&lock);
        omp_destroy_lock(&lock2);
    }

    void emitPhotons(int photonNumber);

private:
    int asd; ///< test var
    PhotonMap* _photon_map;
    HitPointMap* _hit_point_map;
    Scene* _scene;
    omp_lock_t lock,lock2;
    void _photonTracing(Photon& photon, int depth, bool isInternal);
};

#endif // PHOTONTRACER_H
