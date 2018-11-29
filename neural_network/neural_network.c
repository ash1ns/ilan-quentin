#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "matrix.h"
#include <time.h>
#include "file.h"
#include "save_data.h"

// name_of_name_r = number of columns of the matrix
// name_of_name_c = number of columns of the matrix
//Inputs layer
int inputs_r = 784; 
int inputs_c = 1;
float inputs[784 * 1];
//Hidden layer
int hidden_r = 15;
int hidden_c = 1;
float hidden[15 * 1];
//Output Layer
int output_r = 62;
int output_c = 1;
float output[62 * 1];
//Target
float target[62];
//Weights between inputs and hidden
int weights_ih_r = 15;// = hidden_r
int weights_ih_c = 784;// = inputs_r
float weights_ih[15 * 784];//hidden_r * inputs_r
//Weights between hidden and output
int weights_ho_r = 62;// = output_r
int weights_ho_c = 15;// = hidden_r
float weights_ho[62 * 15];//output_r * hidden_r
//Bias hidden
float bias_hidden[15 * 1];//same size as hidden
//Bias output
float bias_output[62 * 1];//same size as output
//Error of the hidden layer
float error_hidden[15 * 1];//same size as hidden
//Error of the output layer
float error_output[62 * 1];//same size as output
//Learning rate
float learning_rate = 0.2;
//One col matrix for error between inputs and hidden    
float one_col_matrix_ih[] = {1, 1};
//One col matrix for error between hidden and output    
float one_col_matrix_ho[] = {1};
//Hidden transposed
float hidden_tr[15 * 1]; //same size as hidden
//Input transposed 
float inputs_tr[784 * 1]; //same size as inputs
//Weights_ho_tr
float weights_ho_tr[62 * 15]; // = hidden_r * output_r 

//Training data
int width_letter = 28;
int height_letter = 28;
int number_of_letters = 62; //a + A + 0 
float all_training_data[28 * 28 * 62];

void save_weights_bias()
{
    save_matrix("neural_network/save_weights_bias/neural_network/save_weights_ih.data"
    , weights_ih, sizeof(weights_ih) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/neural_network/save_weights_ho.data"
    , weights_ho, sizeof(weights_ho) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/neural_network/save_bias_hidden.data"
    , bias_hidden, sizeof(bias_hidden) / sizeof(float));
    save_matrix("neural_network/save_weights_bias/neural_network/save_bias_output.data"
    , bias_output, sizeof(bias_output) / sizeof(float)); 
}

void get_weights_bias()
{
    //Get weights_ih
    float *buffer = malloc(sizeof(weights_ih));
    get_matrix(buffer, "neural_network/save_weights_bias/neural_network/save_weights_ih.data"
    , sizeof(weights_ih) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ih) / sizeof(float); i++)
    {
        weights_ih[i] = *(buffer + i);
    }
    free(buffer);

    //Get weight_ho
    buffer = malloc(sizeof(weights_ho));
    get_matrix(buffer, "neural_network/save_weights_bias/neural_network/save_weights_ho.data"
    , sizeof(weights_ho) / sizeof(float));
    for (size_t i = 0; i < sizeof(weights_ho) / sizeof(float); i++)
    {
        weights_ho[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_hidden
    buffer = malloc(sizeof(bias_hidden));
    get_matrix(buffer, "neural_network/save_weights_bias/neural_network/save_bias_hidden.data"
    , sizeof(bias_hidden) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_hidden) / sizeof(float); i++)
    {
        bias_hidden[i] = *(buffer + i);
    }
    free(buffer);

    //Get bias_output
    buffer = malloc(sizeof(bias_output));
    get_matrix(buffer, "neural_network/save_weights_bias/neural_network/save_bias_output.data"
    , sizeof(bias_output) / sizeof(float));
    for (size_t i = 0; i < sizeof(bias_output) / sizeof(float); i++)
    {
        bias_output[i] = *(buffer + i);
    }
    free(buffer);
}

//Get from a file  and fill the training data array
void get_training_data()
{
    float *buffer = malloc(sizeof(all_training_data));
    get_letters_from_file("training.data", buffer, width_letter * height_letter, number_of_letters);
    for (size_t i = 0; i < sizeof(all_training_data) / sizeof(float); i++)
        all_training_data[i] = *(buffer + i);
    free(buffer);
}

//Get one letter in pos from all training data array
void get_one_letter(float letter[], size_t pos)
{
    pos = width_letter * height_letter * pos;
    for (int i = 0; i < height_letter * width_letter; i++, pos++)
        letter[i] = all_training_data[pos];
}

void init()
{
    initMatrix(weights_ih, weights_ih_r, weights_ih_c);//weigths inputs -> hidden
    initMatrix(weights_ho, weights_ho_r, weights_ho_c);//weigths hidden -> output
    initMatrix(bias_hidden,hidden_r,hidden_c); 
    initMatrix(bias_output,output_r,output_c);
}

void feed_forward()
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

void get_error()
{
    //calcul of output error : error_output = target - output
    subtract(error_output, target, output, output_r * output_c);
    
    //(calcul of hidden layers errors : error_hidden = weights_ho_tr * 
    //error_output
    transpose(weights_ho_tr, weights_ho, weights_ho_r, weights_ho_c);
    multiply(error_hidden, weights_ho_tr, weights_ho_c, weights_ho_r, error_output, output_c);
}

void feed_backward()
{
    get_error();
    float delta_weight_ho[2];
    float delta_weight_ih[4];
    float gradient_ho[26];
    float gradient_ih[15];
    float gradient_derivative_ho[26];
    float gradient_derivative_ih[15];
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

void train(unsigned long nb_iterations)
{
    get_training_data();//Fill the training data matrix;
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


char get_output(float output[])
{
    /* HOW OUTPUT[] WORKS ?

    * a -> z are store from 0 to 25
    * A -> Z are store from 26 -> 51
    * 0 -> 9 are store from 52 -> 61
    */
    
    float max = output[0];
    size_t letter_pos = 0;
    for (int i = 0; i <= 61; i++)
    {
        if (max < output[i])
        {
            max = output[i];
            letter_pos = i;
        }
    }
    if (letter_pos < 26) return letter_pos + 'a'; //a 
    if (letter_pos < 52) return letter_pos - 26 + 'A'; //A
    else return letter_pos - 52 + '0'; //figure
}
void neural_network()
{
    
    //Save training data before using it
    get_training_data();
    float letter[height_letter * width_letter];
    for (int i = 0; i < number_of_letters; i++)
    {
        get_one_letter(letter, i);
        printMatrixInt(letter, height_letter, width_letter);
        printf("\n");
    }
    /*
    //train for the first time
    unsigned long time;
    puts("How many iterations ?");

    int scan = scanf("%lu",&time); 

    while (scan == 0) 
    {
       scan = scanf("%lu",&time);
    }
    
    //train until the good guess
    //!\\Still training for xor 
    train(time);
    */
}
