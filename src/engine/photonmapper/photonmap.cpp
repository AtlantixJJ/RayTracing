#include "common/const.h"
#include "engine/photonmapper/photonmap.h"
#include "common/intersection.h"

#include <algorithm>

PhotonMap::~PhotonMap()
{
    if (_photons) delete[] _photons;
    if (_plane) delete[] _plane;
}

Color PhotonMap::getIrradiance(const Intersection& coll, int samples) const
{
    std::priority_queue<pair<double, int>> *queue = new std::priority_queue<pair<double, int>>();
    queue->push(make_pair(0.1, -1)); // 最大采样半径

    //cout << samples << " " << coll.p << endl;    
    _findNearestPhotons(0, _n, coll.p, samples, queue);

    Color ret;
    double maxDist = queue->top().first, k = 1;
    for (int i = 0; i < samples && !queue->empty(); i++, queue->pop())
    {
        int id = queue->top().second;
        //cout<<id<<' '<<queue.top().first<<' '<<_photons[id].pow<<endl;
        if (id >= 0 && coll.n.dot(_photons[id].dir) < -Const::EPS)
            ret += _photons[id].pow ;//* (1 - queue->top().first / maxDist / k);
    }

    delete queue;
    //cout<<ret<<endl;
    return ret * (1 / Const::PI / maxDist) ;/// (1 - 2 / 3 / k);
}

void PhotonMap::build()
{
    printf("Building Photon Map...\n");
    if (_photons) delete[] _photons;
    if (_plane) delete[] _plane;

    _n = _buffer.size();
    _photons = new Photon[_n];
    for (int i = 0; i < _n; i++) _photons[i] = _buffer[i];
    _buffer.clear();
    _plane = new unsigned char[_n * 2];

    cout << "Total photons: " << _n << endl;
    _build(0, _n);
}

void PhotonMap::_findNearestPhotons(int l, int r, Vector3 pos, int samples,
    std::priority_queue<pair<double, int>> *q) const
{
    if (l >= r) return;
    int mi = (l + r) >> 1, k = _plane[mi];

    double dist = pos[k] - _photons[mi].pos[k], res = (_photons[mi].pos - pos).mod2();
    if (res < q->top().first)
    {
        if ((int) q->size() == samples) q->pop();
        q->push(make_pair(res, mi));
    }

    if (dist < 0)
    {
        _findNearestPhotons(l, mi, pos, samples, q);
        if (dist * dist < q->top().first) 
        _findNearestPhotons(mi + 1, r, pos, samples, q);
    }
    else
    {
        _findNearestPhotons(mi + 1, r, pos, samples, q);
        if (dist * dist < q->top().first) 
        _findNearestPhotons(l, mi, pos, samples, q);
    }
}

void PhotonMap::_build(int l, int r)
{
    if (l >= r) return;
    int mi = (l + r) >> 1, k;

    // 选择方差最小的坐标分量进行划分
    double mean[3] = {0}, var[3] = {0};
    for (int i = l; i < r; i++)
        for (int j = 0; j < 3; j++) mean[j] += _photons[i].pos[j];
    mean[0] /= r - l, mean[1] /= r - l, mean[2] /= r - l;
    for (int i = l; i < r; i++)
        for (int j = 0; j < 3; j++) var[j] += (_photons[i].pos[j] - mean[j]) * (_photons[i].pos[j] - mean[j]);
    if (var[0] > var[1] && var[0] > var[2])
        k = 0;
    else if (var[1] > var[0] && var[1] > var[2])
        k = 1;
    else
        k = 2;
    _plane[mi] = k;

    nth_element(_photons + l, _photons + mi, _photons + r, [&](const Photon& x, const Photon& y) {
        return x.pos[k] < y.pos[k];
    });
    _build(l, mi);
    _build(mi + 1, r);
}
