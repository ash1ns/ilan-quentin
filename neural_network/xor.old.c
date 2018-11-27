#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "matrix.h"
#include <time.h>
#include "file.h"

// name_of_name_r = number of columns of the matrix
// name_of_name_c = number of columns of the matrix
//Inputs layer
int inputs_r = 2;
int inputs_c = 1;
float inputs[2];
//Hidden layer
int hidden_r = 2;
int hidden_c = 1;
float hidden[2];
//Output Layer
int output_r = 1;
int output_c = 1;
float output[1];
//Target
float target[1];
//Weights between inputs and hidden
int weights_ih_r = 2;// = hidden_r
int weights_ih_c = 2;// = inputs_r
float weights_ih[2 * 2];//hidden_r * inputs_r
//Weights between hidden and output
int weights_ho_r = 1;// = output_r
int weights_ho_c = 2;// = hidden_r
float weights_ho[1 * 2];//output_r * hidden_r
//Bias hidden
float bias_hidden[2];//same size as hidden
//Bias output
float bias_output[1];//same size as output
//Error of the hidden layer
float error_hidden[2];//same size as hidden
//Error of the output layer
float error_output[1];//same size as output
//Learning rate
float learning_rate = 0.2;
//One col matrix for error between inputs and hidden    
float one_col_matrix_ih[] = {1, 1};
//One col matrix for error between hidden and output    
float one_col_matrix_ho[] = {1};
//Hidden transposed
float hidden_tr[2];
//Input transposed
float inputs_tr[2];
//Weights_ho_tr
float weights_ho_tr[2];

void save_weights_bias_xor()
{
    save_matrix("neural_network/save_weights_bias/xor/save_weights_ih_xor.data"
    , weights_ih_xor, sizeof(weights_ih_xor) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/xor/save_weights_ho_xor.data"
    , weights_ho_xor, sizeof(weights_ho_xor) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/xor/save_bias_hidden_xor.data"
    , bias_hidden_xor, sizeof(bias_hidden_xor) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/xor/save_bias_output_xor.data"
    , bias_output_xor, sizeof(bias_output_xor) / sizeof(float)); 
}

void get_weights_bias_xor()
{
    //Get weights_ih_xor
    float *buffer = malloc(sizeof(weights_ih_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_weights_ih_xor.data"
    , sizeof(weights_ih_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ih_xor) / sizeof(float); i++)
    {
        weights_ih_xor[i] = *(buffer + i);
    }
    free(buffer);

    //Get weight_ho
    buffer = malloc(sizeof(weights_ho_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_weights_ho_xor.data"
    , sizeof(weights_ho_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ho_xor) / sizeof(float); i++)
    {
        weights_ho_xor[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_hidden_xor
    buffer = malloc(sizeof(bias_hidden_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_bias_hidden_xor.data"
    , sizeof(bias_hidden_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_hidden_xor) / sizeof(float); i++)
    {
        bias_hidden_xor[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_output_xor
    buffer = malloc(sizeof(bias_output_xor));
    get_matrix(buffer, "neural_network/save_weights_bias/xor/save_bias_output_xor.data"
    , sizeof(bias_output_xor) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_output_xor) / sizeof(float); i++)
    {
        bias_output_xor[i] = *(buffer + i);
    }
    free(buffer);
}

void init_xor()
{
    
    initMatrix(weights_ih, weights_ih_r, weights_ih_c);//weigths inputs -> hidden
    initMatrix(weights_ho, weights_ho_r, weights_ho_c);//weigths hidden -> output
    initMatrix(bias_hidden,hidden_r,hidden_c); 
    initMatrix(bias_output,output_r,output_c);
}

void feed_forward_xor()
{
    
    //from inputs to hidden
    multiply(hidden, weights_ih, weights_ih_r, weights_ih_c, inputs, inputs_c);
    add(hidden, hidden, bias_hidden, hidden_r * hidden_c);
    sigmoidArr(hidden, hidden_r * hidden_c);
    
    //from hidden to output
    multiply(output, weights_ho, weights_ho_r, weights_ho_c, hidden, hidden_c);
    add(output, output, bias_output, output_r * output_c);
    sigmoidArr(output, output_r * output_c);
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
    multiplyByScalar(learning_rate, gradient_ho, error_output, output_r * output_c); 
    // gradient_derivative <- 1 - output
    subtract(gradient_derivative_ho, one_col_matrix_ho, output, output_r * output_c); 
    //gradient_derivative_ho <- output . gradient_derivative_ho
    elementWise(gradient_derivative_ho, output, gradient_derivative_ho, output_r * output_c); 
    // gradient_ho <- gradient_ho . gradient_derivative_ho
    elementWise(gradient_ho, gradient_ho, gradient_derivative_ho, output_r * output_c); 
    transpose(hidden_tr, hidden, hidden_r, hidden_c);
    // delta_weight_ho <- gradient_ho * hidden_tr
    multiply(delta_weight_ho, gradient_ho, output_r, output_c, hidden_tr, hidden_r); 
    
    //Update weights_ho, bias_ho (bias_output)
    // weights_ho <- delta_weight_ho + weights_ho
    add(weights_ho, weights_ho, delta_weight_ho, weights_ho_r * weights_ho_c); 
    add(bias_output, bias_output, gradient_ho, output_r * output_c);

    //Calculate the delta_weights_ih = (learning_rate * error_hidden)
    //. (hidden . (1 - hidden)) * input_tr
    // gradient)_ih <- learning_rate * error_hidden
    multiplyByScalar(learning_rate, gradient_ih, error_hidden, hidden_r * hidden_c); 
    // gradient_derivative_ih <- 1 - hidden
    subtract(gradient_derivative_ih, one_col_matrix_ih, hidden, hidden_r * hidden_c); 
    //gradient_derivative_ih <- hidden . gradient_derivative_ih
    elementWise(gradient_derivative_ih, hidden, gradient_derivative_ih, hidden_r * hidden_c);
    // gradient_ih <- gradient_ih . gradient_derivative_ih
    elementWise(gradient_ih, gradient_ih, gradient_derivative_ih, hidden_r * hidden_c);
    transpose(inputs_tr, inputs, inputs_r, inputs_c);
    // delta_weight_ih <- gradient_ih * inputs_tr
    multiply(delta_weight_ih, gradient_ih, hidden_r, hidden_c, inputs_tr, inputs_r); 
    
    //Update of weights_ih, bias_ih (bias_hidden)
    // weights_ih <- delta_weight_ih + weights_ih
    add(weights_ih, weights_ih, delta_weight_ih, weights_ih_r * weights_ih_c); 
    add(bias_hidden, bias_hidden, gradient_ih, hidden_r * hidden_c);
}

void train_xor(unsigned long nb_iterations)
{ 
    int i = 0;
    do {
        init_xor();
        inputs[0] = 0;
        inputs[1] = 1;
        target[0] = 1;
        for (unsigned long ite = 0; ite < nb_iterations; ite++)
        {
            feed_forward_xor();
            feed_backward_xor();
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
        feed_forward_xor();
        if (output[0] > 0.2)//Not working do it again
            trainingHasWorked += 1;

        inputs[0] = 0.0;
        inputs[1] = 1.0;
        feed_forward_xor();
        if (output[0] < 0.8)//Not working do it again
            trainingHasWorked += 1;

        inputs[0] = 1.0;
        inputs[1] = 0.0;
        feed_forward_xor();
        if (output[0] < 0.8)//Not working do it again
            trainingHasWorked += 1;


        inputs[0] = 1.0;
        inputs[1] = 1.0;
        feed_forward_xor();
        if (output[0] > 0.2)//Not working do it again
            trainingHasWorked += 1;

        if (trainingHasWorked == 0)//Every check works
        {
            break;//quit the loop, end of the training
        }
        printf("train %i : error %i\n", i + 1, trainingHasWorked);
        i += 1;    
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
   
    inputs[0] = 0.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("0 xor 0 : ");
    printMatrix(output, output_r, output_c);

    inputs[0] = 0.0;
    inputs[1] = 1.0;
    feed_forward();
    printf("0 xor 1 : ");
    printMatrix(output, output_r, output_c);

    inputs[0] = 1.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("1 xor 0 : ");
    printMatrix(output,output_r, output_c);


    inputs[0] = 1.0;
    inputs[1] = 1.0;
    feed_forward();
    printf("1 xor 1 : ");
    printMatrix(output, output_r, output_c);

    //Test with saved matrix
    printf("Test with saved matrix\n");
    init_xor();
    get_weights_bias_xor();

    inputs[0] = 0.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("0 xor 0 : ");
    printMatrix(output,1,1);

    inputs[0] = 0.0;
    inputs[1] = 1.0;
    feed_forward();
    printf("0 xor 1 : ");
    printMatrix(output, output_r, output_c);

    inputs[0] = 1.0;
    inputs[1] = 0.0;
    feed_forward();
    printf("1 xor 0 : ");
    printMatrix(output, output_r, output_c);


    inputs[0] = 1.0;


}
