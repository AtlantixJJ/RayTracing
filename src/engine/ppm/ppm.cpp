#include "utils/config.h"
#include "common/const.h"
#include "engine/photonmapper/photontracer.h"
#include "engine/ppm/hitpointmap.h"
#include "engine/ppm/ppm.h"
#include "env/camera.h"

void PPM::run(const std::string& outFile)
{
    if (!_scene) return;
    _map = new HitPointMap();

    _find_edge = true;
    RayTracer::run(outFile);
    _find_edge = false;

    for (int i = 0; i < _w; i++)
        for (int j = 0; j < _h; j++)
        {
            _cur_x = i, _cur_y = j;
            _camera->setColor(i, j, _DOFTracing(i, j));
        }

    _map->build();
    Bmp* film = _camera->copyFilm();

    printf("PPM Iteration Start...\n");
    PhotonTracer* tracer = new PhotonTracer(_scene, _map);
    for (int i = 0, tot = 0; i < Config::ppm_iteration_depth; i++)
    {
        printf("Round [%d]\n", i);
        tracer->emitPhotons(Config::ppm_photo_number);
        _map->update();
        tot += Config::ppm_photo_number;

        _camera->setFilm(film);
        for (auto p = _map->hitPointBegin(); p != _map->hitPointEnd(); p++)
        {
            Color color = _camera->getColor(p->x, p->y) + p->color * p->flux * (1 / Const::PI / p->r2 / tot);
            _camera->setColor(p->x, p->y, color);
        }
        _camera->print(outFile.c_str());
    }

    delete film;
    delete tracer;
    delete _map;
}

Color PPM::_localIllumination(const Intersection& coll, const Material* material, const Color& factor) const
{
    if (_find_edge)
        return RayTracer::_localIllumination(coll, material, factor);

    HitPoint point;
    point.pos = coll.p;
    point.n = coll.n;
    point.dir = coll.ray.dir;
    point.material = material;
    point.color = material->color * coll.getObject()->getTextureColor(coll) * factor * material->diff;
    point.r2 = Config::ppm_search_rad;
    point.x = _cur_x;
    point.y = _cur_y;
    _map->addHitPoint(point);

    if (Config::photon_map_only)
        return Color();
    else
        return RayTracer::_localIllumination(coll, material, factor);
}
