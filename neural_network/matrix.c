#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include <time.h>
//arr[row * nbColumn + column]

void copy(float res[], float arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
        res[i] = arr[i];
}

//res = arr1 + arr2
void add(float res[], float arr1[], float arr2[], size_t len)
{
    for (size_t i = 0; i < len; i++) 
        res[i] = arr1[i] + arr2[i];
}

//res = arr1 - arr2
void subtract(float res[], float arr1[], float arr2[], size_t len)
{
    for (size_t i = 0; i < len; i++) 
        res[i] = arr1[i] - arr2[i];
}

//res = arr1 * lr
void multiplyByScalar(float k, float res[], float arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
        res[i] = arr[i] * k;
}

//res = arr1 * arr2
void multiply(float res[], size_t res_row, size_t res_col, float arr1[], size_t
arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t arr2_col)
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

void elementWise(float res[], size_t res_row, size_t res_col, float arr1[], 
size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t 
arr2_col)
{
    if (arr1_row != arr2_row || arr1_col != arr2_col || res_row != arr1_row || 
    res_col != arr1_col)
    {	
         errx(1,"element wise -> Wrong size!");
    }
    
    for (size_t row = 0; row < res_row; row++) 
    {
        for (size_t col = 0; col < res_col; col++)
	{
            res[row * res_col + col] = arr1[row * arr1_col + col] 
            * arr2[row * arr2_col + col];
    	}
    }
}

//Acitvation function (sigmoid)
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

//res = transpose(arr)
void transpose(float res[], size_t res_row, size_t res_col, float arr[], size_t
arr_row, size_t arr_col)
{
    if (res_row != arr_col || res_col != arr_row) 
    {
        errx(1,"transpose -> Wrong size!");
    }
    for (size_t i = 0; i < arr_row; i++)
    {
        for (size_t j = 0; j < arr_col; j++)
        {
            res[j * res_col + i] = arr[i * arr_col +j];
        }
    }
}


//Init a matrix randomly ]-1.0, 1.0[
void initMatrix(float arr[], size_t row, size_t col)
{
    float random;
    float neg_random;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            random = (float)(rand() % 100);
            neg_random = rand() % 2;//0 for -1 and 1 for 1
            if (neg_random == 0)
                neg_random = -1;
            arr[i * col + j] = (float)(random * neg_random / 100.0);
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
            printf("%f ", arr[i * col + j]);
        }
        printf("\n");
    }
}
