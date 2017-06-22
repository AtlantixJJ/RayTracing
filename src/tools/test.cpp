#include "omp.h"
#include <stdio.h>

int main()
{
    int i;
    #pragma omp parallel for //num_threads(2)
    for(i = 0 ; i < 5 ;i++)
        printf("%d\n",i);
}