#ifndef STATMAP_H_
#define STATMAP_H_

#include "common/photon.h"
#include <queue>
#include <vector>

class Collision;

/**
* Take the statistics of Photons
**/
class StatMap
{
public:
    StatMap()
        : n(0), plane(nullptr), phs(nullptr) {}
    ~StatMap();


    void addPhoton(const Photon& photon) { buffer.push_back(photon); }
    Color getIrradiance(const Collision&, int);
    /// Start computation
    void buildMap(bool);

protected:
    // 建 KD-tree
    void buildKDTree(int l, int r);

    // 找最近 m_samples 个光子
    void findNearestPhotons(int l, int r);

    void clear(){
        if(phs) delete [] phs;
        if(plane) delete [] plane;
    }

protected:
    int n;
    unsigned char* plane;
    Photon* phs; /// photon list
    std::vector<Photon> buffer;
    std::priority_queue<pair<double, int>> q;

    int samples; // 最近的光子数
    Vector3 pos; // 询问点
};

#endif