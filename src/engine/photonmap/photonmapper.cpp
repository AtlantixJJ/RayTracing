#include "engine/photonmap/photonmapper.h"

void PhotonMapper::run(const std::string& outFile)
{
    if (!scene) return;

    cout << "Building photon map..." << endl;
    PhotonTracer* tracer = new PhotonTracer(scene);
    //map = tracer->getPhotonMap();
    //delete tracer;
    //RayTracer::run(outFile);
    //delete map;
}