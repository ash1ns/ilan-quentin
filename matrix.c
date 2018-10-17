#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>

//arr[row * nbColumn + column]
//Verifie type
//arr1 = arr1 + arr2
void add(float arr1[], size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t arr2_col)
{
    if (arr1_row != arr2_row || arr1_col != arr2_col)
    {	
         errx(1,"add -> Wrong size!");
    }
    
    for (size_t row = 0; row < arr1_row; row++) 
    {
        for (size_t col = 0; col < arr1_col; col++)
	{
            arr1[row * arr1_col + col] = arr1[row * arr1_col + col] + arr2[row * arr2_col + col];
    	}
     }
}

//res = arr1 * arr2
void multiply(float res[], size_t res_row, size_t res_col, float arr1[], size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t arr2_col)
{
    if (arr1_col != arr2_row || res_row != arr1_row || res_col != arr2_col)
    {
        errx(1, "multiply -> Wrong size !");
    }
    for (size_t row = 0; row < arr1_row; row++)
    {
        for (size_t col = 0; col < arr2_col; col++)
        {
            float sum = 0;
            for (size_t k = 0; k < arr2_row;k++)
            {
                sum += arr1[row * arr1_col + k] * arr2[k * arr2_col + col];
            }
            res[row * res_col + col] = sum;
        }
    }
}

//Declare the activation function we use
float sigmoid(float input) {
    return 1 / (1 + exp(-input)); 
}


//arr1 = sigmoid(arr1)
void sigmoid_arr(float arr[], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++) 
    {
        for (size_t j = 0; j < col; j++)
        {
            arr[i * col + j] = sigmoid(arr[i * col + j]);
        }
    }
}

//Init a matrix randomly
void initMatrix(float arr[], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            float random = (float)(rand()%(100));
            random = random / 100.0;
            arr[i * col + j] = random; 
        }
    }
}

//print the matrix arr
void printMatrix(float arr[], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++) 
    {
        for (size_t j = 0; j < col; j++)
        {
            printf("%lf ", arr[i * col + j]);
        }
        printf("\n");
    }
}
