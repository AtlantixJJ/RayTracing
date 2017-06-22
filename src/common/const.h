#ifndef CONST_H
#define CONST_H

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef unsigned long long ID;

namespace Const
{

constexpr double EPS = 1e-6;
constexpr double PI = acos(-1.0);
constexpr int HASH_KEY = 2791371;
constexpr int OMPTHREADS = 4;


#define randDouble ( 1.0 * rand() / 2147483647.0 )

#define randUInt ( rand() )

#define randID ( (rand() << 31) | rand() )

}

#endif // CONST_H
