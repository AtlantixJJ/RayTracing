#include "common/const.h"
#include "engine/photonmap/photontracer.h"
#include "light/light.h"
#include "object/material.h"
#include "object/object.h"
#include "scene/scene.h"

void PhotonTracer::buildPhotonMap()
{
    clear();
    map = new StatMap();
    double power = 0, lp = 0;
    Photon ph;

    for( auto l = scene->lightsBegin(); l != scene -> lightsEnd(); l++)
        power += (*l)->getColor().power();
    power /= gconf->photon_number;

    for( auto l = scene->lightsBegin(); l != scene->lightsEnd() ; l++)
    {
        lp = (*l)->getColor().power();
        for (; lp > 0; lp -= power)
        {
            ph = (*l)->emitPhoton(power);
            tracePhoton(ph, 1, false);
        }
    }
    map->buildMap(true);
}

void PhotonTracer::tracePhoton(Photon& photon, int depth, bool isInternal)
{
    if( depth > gconf->photon_tracing_max_depth) return;
    Collision coll = scene->findNearestCollision(photon.pos,
        photon.dir);
    
    const Object *obj;
    const Material *mt;
    Color c;
    Color uni(1,1,1);
    Color absorb;
    double f = 0;
    double pd,ps,pt;

    if(coll.isHit() && coll.atObject())
    {
        photon.pos = coll.p;
        obj = coll.object;
        mt = obj->getMaterial();

        if(mt->diff > Const::EPS)
        {
            map->addPhoton(photon);
        }

        c = mt->color * obj->getTextureColor(coll);
        uni = Color(1,1,1);
        if(isInternal)
        {
            absorb = (mt->absorb_color * (-coll.dist)).exp();
            c *= absorb;
            uni *= absorb;
        }
        f = Const::randDouble();
        pd = (mt->diff + mt->spec) * c.power();
        if( f < pd) // diffusion
        {
            photon.dir = coll.n.diffuse();
            photon.pow *= c / c.power();
            tracePhoton(photon, depth+1, isInternal);
            return;
        }
        ps = mt->refl * c.power();
        if( f < pd + ps) // reflection
        {
            photon.dir = coll.ray_dir.reflect(coll.n);
            photon.pow += c / c.power();
            tracePhoton(photon, depth+1, isInternal);
            return;
        }
        pt = mt->refr * uni.power();
        double n = mt->rindex;
        if( f < pd + ps + pt) // refraction : change internal state
        {
            if(isInternal) n = 1/n;
            photon.dir = coll.ray_dir.refract(coll.n,n);
            photon.pow *= uni / uni.power();
            tracePhoton(photon, depth+1, !isInternal);
        }
    }
}