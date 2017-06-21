#ifndef PHOTONTRACER_H
#define PHOTONTRACER_H

#include "engine/photonmap/statmap.h"
#include "common/config.h"

class Scene;

class PhotonTracer
{
public:
    StatMap* getPhotonMap(){return map;}
    void buildPhotonMap();
    
    PhotonTracer(Scene* s)
        : map(nullptr), scene(s) {}
    ~PhotonTracer() {}
protected:
    
    void tracePhoton(Photon& photon, int depth, bool isInternal);

    void clear() {
        if (map) delete [] map;
    }

protected:
    StatMap* map;
    Scene* scene;
    Config *gconf;
};

#endif // PHOTONTRACER_H
