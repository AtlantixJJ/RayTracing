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
    double power = 0;

    for( auto l = scene->lightsBegin(); l != scene -> lightsEnd(); l++)
        power += (*l)->getColor().power();
    power /= gconf->photon_number;

    //map->buildMap();
}