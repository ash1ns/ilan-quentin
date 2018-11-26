#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "matrix.h"
#include <time.h>
#include "file.h"

float inputs_xor[2];
float hidden_xor[2];
float output_xor[1];
float target_xor[1];

float weights_ih_xor[4];
float weights_ho_xor[2];

float bias_hidden_xor[2];
float bias_output_xor[1];

float error_output_xor[1];
float error_hidden_xor[2];

float learning_rate_xor = 0.2;

void save_weights_bias_xor()
{
    save_matrix("neural_network/save_weights_bias/xor/save_weights_ih_xor.data", weights_ih_xor, 
    sizeof(weights_ih_xor) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/xor/save_weights_ho_xor.data", weights_ho_xor, 
    sizeof(weights_ho_xor) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/xor/save_bias_hidden_xor.data", bias_hidden_xor,
    sizeof(bias_hidden_xor) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/xor/save_bias_output_xor.data", bias_output_xor,
    sizeof(bias_output_xor) / sizeof(float)); 
}

void get_weights_bias_xor()
{
    //Get weights_ih_xor
    float *buffer = malloc(sizeof(weights_ih_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_weights_ih_xor.data", 
    sizeof(weights_ih_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ih_xor) / sizeof(float); i++)
    {
        weights_ih_xor[i] = *(buffer + i);
    }
    free(buffer);

    //Get weight_ho
    buffer = malloc(sizeof(weights_ho_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_weights_ho_xor.data", 
    sizeof(weights_ho_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ho_xor) / sizeof(float); i++)
    {
        weights_ho_xor[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_hidden_xor
    buffer = malloc(sizeof(bias_hidden_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_bias_hidden_xor.data", 
    sizeof(bias_hidden_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_hidden_xor) / sizeof(float); i++)
    {
        bias_hidden_xor[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_output_xor
    buffer = malloc(sizeof(bias_output_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_bias_output_xor.data", 
    sizeof(bias_output_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_output_xor) / sizeof(float); i++)
    {
        bias_output_xor[i] = *(buffer + i);
    }
    free(buffer);
}

void init_xor()
{
    initMatrix(weights_ih_xor,2,2); //weigths inputs_xor -> hidden_xor
    initMatrix(weights_ho_xor,1,2); //weigths hidden_xor -> output_xor
    initMatrix(bias_hidden_xor,2,1); 
    initMatrix(bias_output_xor,1,1);
}

void feed_forward_xor()
{
    //from inputs_xor to hidden_xor
    multiply(hidden_xor,2,1,weights_ih_xor,2,2,inputs_xor,2,1);
    add(hidden_xor,2,1,hidden_xor,2,1,bias_hidden_xor,2,1);
    sigmoid_arr(hidden_xor,2,1);
    
    //from hidden_xor to output_xor
    multiply(output_xor,1,1,weights_ho_xor,1,2,hidden_xor,2,1);
    add(output_xor,1,1,output_xor,1,1,bias_output_xor,1,1);
    sigmoid_arr(output_xor,1,1);
}

void get_error_xor()
{
    float weights_ho_xor_tr[2];
    //calcul of output_xor error : error_output_xor = target_xor - output_xor
    subtract(error_output_xor,1,1,target_xor,1,1,output_xor,1,1);
    
    //(calcul of hidden_xor layers errors : error_hidden_xor = weights_ho_xor_tr * 
    //error_output_xor
    transpose(weights_ho_xor_tr,2,1,weights_ho_xor,1,2);
    multiply(error_hidden_xor,2,1,weights_ho_xor_tr,2,1,error_output_xor,1,1);
}

void feed_backward_xor()
{
    get_error_xor();
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
    
    //Calculate the delta_weights_ho_xor = (learning_rate_xor * error_output_xor) . 
    //(ouput . (1 - output_xor)) * hidden_xor_tr
    // gradient_ho <- learning_rate_xor * error_output_xor
    multiplyByScalar(learning_rate_xor,gradient_ho,1,1,error_output_xor,1,1); 
    float one_col_matrix_ho[] = {1};
    // gradient_derivative <- 1 - output_xor
    subtract(gradient_derivative_ho,1,1,one_col_matrix_ho,1,1,output_xor,1,1); 
    //gradient_derivative_ho <- output_xor . gradient_derivative_ho
    elementWise(gradient_derivative_ho,1,1,output_xor,1,1,gradient_derivative_ho,1,
    1); 
    // gradient_ho <- gradient_ho . gradient_derivative_ho
    elementWise(gradient_ho,1,1,gradient_ho,1,1,gradient_derivative_ho,1,1); 
    float hidden_xor_tr[2];//output_xor transposed
    transpose(hidden_xor_tr,1,2,hidden_xor,2,1);
    // delta_weight_ho <- gradient_ho * hidden_xor_tr
    multiply(delta_weight_ho,1,2,gradient_ho,1,1,hidden_xor_tr,1,2); 
    
    //Update weights_ho_xor, bias_ho (bias_output_xor)
    // weights_ho_xor <- delta_weight_ho + weights_ho_xor
    add(weights_ho_xor,1,2,weights_ho_xor,1,2,delta_weight_ho,1,2); 
    add(bias_output_xor,1,1,bias_output_xor,1,1,gradient_ho,1,1);

    //Calculate the delta_weights_ih_xor = (learning_rate_xor * error_hidden_xor)
    //. (hidden_xor . (1 - hidden_xor)) * input_tr
    // gradient)_ih <- learning_rate_xor * error_hidden_xor
    multiplyByScalar(learning_rate_xor,gradient_ih,2,1,error_hidden_xor,2,1); 
    float one_col_matrix_ih[] = {1, 1};
    // gradient_derivative_ih <- 1 - hidden_xor
    subtract(gradient_derivative_ih,2,1,one_col_matrix_ih,2,1,hidden_xor,2,1); 
    elementWise(gradient_derivative_ih,2,1,hidden_xor,2,1,gradient_derivative_ih,2,
    1); //gradient_derivative_ih <- hidden_xor . gradient_derivative_ih
    // gradient_ih <- gradient_ih . gradient_derivative_ih
    elementWise(gradient_ih,2,1,gradient_ih,2,1,gradient_derivative_ih,2,1);
    float inputs_xor_tr[2];//input transposed 
    transpose(inputs_xor_tr,1,2,inputs_xor,2,1);
    // delta_weight_ih <- gradient_ih * inputs_xor_tr
    multiply(delta_weight_ih,2,2,gradient_ih,2,1,inputs_xor_tr,1,2); 
    
    //Update of weights_ih_xor, bias_ih (bias_hidden_xor)
    // weights_ih_xor <- delta_weight_ih + weights_ih_xor
    add(weights_ih_xor,2,2,weights_ih_xor,2,2,delta_weight_ih,2,2); 
    add(bias_hidden_xor,2,1,bias_hidden_xor,2,1,gradient_ih,2,1);
    
}

void train_xor(unsigned long nb_iterations)
{
    int i = 0;
    do {
        init_xor();
        inputs_xor[0] = 0;
        inputs_xor[1] = 1;
        target_xor[0] = 1;
        for (unsigned long ite = 0; ite < nb_iterations; ite++)
        {
            feed_forward_xor();
            feed_backward_xor();
            inputs_xor[0] = (float)(rand() % 2);//pick random inputs_xor
            inputs_xor[1] = (float)(rand() % 2);
            if (inputs_xor[0] == inputs_xor[1])//set the target_xor
                target_xor[0] = 0;
            else
                target_xor[0] = 1;
        }
        int trainingHasWorked = 0;

        inputs_xor[0] = 0.0;
        inputs_xor[1] = 0.0;
        feed_forward_xor();
        if (output_xor[0] > 0.2)//Not working do it again
            trainingHasWorked += 1;

        inputs_xor[0] = 0.0;
        inputs_xor[1] = 1.0;
        feed_forward_xor();
        if (output_xor[0] < 0.8)//Not working do it again
            trainingHasWorked += 1;

        inputs_xor[0] = 1.0;
        inputs_xor[1] = 0.0;
        feed_forward_xor();
        if (output_xor[0] < 0.8)//Not working do it again
            trainingHasWorked += 1;


        inputs_xor[0] = 1.0;
        inputs_xor[1] = 1.0;
        feed_forward_xor();
        if (output_xor[0] > 0.2)//Not working do it again
            trainingHasWorked += 1;

        if (trainingHasWorked == 0)//Every check works
        {
            break;//quit the loop, end of the training
        }
        printf("train %i : error %i\n", i + 1, trainingHasWorked);
        i += 1;
    } while (i < 100);//while true
    save_weights_bias_xor();
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
    train_xor(time);
    
    inputs_xor[0] = 0.0;
    inputs_xor[1] = 0.0;
    feed_forward_xor();
    printf("0 xor 0 : ");
    printMatrix(output_xor,1,1);

    inputs_xor[0] = 0.0;
    inputs_xor[1] = 1.0;
    feed_forward_xor();
    printf("0 xor 1 : ");
    printMatrix(output_xor,1,1);

    inputs_xor[0] = 1.0;
    inputs_xor[1] = 0.0;
    feed_forward_xor();
    printf("1 xor 0 : ");
    printMatrix(output_xor,1,1);


    inputs_xor[0] = 1.0;
    inputs_xor[1] = 1.0;
    feed_forward_xor();
    printf("1 xor 1 : ");
    printMatrix(output_xor,1,1);

    //Test with saved matrix
    printf("Test with saved matrix\n");
    init_xor();
    get_weights_bias_xor();

    inputs_xor[0] = 0.0;
    inputs_xor[1] = 0.0;
    feed_forward_xor();
    printf("0 xor 0 : ");
    printMatrix(output_xor,1,1);

    inputs_xor[0] = 0.0;
    inputs_xor[1] = 1.0;
    feed_forward_xor();
    printf("0 xor 1 : ");
    printMatrix(output_xor,1,1);

    inputs_xor[0] = 1.0;
    inputs_xor[1] = 0.0;
    feed_forward_xor();
    printf("1 xor 0 : ");
    printMatrix(output_xor,1,1);


    inputs_xor[0] = 1.0;
    inputs_xor[1] = 1.0;
    feed_forward_xor();
    printf("1 xor 1 : ");
    printMatrix(output_xor,1,1);
}
