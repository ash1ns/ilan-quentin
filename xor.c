#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "matrix.h"
#include <time.h>

float inputs[2];
float hidden[2];
float output[1];
float target[1];

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

void feed_forward()
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
    get_error();
    float delta_weight_ho[2];
    float delta_weight_ih[4];
    float gradient_ho[1];
    float gradient_ih[2];
    float gradient_derivative_ho[1];
    float gradient_derivative_ih[2];
    /****   * matrix product
            . matrix element wise
            + matrix addition
    ****/
    
    //Calculate the delta_weights_ho = (learning_rate * error_output) . (ouput . (1 - output)) * hidden_tr
    multiplyByScalar(learning_rate,gradient_ho,1,1,error_output,1,1); // gradient_ho <- learning_rate * error_output
    float one_col_matrix_ho[] = {1};
    subtract(gradient_derivative_ho,1,1,one_col_matrix_ho,1,1,output,1,1); // gradient_derivative <- 1 - output
    elementWise(gradient_derivative_ho,1,1,output,1,1,gradient_derivative_ho,1,1); //gradient_derivative_ho <- output . gradient_derivative_ho
    elementWise(gradient_ho,1,1,gradient_ho,1,1,gradient_derivative_ho,1,1); // gradient_ho <- gradient_ho . gradient_derivative_ho
    float hidden_tr[2];//output transposed
    transpose(hidden_tr,1,2,hidden,2,1);
    multiply(delta_weight_ho,1,2,gradient_ho,1,1,hidden_tr,1,2); // delta_weight_ho <- gradient_ho * hidden_tr
    
    //Update weights_ho, bias_ho (bias_output)
    add(weights_ho,1,2,weights_ho,1,2,delta_weight_ho,1,2); // weights_ho <- delta_weight_ho + weights_ho
    add(bias_output,1,1,bias_output,1,1,gradient_ho,1,1);

    //Calculate the delta_weights_ih = (learning_rate * error_hidden) . (hidden . (1 - hidden)) * input_tr
    multiplyByScalar(learning_rate,gradient_ih,2,1,error_hidden,2,1); // gradient)_ih <- learning_rate * error_hidden
    float one_col_matrix_ih[] = {1, 1};
    subtract(gradient_derivative_ih,2,1,one_col_matrix_ih,2,1,hidden,2,1); // gradient_derivative_ih <- 1 - hidden
    elementWise(gradient_derivative_ih,2,1,hidden,2,1,gradient_derivative_ih,2,1); //gradient_derivative_ih <- hidden . gradient_derivative_ih
    elementWise(gradient_ih,2,1,gradient_ih,2,1,gradient_derivative_ih,2,1); // gradient_ih <- gradient_ih . gradient_derivative_ih
    float inputs_tr[2];//input transposed 
    transpose(inputs_tr,1,2,inputs,2,1);
    multiply(delta_weight_ih,2,2,gradient_ih,2,1,inputs_tr,1,2); // delta_weight_ih <- gradient_ih * inputs_tr
    
    //Update of weights_ih, bias_ih (bias_hidden)
    add(weights_ih,2,2,weights_ih,2,2,delta_weight_ih,2,2); // weights_ih <- delta_weight_ih + weights_ih
    add(bias_hidden,2,1,bias_hidden,2,1,gradient_ih,2,1);
    
}

struct training_data 
{
    float inputs[2];
    float target[1];
}; 

struct training_data data0;
struct training_data data1;
struct training_data data2;
struct training_data data3;
 
void choose_inputs_target()
{
    data0.inputs[0] = 0; 
    data0.inputs[1] = 0; 
    data0.target[0] = 0;

    data1.inputs[0] = 0; 
    data1.inputs[1] = 1; 
    data1.target[0] = 1;
    
    data2.inputs[1] = 1; 
    data2.inputs[1] = 0; 
    data2.target[0] = 1;
    
    data3.inputs[1] = 1; 
    data3.inputs[1] = 1; 
    data3.target[0] = 0;
    
    srand(time(NULL));    
    
    int rdm = rand()%5;
    switch (rdm)
    {
        case 0:
            copy(inputs,2,1,data0.inputs,2,1);
            copy(target,1,1,data0.target,1,1);
            break;
        case 1:
            copy(inputs,2,1,data1.inputs,2,1);
            copy(target,1,1,data1.target,1,1);
            break;
        case 2:
            copy(inputs,2,1,data2.inputs,2,1);
            copy(target,1,1,data2.target,1,1);
            break;
        case 3:
            copy(inputs,2,1,data3.inputs,2,1);
            copy(target,1,1,data3.target,1,1);
            break;
    }
}

void train()
{
    unsigned long time;
    puts("How many iterations ?");
    scanf("%lu",&time);
    for (unsigned long ite = 0; ite < time; ite++)
    {
        choose_inputs_target(); //input & target initialize
        feed_forward();
        feed_backward();
        printf("ite : %lu || error : ",ite);
        printMatrix(error_output,1,1);
    }
}

int main()
{
    init();
    train();
    int arg1;
    int arg2;
    puts("arg1?");
    scanf("%d",&arg1);
    puts("arg2?");
    scanf("%d",&arg2);
    inputs[0] = (float)arg1;
    inputs[1] = (float)arg2;
    feed_forward();
    printMatrix(output,1,1);
    return EXIT_SUCCESS;
}
