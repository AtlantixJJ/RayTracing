#ifndef POLYNOMIAL6_H
#define POLYNOMIAL6_H

#include <vector>

struct Polynomial6
{
public:
    Polynomial6(const long double a[7]);

    long double F(long double x);
    long double dF(long double x);
    int rootCount(long double l, long double r);
    std::vector<double> findAllRoots(double l, double r);

private:
    long double _a[7], _sturm[7][7];
    std::vector<double> _roots;

    void _init();
    bool _findOneRoot(long double l, long double r, long double& x);
    void _findAllRoots(long double l, long double r);
};

#endif // POLYNOMIAL6_H
