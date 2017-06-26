#ifndef HITPOINTMAP_H
#define HITPOINTMAP_H
#include "common/common.h"
#include "object/material.h"
#include "omp.h"
#include <vector>
struct HitPoint;

struct HitPoint
{
    HitPoint()
        : N(0), M(0), flux() {}

    double r2;  
    int N, M; 
    Color flux; 
    Vector3 pos, n, dir;      
    const Material* material; 
    int x, y;                 
    Color color;  
    void update(const Photon& photon,bool dbgf=false)
    {
        M++;
        if (photon.dir.dot(n) < -Const::EPS)
            flux += photon.pow * material->BRDF(-photon.dir, n, dir);
        if (dbgf && DEBUG >= 1){
            printf("UPD : power : ");
            std::cout<<photon.pow<<" "<< material->BRDF(-photon.dir, n, dir)<<std::endl;
        }
    }
};

struct Node{
    Node()
        : point(nullptr) {}
    Node(HitPoint* p) : point(p){
        double r = sqrt(p->r2);
        x1 = p->pos.x - r, x2 = p->pos.x + r;
        y1 = p->pos.y - r, y2 = p->pos.y + r;
        z1 = p->pos.z - r, z2 = p->pos.z + r;
    }

    void updateBoundingBox(Node* child){
        x1 = std::min(x1, child->x1);
        x2 = std::max(x2, child->x2);
        y1 = std::min(y1, child->y1);
        y2 = std::max(y2, child->y2);
        z1 = std::min(z1, child->z1);
        z2 = std::max(z2, child->z2);
    }

    HitPoint* point;
    double x1, x2, y1, y2, z1, z2; // bounding box
};

class HitPointMap
{
public:
    HitPointMap()
        : _n(0), _plane(nullptr), _nodes(nullptr) {
            omp_init_lock(&lockp);
        }
    ~HitPointMap();

    std::vector<HitPoint>::const_iterator hitPointBegin() const { return _points.begin(); }
    std::vector<HitPoint>::const_iterator hitPointEnd() const { return _points.end(); }

    void addHitPoint(const HitPoint& point) {
        //printf("addHit\n");
        omp_set_lock(&lockp);
        _points.push_back(point);
        omp_unset_lock(&lockp); 
    }

    void incomingPhoton(const Photon& photon);
    void buildKDTree();
    void update();

private:

    omp_lock_t lockp;
    int _n;
    unsigned char* _plane;
    Node* _nodes;
    std::vector<HitPoint> _points;

    void _build(int l, int r);

    void _rebuild(int l, int r);

    void _findHitPointsbyDist(int l, int r, const Photon& photon);
};

#endif // HITPOINTMAP_H
