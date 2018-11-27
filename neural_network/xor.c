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
int inputs_xor_r = 2;
int inputs_xor_c = 1;
float inputs_xor[2];
//Hidden layer
int hidden_xor_r = 2;
int hidden_xor_c = 1;
float hidden_xor[2];
//Output Layer
int output_xor_r = 1;
int output_xor_c = 1;
float output_xor[1];
//Target
float target_xor[1];
//Weights between inputs_xor and hidden_xor
int weights_ih_xor_r = 2;// = hidden_xor_r
int weights_ih_xor_c = 2;// = inputs_xor_r
float weights_ih_xor[2 * 2];//hidden_xor_r * inputs_xor_r
//Weights between hidden_xor and output_xor
int weights_ho_xor_r = 1;// = output_xor_r
int weights_ho_xor_c = 2;// = hidden_xor_r
float weights_ho_xor[1 * 2];//output_xor_r * hidden_xor_r
//Bias hidden_xor
float bias_hidden_xor[2];//same size as hidden_xor
//Bias output_xor
float bias_output_xor[1];//same size as output_xor
//Error of the hidden_xor layer
float error_hidden_xor[2];//same size as hidden_xor
//Error of the output_xor layer
float error_output_xor[1];//same size as output_xor
//Learning rate
float learning_rate_xor = 0.2;
//One col matrix for error between inputs_xor and hidden_xor    
float one_col_matrix_ih_xor[] = {1, 1};
//One col matrix for error between hidden_xor and output_xor    
float one_col_matrix_ho_xor[] = {1};
//Hidden transposed
float hidden_xor_tr[2];
//Input transposed 
float inputs_xor_tr[2];
//Weights_ho_tr
float weights_ho_xor_tr[2];

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
    initMatrix(weights_ih_xor, weights_ih_xor_r, weights_ih_xor_c);//weigths inputs_xor -> hidden_xor
    initMatrix(weights_ho_xor, weights_ho_xor_r, weights_ho_xor_c);//weigths hidden_xor -> output_xor
    initMatrix(bias_hidden_xor,hidden_xor_r,hidden_xor_c); 
    initMatrix(bias_output_xor,output_xor_r,output_xor_c);
}

void feed_forward_xor()
{
    //from inputs_xor to hidden_xor
    multiply(hidden_xor, weights_ih_xor, weights_ih_xor_r, weights_ih_xor_c, inputs_xor, inputs_xor_c);
    add(hidden_xor, hidden_xor, bias_hidden_xor, hidden_xor_r * hidden_xor_c);
    sigmoidArr(hidden_xor, hidden_xor_r * hidden_xor_c);
    
    //from hidden_xor to output_xor
    multiply(output_xor, weights_ho_xor, weights_ho_xor_r, weights_ho_xor_c, hidden_xor, hidden_xor_c);
    add(output_xor, output_xor, bias_output_xor, output_xor_r * output_xor_c);
    sigmoidArr(output_xor, output_xor_r * output_xor_c);
}

void get_error_xor()
{
    //calcul of output_xor error : error_output_xor = target_xor - output_xor
    subtract(error_output_xor, target_xor, output_xor, output_xor_r * output_xor_c);
    
    //(calcul of hidden_xor layers errors : error_hidden_xor = weights_ho_xor_tr * 
    //error_output_xor
    transpose(weights_ho_xor_tr, weights_ho_xor, weights_ho_xor_r, weights_ho_xor_c);
    multiply(error_hidden_xor, weights_ho_xor_tr, weights_ho_xor_c, weights_ho_xor_r, error_output_xor, output_xor_c);
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
    //(output_xor . (1 - output_xor)) * hidden_xor_tr
    // gradient_ho <- learning_rate_xor * error_output_xor
    multiplyByScalar(learning_rate_xor, gradient_ho, error_output_xor, output_xor_r * output_xor_c); 
    // gradient_derivative <- 1 - output_xor
    subtract(gradient_derivative_ho, one_col_matrix_ho_xor, output_xor, output_xor_r * output_xor_c); 
    //gradient_derivative_ho <- output_xor . gradient_derivative_ho
    elementWise(gradient_derivative_ho, output_xor, gradient_derivative_ho, output_xor_r * output_xor_c); 
    // gradient_ho <- gradient_ho . gradient_derivative_ho
    elementWise(gradient_ho, gradient_ho, gradient_derivative_ho, output_xor_r * output_xor_c); 
    transpose(hidden_xor_tr, hidden_xor, hidden_xor_r, hidden_xor_c);
    // delta_weight_ho <- gradient_ho * hidden_xor_tr
    multiply(delta_weight_ho, gradient_ho, output_xor_r, output_xor_c, hidden_xor_tr, hidden_xor_r); 
    
    //Update weights_ho_xor, bias_ho (bias_output_xor)
    // weights_ho_xor <- delta_weight_ho + weights_ho_xor
    add(weights_ho_xor, weights_ho_xor, delta_weight_ho, weights_ho_xor_r * weights_ho_xor_c); 
    add(bias_output_xor, bias_output_xor, gradient_ho, output_xor_r * output_xor_c);

    //Calculate the delta_weights_ih_xor = (learning_rate_xor * error_hidden_xor)
    //. (hidden_xor . (1 - hidden_xor)) * input_tr
    // gradient)_ih <- learning_rate_xor * error_hidden_xor
    multiplyByScalar(learning_rate_xor, gradient_ih, error_hidden_xor, hidden_xor_r * hidden_xor_c); 
    // gradient_derivative_ih <- 1 - hidden_xor
    subtract(gradient_derivative_ih, one_col_matrix_ih_xor, hidden_xor, hidden_xor_r * hidden_xor_c); 
    //gradient_derivative_ih <- hidden_xor . gradient_derivative_ih
    elementWise(gradient_derivative_ih, hidden_xor, gradient_derivative_ih, hidden_xor_r * hidden_xor_c);
    // gradient_ih <- gradient_ih . gradient_derivative_ih
    elementWise(gradient_ih, gradient_ih, gradient_derivative_ih, hidden_xor_r * hidden_xor_c);
    transpose(inputs_xor_tr, inputs_xor, inputs_xor_r, inputs_xor_c);
    // delta_weight_ih <- gradient_ih * inputs_xor_tr
    multiply(delta_weight_ih, gradient_ih, hidden_xor_r, hidden_xor_c, inputs_xor_tr, inputs_xor_r); 
    
    //Update of weights_ih_xor, bias_ih (bias_hidden_xor)
    // weights_ih_xor <- delta_weight_ih + weights_ih_xor
    add(weights_ih_xor, weights_ih_xor, delta_weight_ih, weights_ih_xor_r * weights_ih_xor_c); 
    add(bias_hidden_xor, bias_hidden_xor, gradient_ih, hidden_xor_r * hidden_xor_c);   
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
        int train_xoringHasWorked = 0;

        inputs_xor[0] = 0.0;
        inputs_xor[1] = 0.0;
        feed_forward_xor();
        if (output_xor[0] > 0.2)//Not working do it again
            train_xoringHasWorked += 1;

        inputs_xor[0] = 0.0;
        inputs_xor[1] = 1.0;
        feed_forward_xor();
        if (output_xor[0] < 0.8)//Not working do it again
            train_xoringHasWorked += 1;

        inputs_xor[0] = 1.0;
        inputs_xor[1] = 0.0;
        feed_forward_xor();
        if (output_xor[0] < 0.8)//Not working do it again
            train_xoringHasWorked += 1;


        inputs_xor[0] = 1.0;
        inputs_xor[1] = 1.0;
        feed_forward_xor();
        if (output_xor[0] > 0.2)//Not working do it again
            train_xoringHasWorked += 1;

        if (train_xoringHasWorked == 0)//Every check works
        {
            break;//quit the loop, end of the train_xoring
        }
        printf("train_xor %i : error %i\n", i + 1, train_xoringHasWorked);
        i += 1;
    } while (i < 100);//while true
    save_weights_bias_xor();
}
void xor()
{
    //train_xor for the first time
    unsigned long time;
    puts("How many iterations ?");

    int scan = scanf("%lu",&time); 

    while (scan == 0) 
    {
       scan = scanf("%lu",&time);
    }
    
    //train_xor until the good guess
    train_xor(time);
    
    inputs_xor[0] = 0.0;
    inputs_xor[1] = 0.0;
    feed_forward_xor();
    printf("0 xor 0 : ");
    printMatrix(output_xor, output_xor_r, output_xor_c);

    inputs_xor[0] = 0.0;
    inputs_xor[1] = 1.0;
    feed_forward_xor();
    printf("0 xor 1 : ");
    printMatrix(output_xor, output_xor_r, output_xor_c);

    inputs_xor[0] = 1.0;
    inputs_xor[1] = 0.0;
    feed_forward_xor();
    printf("1 xor 0 : ");
    printMatrix(output_xor,output_xor_r, output_xor_c);


    inputs_xor[0] = 1.0;
    inputs_xor[1] = 1.0;
    feed_forward_xor();
    printf("1 xor 1 : ");
    printMatrix(output_xor, output_xor_r, output_xor_c);

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
    printMatrix(output_xor, output_xor_r, output_xor_c);

    inputs_xor[0] = 1.0;
    inputs_xor[1] = 0.0;
    feed_forward_xor();
    printf("1 xor 0 : ");
    printMatrix(output_xor, output_xor_r, output_xor_c);


    inputs_xor[0] = 1.0;
    inputs_xor[1] = 1.0;
    feed_forward_xor();
    printf("1 xor 1 : ");
    printMatrix(output_xor, output_xor_r, output_xor_c);
}
