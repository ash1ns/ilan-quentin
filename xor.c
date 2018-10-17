#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "matrix.h"

float inputs[] = {0, 1};
float hidden[2];
float output[1];

float weights_ih[4];
float weights_ho[2];

float bias_hidden[2];
float bias_output[1];

void init()
{
    
    initMatrix(weights_ih,2,2); //weigths inputs -> hidden
    initMatrix(weights_ho,1,2); //weigths hidden -> output
    initMatrix(bias_hidden,2,1);
    initMatrix(bias_output,1,1);
}

void feed_foward()
{
    //from inputs to hidden
    printMatrix(hidden,2,1);
    printf("\n");
    multiply(hidden,2,1,weights_ih,2,2,inputs,2,1);
    puts("mult weights_ih inputs");
    printMatrix(hidden,2,1);
    printf("\n");
    add(hidden,2,1,bias_hidden,2,1);
    puts("add hidden bias_hidden");
    printMatrix(hidden,2,1);
    printf("\n");
    sigmoid_arr(hidden,2,1);
    puts("sigmoid hidden");
    printMatrix(hidden,2,1);
    
    //from hidden to output
    printf("\n");
    multiply(output,1,1,weights_ho,1,2,hidden,2,1);
    //ERROR
    puts("mult weights_ho hidden");
    printMatrix(output,1,1);
    printf("\n");
    add(output,1,1,bias_output,1,1);
    puts("add output bias_output");
    printMatrix(output,1,1);
    printf("\n");
    sigmoid_arr(output,1,1);
    puts("sigmoid output");
    printMatrix(output,1,1);

}

int main()
{
    
    init();
    feed_foward();
    printf("MAKE OK");
    return EXIT_SUCCESS;
}





