#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "common/common.h"

#include <queue>
#include <vector>

class Intersection;
/**
*   Photon Map.
**/
class PhotonMap
{
public:
    PhotonMap()
        : _n(0), _plane(nullptr), _photons(nullptr) {}
    ~PhotonMap();

    void addPhoton(const Photon& photon) {
        //printf("add a photon\n");
        //std::cout<< photon;
        _buffer.push_back(photon);
        //printf("ph done.\n");
    }

    Color getIrradiance(const Intersection& coll, int samples) const;

    void build(); ///< Interface to create the tree

private:
    int _n; /// < the number of photons
    unsigned char* _plane;
    Photon* _photons;
    std::vector<Photon> _buffer;
    //int _samples; // k-nearest
    //Vector3 _pos; // collision point
    //// Deprecated
    //std::priority_queue<pair<double, int>> _pq;
    // make KD-tree
    void _build(int l, int r);

    // samples-nearest neighbor
    void _findNearestPhotons(int l, int r, Vector3 pos, int samples, std::priority_queue<pair<double, int>> *)const;
};

#endif // PHOTONMAP_H
