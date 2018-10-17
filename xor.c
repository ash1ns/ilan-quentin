#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "matrix.h"

int main()
{
    //double hidden[2];
    //double output[1];
    
    double a[] = {1.0, 2.0, 3.0, 4.0};
    double b[] = {3.0, 4.0};
    double res[] = {0, 0};

    multiply(res, 2, 1, a, 2, 2, b, 2, 1);
    printMatrix(res, 2, 1);
    function(res, 2, 1);
    printMatrix(res, 2, 1);

    return EXIT_SUCCESS;
}
