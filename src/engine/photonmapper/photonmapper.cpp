#include "utils/config.h"
#include "common/const.h"
#include "engine/photonmapper/photonmap.h"
#include "engine/photonmapper/photonmapper.h"
#include "engine/photonmapper/photontracer.h"
#include "env/camera.h"

void PhotonMapper::run(const std::string& outFile)
{
    if (!_scene) return;

    cout << "Building photon map..." << endl;
    _map = new PhotonMap();
    PhotonTracer* tracer = new PhotonTracer(_scene, _map);
    tracer->emitPhotons(Config::photo_number);
    _map->build();
    RayTracer::run(outFile);
    delete tracer;
    delete _map;
}

Color PhotonMapper::_localIllumination(const Intersection& coll,
    const Material* material, const Color& factor,
    int fx, int fy) const
{
    Color color = material->color * coll.getObject()->getTextureColor(coll),
          ret = color * _map->getIrradiance(coll, Config::photo_sample) * (material->diff / Config::photo_number) * factor;
    if (Config::photon_map_only)
        return ret + color * _scene->getAmbientLightColor() * factor * material->diff;
    else
        return ret + RayTracer::_localIllumination(coll, material, factor);
}
