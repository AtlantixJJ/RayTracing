#ifndef CONST_H
#define CONST_H

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG -1

namespace Const
{
const double EPS = 1e-6;
const double PI = acos(-1.0);

const double MIN_WEIGHT = 0.05;
const int MAX_DEPTH = 20;
const int SPEC_POWER = 50;

inline double randDouble()
{
    return 1.0 * rand() / RAND_MAX;
}
}

#endif // CONST_H
