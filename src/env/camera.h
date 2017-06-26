#ifndef CAMERA_H
#define CAMERA_H

#include "common/common.h"
#include "math/vector3.h"

#include <string>
#include <vector>

class Bmp;

class Camera
{
public:
    Camera(const Vector3& eye, const Vector3& lookAt, const Vector3& up, int w, int h, double fovy, double aper = 0);
    Camera(const Json::Value& camera);
    ~Camera();

    int getW() const { return _w; }
    int getH() const { return _h; }
    Vector3 getEye() const { return _eye; }

    bool isDOF() const;

    Ray emit(double x, double y) const;

    Ray dofEmit(double x, double y) const;

    Color getColor(int x, int y) const
    {
        return 0 <= x && x < _w && 0 <= y && y < _h ? _color[x][y] : Color();
    }

    void setColor(int x, int y, const Color& color) { _color[x][y] = color; }

    void print(const std::string& file) const;

    Bmp* copyf() const;

    void setf(const Bmp* film);

    Json::Value toJson() const;
protected:
    void _init();
    
private:
    Vector3 _eye, _look_at, _dir, _up;
    int _w, _h;                      
    double _fovy; 
    double _aperture, _focal_len;     
    Vector3 _dw, _dh;      
    Color** _color;   


};

#endif // CAMERA_H
