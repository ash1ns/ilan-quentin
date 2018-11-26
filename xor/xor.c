#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "matrix.h"
#include <time.h>
#include "file.h"

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

float learning_rate = 0.2;

void save_weights_bias()
{
    save_matrix("xor/save_weights_bias/save_weights_ih.data", weights_ih, 
    sizeof(weights_ih) / sizeof(float));
    save_matrix("xor/save_weights_bias/save_weights_ho.data", weights_ho, 
    sizeof(weights_ho) / sizeof(float));
    save_matrix("xor/save_weights_bias/save_bias_hidden.data", bias_hidden,
    sizeof(bias_hidden) / sizeof(float));
    save_matrix("xor/save_weights_bias/save_bias_output.data", bias_output,
    sizeof(bias_output) / sizeof(float)); 
}

void get_weights_bias()
{
    //Get weights_ih
    float *buffer = malloc(sizeof(weights_ih));
    get_matrix(buffer, "xor/save_weights_bias/save_weights_ih.data", 
    sizeof(weights_ih) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ih) / sizeof(float); i++)
    {
        weights_ih[i] = *(buffer + i);
    }
    free(buffer);

    //Get weight_ho
    buffer = malloc(sizeof(weights_ho));
    get_matrix(buffer, "xor/save_weights_bias/save_weights_ho.data", 
    sizeof(weights_ho) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ho) / sizeof(float); i++)
    {
        weights_ho[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_hidden
    buffer = malloc(sizeof(bias_hidden));
    get_matrix(buffer, "xor/save_weights_bias/save_bias_hidden.data", 
    sizeof(bias_hidden) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_hidden) / sizeof(float); i++)
    {
        bias_hidden[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_output
    buffer = malloc(sizeof(bias_output));
    get_matrix(buffer, "xor/save_weights_bias/save_bias_output.data", 
    sizeof(bias_output) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_output) / sizeof(float); i++)
    {
        bias_output[i] = *(buffer + i);
    }
    free(buffer);
}

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
    //calcul of output error : error_output = target - output
    subtract(error_output,1,1,target,1,1,output,1,1);
    
    //(calcul of hidden layers errors : error_hidden = weights_ho_tr * 
    //error_output
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
    
    //Calculate the delta_weights_ho = (learning_rate * error_output) . 
    //(ouput . (1 - output)) * hidden_tr
    // gradient_ho <- learning_rate * error_output
    multiplyByScalar(learning_rate,gradient_ho,1,1,error_output,1,1); 
    float one_col_matrix_ho[] = {1};
    // gradient_derivative <- 1 - output
    subtract(gradient_derivative_ho,1,1,one_col_matrix_ho,1,1,output,1,1); 
    //gradient_derivative_ho <- output . gradient_derivative_ho
    elementWise(gradient_derivative_ho,1,1,output,1,1,gradient_derivative_ho,1,
    1); 
    // gradient_ho <- gradient_ho . gradient_derivative_ho
    elementWise(gradient_ho,1,1,gradient_ho,1,1,gradient_derivative_ho,1,1); 
    float hidden_tr[2];//output transposed
    transpose(hidden_tr,1,2,hidden,2,1);
    // delta_weight_ho <- gradient_ho * hidden_tr
    multiply(delta_weight_ho,1,2,gradient_ho,1,1,hidden_tr,1,2); 
    
    //Update weights_ho, bias_ho (bias_output)
    // weights_ho <- delta_weight_ho + weights_ho
    add(weights_ho,1,2,weights_ho,1,2,delta_weight_ho,1,2); 
    add(bias_output,1,1,bias_output,1,1,gradient_ho,1,1);

    //Calculate the delta_weights_ih = (learning_rate * error_hidden)
    //. (hidden . (1 - hidden)) * input_tr
    // gradient)_ih <- learning_rate * error_hidden
    multiplyByScalar(learning_rate,gradient_ih,2,1,error_hidden,2,1); 
    float one_col_matrix_ih[] = {1, 1};
    // gradient_derivative_ih <- 1 - hidden
    subtract(gradient_derivative_ih,2,1,one_col_matrix_ih,2,1,hidden,2,1); 
    elementWise(gradient_derivative_ih,2,1,hidden,2,1,gradient_derivative_ih,2,
    1); //gradient_derivative_ih <- hidden . gradient_derivative_ih
    // gradient_ih <- gradient_ih . gradient_derivative_ih
    elementWise(gradient_ih,2,1,gradient_ih,2,1,gradient_derivative_ih,2,1);
    float inputs_tr[2];//input transposed 
    transpose(inputs_tr,1,2,inputs,2,1);
    // delta_weight_ih <- gradient_ih * inputs_tr
    multiply(delta_weight_ih,2,2,gradient_ih,2,1,inputs_tr,1,2); 
    
    //Update of weights_ih, bias_ih (bias_hidden)
    // weights_ih <- delta_weight_ih + weights_ih
    add(weights_ih,2,2,weights_ih,2,2,delta_weight_ih,2,2); 
    add(bias_hidden,2,1,bias_hidden,2,1,gradient_ih,2,1);
    
}

void train(unsigned long nb_iterations)
{
    int i = 0;
    do {
        init();
        inputs[0] = 0;
        inputs[1] = 1;
        target[0] = 1;
        for (unsigned long ite = 0; ite < nb_iterations; ite++)
        {
            feed_forward();
            feed_backward();
            inputs[0] = (float)(rand() % 2);//pick random inputs
            inputs[1] = (float)(rand() % 2);
            if (inputs[0] == inputs[1])//set the target
                target[0] = 0;
            else
                target[0] = 1;
        }
        int trainingHasWorked = 0;

        inputs[0] = 0.0;
        inputs[1] = 0.0;
        feed_forward();
        if (output[0] > 0.2)//Not working do it again
            trainingHasWorked += 1;

        inputs[0] = 0.0;
        inputs[1] = 1.0;
        feed_forward();
        if (output[0] < 0.8)//Not working do it again
            trainingHasWorked += 1;

        inputs[0] = 1.0;
        inputs[1] = 0.0;
        feed_forward();
        if (output[0] < 0.8)//Not working do it again
            trainingHasWorked += 1;


        inputs[0] = 1.0;
        inputs[1] = 1.0;
        feed_forward();
        if (output[0] > 0.2)//Not working do it again
            trainingHasWorked += 1;

        if (trainingHasWorked == 0)//Every check works
        {
            break;//quit the loop, end of the training
        }
        printf("train %i : error %i\n", i + 1, trainingHasWorked);
        i += 1;
    } while (i < 100);//while true
    save_weights_bias();
}
void xor()
{
    //train for the first time
    unsigned long time;
    puts("How many iterations ?");

    int scan = scanf("%lu",&time); 

    while (scan == 0) 
    {
       scan = scanf("%lu",&time);
    }
    
    //train until the good guess
    train(time);
    
    inputs[0] = 0.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("0 xor 0 : ");
    printMatrix(output,1,1);

    inputs[0] = 0.0;
    inputs[1] = 1.0;
    feed_forward();
    printf("0 xor 1 : ");
    printMatrix(output,1,1);

    inputs[0] = 1.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("1 xor 0 : ");
    printMatrix(output,1,1);


    inputs[0] = 1.0;
    inputs[1] = 1.0;
    feed_forward();
    printf("1 xor 1 : ");
    printMatrix(output,1,1);

    //Test with saved matrix
    printf("Test with saved matrix\n");
    init();
    get_weights_bias();

    inputs[0] = 0.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("0 xor 0 : ");
    printMatrix(output,1,1);

    inputs[0] = 0.0;
    inputs[1] = 1.0;
    feed_forward();
    printf("0 xor 1 : ");
    printMatrix(output,1,1);

    inputs[0] = 1.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("1 xor 0 : ");
    printMatrix(output,1,1);


    inputs[0] = 1.0;
    inputs[1] = 1.0;
    feed_forward();
    printf("1 xor 1 : ");
    printMatrix(output,1,1);
}
