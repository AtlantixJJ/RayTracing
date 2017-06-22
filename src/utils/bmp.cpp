#include "utils/bmp.h"
#include "utils/config.h"
#include "common/const.h"

#include <cstring>

Bmp::Bmp(int w, int h, const Color& background)
    : _w(w), _h(h),
      _file_name("")
{
    _data = new BmpColor*[w];
    for (int i = 0; i < _w; i++)
    {
        _data[i] = new BmpColor[h];
        for (int j = 0; j < _h; j++) setColor(i, j, background);
    }

    memset(&_bf, 0, sizeof(_bf));
    memset(&_bi, 0, sizeof(_bi));

    _bf.bfType = 0x4D42;
    _bf.bfSize = (_w * 3 + _w % 4) * _h + 54;
    _bf.bfOffBits = 54;

    _bi.biSize = 40;
    _bi.biWidth = _w;
    _bi.biHeight = _h;
    _bi.biPlanes = 1;
    _bi.biBitCount = 24;
}

Bmp::Bmp(const std::string& file)
    : _w(0), _h(0),
      _file_name(file)
{
    FILE* f = fopen(file.c_str(), "rb");
    if (!f)
    {
        std::cerr << "ERROR: No such BMP file '" + file + "'" << std::endl;
        return;
    }

    fread(&_bf, 1, sizeof(BITMAPFILEHEADER), f);
    fread(&_bi, 1, sizeof(BITMAPINFOHEADER), f);

    _w = _bi.biWidth, _h = _bi.biHeight;
    _data = new BmpColor*[_w];
    for (int i = 0; i < _w; i++) _data[i] = new BmpColor[_h];

    for (int j = _h - 1; j >= 0; j--)
    {
        for (int i = 0; i < _w; i++)
        {
            fread(&_data[i][j].b, 1, sizeof(byte), f);
            fread(&_data[i][j].g, 1, sizeof(byte), f);
            fread(&_data[i][j].r, 1, sizeof(byte), f);
        }
        for (int i = 0; i < _w % 4; i++) fgetc(f);
    }

    fclose(f);
}

Bmp::~Bmp()
{
    for (int i = 0; i < _w; i++) delete[] _data[i];
    delete[] _data;
}

Color Bmp::getColor(double u, double v) const
{
    u *= _w - 1, v *= _h - 1;
    if (Config::enable_texture_filter) // 双线性插值
    {
        int u1 = floor(u + Const::EPS), v1 = floor(v + Const::EPS),
            u2 = u1 + 1, v2 = v1 + 1;
        double ru = u2 - u, rv = v2 - v;
        if (u1 < 0) u1 = _w - 1;
        if (v1 < 0) v1 = _h - 1;
        if (u2 == _w) u2 = 0;
        if (v2 == _h) v2 = 0;
        return getColor(u1, v1) * (ru * rv) + getColor(u1, v2) * (ru * (1 - rv)) +
               getColor(u2, v1) * ((1 - ru) * rv) + getColor(u2, v2) * ((1 - ru) * (1 - rv));
    }
    else
        return getColor(int(u + 0.5), int(v + 0.5));
}

void Bmp::save(const std::string& file) const
{
    FILE* f = fopen(file.c_str(), "wb");

    fwrite(&_bf, 1, sizeof(BITMAPFILEHEADER), f);
    fwrite(&_bi, 1, sizeof(BITMAPINFOHEADER), f);
    for (int j = _h - 1; j >= 0; j--)
    {
        for (int i = 0; i < _w; i++)
        {
            fwrite(&_data[i][j].b, 1, sizeof(byte), f);
            fwrite(&_data[i][j].g, 1, sizeof(byte), f);
            fwrite(&_data[i][j].r, 1, sizeof(byte), f);
        }
        for (int i = 0; i < _w % 4; i++) fputc(0, f);
    }

    fclose(f);
}
