#include "utils/bmp.h"
#include "utils/config.h"
#include "common/const.h"
#include "common/common.h"
#include "env/camera.h"

#include <algorithm>

Camera::Camera(const Vector3& eye, const Vector3& lookAt, const Vector3& up, int w, int h, double fovy, double aper)
    : _eye(eye), _look_at(lookAt), _dir((lookAt - eye).normalize()), _up(up),
      _w(w), _h(h), _fovy(fovy * Const::PI / 180), _aperture(aper), _focal_len((lookAt - eye).mod())
{
    _init();
}

Camera::Camera(const Json::Value& camera)
    : _eye(camera["eye"]), _look_at(camera["look_at"]), _dir((_look_at - _eye).normalize()), _up(camera["up"]),
      _w(camera["w"].asInt()), _h(camera["h"].asInt()),
      _fovy(camera["fovy"].asDouble() * Const::PI / 180),
      _aperture(camera["aperture"].asDouble()),
      _focal_len(camera["focal_len"].isDouble() ? camera["focal_len"].asDouble() : (_look_at - _eye).mod())
{
    _init();
}

Camera::~Camera()
{
    if(_color){
        for (int i = 0; i < _w; i++){
            if(_color[i]) delete[] _color[i];
            _color[i] = nullptr;
        }
        delete[] _color;
        _color = nullptr;
    }
}

bool Camera::isDOF() const
{
    return _aperture > 0 && Config::dof > 0;
}

Ray Camera::emit(double x, double y) const
{
    return Ray(_eye, _dir + _dw * (2.0 * x / _w - 1) + _dh * (2.0 * y / _h - 1));
}

Ray Camera::dofEmit(double x, double y) const
{
    Vector3 focal = _eye + emit(x, y).dir.normalize() * _focal_len;
    double dx, dy;
    for (;;)
    {
        dx = randDouble * 2 - 1;
        dy = randDouble * 2 - 1;
        if (dx * dx + dy * dy <= 1) break;
    }
    Vector3 start = _eye + _dw.normalize() * _aperture * dx + _dh.normalize() * _aperture * dy;
    
    return Ray(start, focal-start);
}

void Camera::print(const std::string& file) const
{
    Bmp* film = new Bmp(_w, _h);
    for (int i = 0; i < _w; i++)
        for (int j = 0; j < _h; j++) film->setColor(i, j, _color[i][j].confine());
    film->save2Json(file);
    delete film;
}

Bmp* Camera::copyf() const
{
    Bmp* bmp = new Bmp(_w, _h);
    for (int i = 0; i < _w; i++)
        for (int j = 0; j < _h; j++) bmp->setColor(i, j, getColor(i, j));
    return bmp;
}

void Camera::setf(const Bmp* film)
{
    for (int i = 0; i < _w; i++)
        for (int j = 0; j < _h; j++) setColor(i, j, film->getColor(i, j));
}

void Camera::_init()
{
    _dw = (_dir * _up).normalize() * tan(_fovy / 2) * (1.0 * _w / _h);
    _dh = (_dir * _dw).normalize() * tan(_fovy / 2);
    _color = new Color*[_w];
    for (int i = 0; i < _w; i++) _color[i] = new Color[_h];
}

Json::Value Camera::toJson() const
{
    Json::Value camera;
    camera["eye"] = _eye.toJson();
    camera["look_at"] = _look_at.toJson();
    camera["up"] = _up.toJson();
    camera["w"] = _w;
    camera["h"] = _h;
    camera["fovy"] = _fovy * 180 / Const::PI;
    camera["aperture"] = _aperture;
    camera["focal_len"] = _focal_len;
    if (_aperture > 0)
    {
        camera["aperture"] = _aperture;
        camera["focal_len"] = _focal_len;
    }
    return camera;
}
