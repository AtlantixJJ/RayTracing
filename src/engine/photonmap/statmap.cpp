#include "common/const.h"
#include "engine/photonmap/statmap.h"
#include "common/collision.h"
#include <algorithm>

StatMap::~StatMap()
{
    clear();
}

Color StatMap::getIrradiance(const Collision& coll, int N)
{
    // Clear the queue
    while ( !q.empty() ) q.pop();

    q.push( make_pair(Const::PH_DEC, -1));
    samples = N;    pos = coll.p;

    Color res;
    double maxDist = q.top().first, k = 1;
    int i, id;
    for(i = 0; i < N && !q.empty() ; ++i, q.pop())
    {
        id = q.top().second;
        if (id >= 0 && coll.n.dot( phs[id].dir ) < Const::EPS )
            res += phs[id].pow * (1 - q.top().first / maxDist / k);
    }
    res *= (4 / Const::PI / maxDist / (1 - 2. / 3. / k));
    return res;
}

void StatMap::buildMap(bool flag)
{
    if(flag)clear();
    n = buffer.size();
    phs = new Photon[n];

    int i;
    for( i = 0 ; i < n; ++i)
        phs[i] = buffer[i];
    buffer.clear();
    plane = new unsigned char [n*2];
    buildKDTree(0, n);
}

void StatMap::buildKDTree(int l, int r)
{
    if( l >= r )return;
    int mid = (l+r)>>1,k;
    int i,j;
    double avg[3] = {0,0,0};
    double var[3] = {0,0,0};
    
    /// Choose the component that has the lowest variance
    for(i = l ; i < r ; ++i)
        for(j = 0 ; j < 3 ; ++ j)
            avg[j] += phs[i].pos[j];
    for(j = 0 ; j < 3 ; ++ j) avg[j] /= double(r - l);

    for(i = l ; i < r ; ++i)
        for(j = 0 ; j < 3 ; ++ j)
            var[j] += (phs[i].pos[j] - avg[j]) * (phs[i].pos[j] - avg[j]);
    
    if (var[0] > var[1] && var[0] > var[2])
        k = 0;
    else if (var[1] > var[0] && var[1] > var[2])
        k = 1;
    else
        k = 2;
    
    plane[mid] = k;

    nth_element(phs + l, phs + mid, phs + r,
         [&](const Photon& x, const Photon& y) {
              return x.pos[k] < y.pos[k]; 
              } );
    buildKDTree(l, mid);
    buildKDTree(mid + 1, r);
}

void StatMap::findNearestPhotons(int l, int r)
{
    if (l >= r) return;
    int mid = (l + r) >> 1, k = plane[mid];

    double dist = pos[k] - phs[mid].pos[k];
    double res = (phs[mid].pos - pos).mod2();
    if (res < q.top().first)
    {
        if ((int) q.size() == samples) q.pop();
        q.push(make_pair(res, mid));
    }

    if (dist < 0)
    {
        findNearestPhotons(l, mid);
        if (dist * dist < q.top().first)
            findNearestPhotons(mid + 1, r);
    }
    else
    {
        findNearestPhotons(mid + 1, r);
        if (dist * dist < q.top().first)
            findNearestPhotons(l, mid);
    }
}
