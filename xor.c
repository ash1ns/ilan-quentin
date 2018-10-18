#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "matrix.h"

float inputs[] = {0, 1};
float hidden[2];
float output[1];
float target[] = {1};

float weights_ih[4];
float weights_ho[2];

float bias_hidden[2];
float bias_output[1];

float error_output[1];
float error_hidden[2];

float learning_rate = 0.15;

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
    multiply(hidden,2,1,weights_ih,2,2,inputs,2,1);
    add(hidden,2,1,hidden,2,1,bias_hidden,2,1);
    sigmoid_arr(hidden,2,1);
    
    //from hidden to output
    multiply(output,1,1,weights_ho,1,2,hidden,2,1);
    add(output,1,1,output,1,1,bias_output,1,1);
    sigmoid_arr(output,1,1);
}

void get_error()
{
    float weights_ho_tr[2];
    //(calcul of output error : e1)
    subtract(error_output,1,1,target,1,1,output,1,1);
    
    //(calcul of hidden layers errors : eh1 and eh2)
    transpose(weights_ho_tr,2,1,weights_ho,1,2);
    multiply(error_hidden,2,1,weights_ho_tr,2,1,error_output,1,1);
}

void feed_backward()
{
    float delta_weight_ho[2];
    //float delta_weight_ih[4];
    float temp[1]; 
    float temp_derivative[1];
    float one_col_matrix[] = {1};
    float hidden_tr[2]; 
    multiplyByScalar(learning_rate,temp,1,1,error_output,1,1); // temp <- learning_rate*error_output
    subtract(temp_derivative,1,1,one_col_matrix,1,1,output,1,1); // temp_derivative <- 1 - output
    elementWise(temp_derivative,1,1,output,1,1,temp_derivative,1,1); //temp_derivative <- el_wise(output,temp_derivative)
    elementWise(temp,1,1,temp,1,1,temp_derivative,1,1); // temp <- el_wise(temp, temp_derivative)
    transpose(hidden_tr,1,2,hidden,2,1);
    multiply(delta_weight_ho,1,2,temp,1,1,hidden_tr,1,2); // delta_weight_ho <- temp * hidden_tr
    printMatrix(weights_ho,1,2);
    add(weights_ho,1,2,weights_ho,1,2,delta_weight_ho,1,2); // weights_ho <- delta_weight_ho = weights_ho
    printMatrix(weights_ho,1,2);
}

int main()
{
    init();
    feed_foward();
    get_error();
    feed_backward();
    return EXIT_SUCCESS;
}
