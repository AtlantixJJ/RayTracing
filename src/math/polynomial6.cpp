#include "utils/config.h"
#include "common/const.h"
#include "math/polynomial6.h"

#include <cstring>
#include <iostream>

const long double EPS = 1e-10;

Polynomial6::Polynomial6(const long double a[7])
{
    for (int i = 0; i < 7; i++) _a[i] = a[i];
    _init();
}

long double Polynomial6::F(long double x)
{
    long double f = 0;
    for (int i = 6; i >= 0; i--) f = f * x + _a[i];
    return f;
}

long double Polynomial6::dF(long double x)
{
    long double f = 0;
    for (int i = 5; i >= 0; i--) f = f * x + _sturm[1][i];
    return f;
}

std::vector<double> Polynomial6::findAllRoots(double l, double r)
{
    _roots.clear();
    _findAllRoots(l, r);
    if (abs(F(l)) < 1e-14) _roots.push_back(l);
    if (abs(F(r)) < 1e-14) _roots.push_back(r);
    return _roots;
}

int Polynomial6::rootCount(long double l, long double r)
{
    int s = 0;
    long double fl, fr, gl = 0, gr = 0;
    if (r - l < EPS) return 0;
    for (int i = 0; i < 7; i++)
    {
        if (_sturm[i][6 - i] == 0) break;
        fl = fr = 0;
        for (int j = 6 - i; j >= 0; j--)
        {
            fl = fl * l + _sturm[i][j];
            fr = fr * r + _sturm[i][j];
        }
        if (fl != 0)
        {
            if (fl * gl < 0) s++;
            gl = fl;
        }
        if (fr != 0)
        {
            if (fr * gr < 0) s--;
            gr = fr;
        }
    }
    return s;
}

void Polynomial6::_init()
{
    memset(_sturm, 0, sizeof(_sturm));
    for (int i = 0; i < 7; i++)
    {
        _sturm[0][i] = _a[i];
        if (i < 6) _sturm[1][i] = (i + 1) * _a[i + 1];
    }
    for (int i = 2; i < 7; i++)
    {
        long double a = _sturm[i - 2][8 - i] / _sturm[i - 1][7 - i],
                    b = (_sturm[i - 2][7 - i] - a * _sturm[i - 1][6 - i]) / _sturm[i - 1][7 - i];
        for (int j = 0; j < 7 - i; j++)
            _sturm[i][j] = (j ? a * _sturm[i - 1][j - 1] : 0) + b * _sturm[i - 1][j] - _sturm[i - 2][j];
        if (_sturm[i][6 - i] == 0)
        {
            for (int j = 0; j < 7 - i; j++) _sturm[i][j] = 0;
            break;
        }
    }
}

bool Polynomial6::_findOneRoot(long double l, long double r, long double& x)
{
    x = l;
    for (int i = 0; i < Config::newton_iters; i++)
    {
        long double f = F(x), d = dF(x), dx;
        if (abs(f) < 1e-14) return l < x - EPS && x < r - EPS;
        if (abs(d) < EPS) break;
        dx = f / d, x -= dx;
        if (abs(dx) < EPS) break;
    }
    return abs(x) < 1e-14 && l < x - EPS && x < r - EPS;
}

void Polynomial6::_findAllRoots(long double l, long double r)
{
    if (r - l < EPS)
    {
        if (abs(F(l)) < 1e-14) _roots.push_back(l);
        return;
    }
    int c = rootCount(l, r);
    if (c == 0)
        return;
    else if (c == 1)
    {
        long double x;
        if (_findOneRoot(l, r, x))
        {
            _roots.push_back(x);
            return;
        }
    }
    long double m = (l + r) / 2;
    _findAllRoots(l, m);
    _findAllRoots(m, r);
}
