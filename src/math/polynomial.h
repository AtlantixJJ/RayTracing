#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
/**
*   Considering using degree-3 Bezier Cure, the equation should be 
* no more than degree 6.
**/
struct Polynomial
{
public:
    /// limited to degree 7
    Polynomial(const long double a[7]);

    long double F(long double x); //eval by fast algorithm

    void printInfo()const{
        for(int i=0;i<_roots.size();i++)
            printf("%d ",_roots[i]);
        printf("\n");
    }
    long double D(long double x); ///< get sturm value

    int rootNum(long double l, long double r);
    std::vector<double> findAllRoots(double l, double r);

private:
    long double _a[7], _s[7][7];
    std::vector<double> _roots;

    void _init();
    bool _findOneRoot(long double l, long double r, long double& x);
    void _findAllRoots(long double l, long double r);
};

#endif // POLYNOMIAL6_H
