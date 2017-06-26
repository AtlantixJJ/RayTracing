#include "utils/config.h"
#include "common/const.h"
#include "math/polynomial.h"

#include <cstring>
#include <iostream>

const long double EPS = 1e-10;

Polynomial::Polynomial(const long double a[7])
{
    for (int i = 0; i < 7; i++) _a[i] = a[i];
    _init();
}

long double Polynomial::F(long double x)
{
    long double f = 0;
    for (int i = 6; i >= 0; i--) f = f * x + _a[i];
    return f;
}

long double Polynomial::D(long double x)
{
    long double f = 0;
    for (int i = 5; i >= 0; i--) f = f * x + _s[1][i];
    return f;
}

std::vector<double> Polynomial::findAllRoots(double l, double r)
{
    _roots.clear();
    _findAllRoots(l, r);
    if (abs(F(l)) < 1e-14) _roots.push_back(l);
    if (abs(F(r)) < 1e-14) _roots.push_back(r);
    return _roots;
}

int Polynomial::rootNum(long double l, long double r)
{
    int s = 0;
    long double f_l, f_r, g_l = 0, g_r = 0;

    if (r - l < Const::EPS) return 0;
    for (int i = 0; i < 7; i++){
        if (_s[i][6 - i] == 0) break;

        f_l = f_r = 0;
        for (int j = 6 - i; j >= 0; j--){
            f_l = f_l * l + _s[i][j];
            f_r = f_r * r + _s[i][j];
        }
        if (f_l != 0)
        {
            if (f_l * g_l < 0) s++;
            g_l = f_l;
        }
        if (f_r != 0)
        {
            if (f_r * g_r < 0) s--;
            g_r = f_r;
        }
    }
    return s;
}

void Polynomial::_init()
{
    memset(_s, 0, sizeof(_s));
    int i,j;

    for ( i = 0; i < 7; i++){
        _s[0][i] = _a[i];
        if (i < 6) _s[1][i] = (i + 1) * _a[i + 1];
    }
    for ( i = 2; i < 7; i++){
        long double a = _s[i - 2][8 - i] / _s[i - 1][7 - i], b = (_s[i - 2][7 - i] - a * _s[i - 1][6 - i]) / _s[i - 1][7 - i];
        for ( j = 0; j < 7 - i; j++)
            _s[i][j] = (j ? a * _s[i - 1][j - 1] : 0) + b * _s[i - 1][j] - _s[i - 2][j];
        
        if (_s[i][6 - i] == 0){
            for ( j = 0; j < 7 - i; j++) _s[i][j] = 0;
            break;
        }
    }
    //for(i = 0 ; i < 7 ; i ++)
    //  printf("%d ",_s[i]);
}

bool Polynomial::_findOneRoot(long double l, long double r, long double& x)
{
    x = l;
    for (int i = 0; i < Config::newton_iters; i++)
    {
        long double f = F(x), d = D(x), dx;
        if (abs(f) < 1e-14) return l < x - EPS && x < r - EPS;
        if (abs(d) < EPS) break;
        dx = f / d, x -= dx;
        if (abs(dx) < EPS) break;
    }
    return abs(x) < 1e-14 && l < x - EPS && x < r - EPS;
}

void Polynomial::_findAllRoots(long double l, long double r)
{
    if (r - l < EPS)
    {
        if (abs(F(l)) < 1e-14) _roots.push_back(l);
        return;
    }
    int c = rootNum(l, r);
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
