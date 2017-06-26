#ifndef BMP_H
#define BMP_H

#include "common/common.h"

#include <string>

class Bmp
{
public:
    Bmp(int w, int h, const Color& background = Color());
    Bmp(const std::string& file);
    ~Bmp();

    int getW() const { return _w; }
    int getH() const { return _h; }

    // 直接获取像素点颜色
    Color getColor(int x, int y) const
    {
        return Color(_data[x][y].r, _data[x][y].g, _data[x][y].b) / 255;
    }

    // 根据像素位置计算颜色
    Color getColor(double u, double v) const;

    void setColor(int x, int y, const Color& color)
    {
        _data[x][y] = BmpColor(color.r * 255 + 0.5, color.g * 255 + 0.5, color.b * 255 + 0.5);
    }

    void save2Json(const std::string& file) const;
    std::string getFilename() const { return _file_name; }

private:
    typedef unsigned char byte;
    typedef unsigned short word;
    typedef unsigned int dword;

#pragma pack(push, 1)
    struct BITMAPFILEHEADER
    {
        word bfType;
        dword bfSize;
        word bfReserved1;
        word bfReserved2;
        dword bfOffBits;
    };
    struct BITMAPINFOHEADER
    {
        dword biSize;
        dword biWidth;
        dword biHeight;
        word biPlanes;
        word biBitCount;
        dword biCompression;
        dword biSizeImage;
        dword biXPelsPerMeter;
        dword biYPelsPerMeter;
        dword biClrUsed;
        dword biClrImportant;
    };
#pragma pack(pop)
    struct BmpColor
    {
        byte r, g, b;
        BmpColor() {}
        BmpColor(byte r, byte g, byte b)
            : r(r), g(g), b(b) {}
    };

    int _w, _h;
    BITMAPFILEHEADER _bf;
    BITMAPINFOHEADER _bi;
    BmpColor** _data;
    std::string _file_name;
};

#endif // BMP_H
