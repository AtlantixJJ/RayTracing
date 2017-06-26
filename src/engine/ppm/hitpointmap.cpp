#include "utils/config.h"
#include "common/const.h"
#include "engine/ppm/hitpointmap.h"

#include <algorithm>

HitPointMap::~HitPointMap()
{
    omp_destroy_lock(&lockp);
    if (_nodes) delete[] _nodes;
    if (_plane) delete[] _plane;
    _points.clear();
}

void HitPointMap::incomingPhoton(const Photon& photon)
{
    _findHitPointsbyDist(0, _n, photon);
}

void HitPointMap::buildKDTree()
{
    if (_nodes) delete[] _nodes;
    if (_plane) delete[] _plane;

    _n = _points.size();
    _plane = new unsigned char[_n * 2];
    _nodes = new Node[_n * 2];

    cout << "Total hit points: " << _n << endl;
    _build(0, _n);
}

void HitPointMap::update()
{
    printf("In Hitpoint Update...\n");
    for (auto& point : _points)
        if (point.M)
        {
            double k = (point.N + point.M * Config::ppm_dec) / (point.N + point.M);
            point.r2 *= k;
            point.flux *= k;
            point.N += point.M * Config::ppm_dec;
            point.M = 0;
        }
    _rebuild(0, _n);
}

void HitPointMap::_findHitPointsbyDist(int l, int r, const Photon& photon)
{
    if (l >= r) return;
    int mi = (l + r) >> 1, k = _plane[mi];
    Vector3 pos = photon.pos;

    if (pos.x < _nodes[mi].x1 || pos.x > _nodes[mi].x2 ||
        pos.y < _nodes[mi].y1 || pos.y > _nodes[mi].y2 ||
        pos.z < _nodes[mi].z1 || pos.z > _nodes[mi].z2) return;

    if ((pos - _nodes[mi].point->pos).mod2() <= _nodes[mi].point->r2){
        if(randDouble < 0.001){
            if(DEBUG>=1)std::cout<<"flo:"<<_nodes[mi].point->flux<<std::endl;
            _nodes[mi].point->update(photon, true);
            if(DEBUG>=1)std::cout<<"flo:"<<_nodes[mi].point->flux<<std::endl;
        }else
            _nodes[mi].point->update(photon);
    }

    if (pos[k] - _nodes[mi].point->pos[k] < 0)
    {
        _findHitPointsbyDist(l, mi, photon);
        _findHitPointsbyDist(mi + 1, r, photon);
    }
    else
    {
        _findHitPointsbyDist(mi + 1, r, photon);
        _findHitPointsbyDist(l, mi, photon);
    }
}

void HitPointMap::_build(int l, int r)
{
    if (l >= r) return;
    int mi = (l + r) >> 1, k;

    double mean[3] = {0}, var[3] = {0};
    for (int i = l; i < r; i++)
        for (int j = 0; j < 3; j++) mean[j] += _points[i].pos[j];
    mean[0] /= r - l;
    mean[1] /= r - l;
    mean[2] /= r - l;
    for (int i = l; i < r; i++)
        for (int j = 0; j < 3; j++) var[j] += (_points[i].pos[j] - mean[j]) * (_points[i].pos[j] - mean[j]);
    if (var[0] > var[1] && var[0] > var[2])
        k = 0;
    else if (var[1] > var[0] && var[1] > var[2])
        k = 1;
    else
        k = 2;
    _plane[mi] = k, _nodes[mi] = Node(&_points[mi]);

    nth_element(_points.begin() + l, _points.begin() + mi, _points.begin() + r, [&](const HitPoint& x, const HitPoint& y) {
        return x.pos[k] < y.pos[k];
    });

    if (l < mi)
    {
        _build(l, mi);
        _nodes[mi].updateBoundingBox(&_nodes[(l + mi) >> 1]);
    }
    if (mi + 1 < r)
    {
        _build(mi + 1, r);
        _nodes[mi].updateBoundingBox(&_nodes[(mi + 1 + r) >> 1]);
    }
}

void HitPointMap::_rebuild(int l, int r)
{
    if (l >= r) return;
    int mi = (l + r) >> 1;

    _nodes[mi] = Node(&_points[mi]);
    if (l < mi)
    {
        _rebuild(l, mi);
        _nodes[mi].updateBoundingBox(&_nodes[(l + mi) >> 1]);
    }
    if (mi + 1 < r)
    {
        _rebuild(mi + 1, r);
        _nodes[mi].updateBoundingBox(&_nodes[(mi + 1 + r) >> 1]);
    }
}
