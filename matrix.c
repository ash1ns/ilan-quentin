#include <stdlib.h>
#include <stdio.h>
#include <err.h>

//arr[row * nbColumn + column]
//Verifie type
//arr1 = arr1 + arr2
void add(double arr1[], size_t arr1_row, size_t arr1_col, double arr2[], size_t arr2_row, size_t arr2_col)
{
    if (arr1_row != arr2_row || arr1_col != arr2_col)
    {	
         errx(1,"Wrong size!");
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
void multiply(double res[], size_t res_row, size_t res_col, double arr1[], size_t arr1_row, size_t arr1_col, double arr2[], size_t arr2_row, size_t arr2_col)
{
    if (arr1_col != arr2_row || res_row != arr1_row || res_col != arr2_col)
    {
        errx(1, "Wrong size !");
    }
    for (size_t row = 0; row < arr1_row; row++)
    {
        for (size_t col = 0; col < arr2_col; col++)
        {
            double sum = 0;
            for (size_t k = 0; k < arr2_row;k++)
            {
                sum += arr1[row * arr1_col + k] * arr2[k * arr2_col + col];
            }
            res[row * res_col + col] = sum;
        }
    }
}

//Declare the activation function we use
double f(double input) {
    return input + 1.0;
}


//arr1 = f(arr1)
void function(double arr[], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++) 
    {
        for (size_t j = 0; j < col; j++)
        {
            arr[i * col + j] = f(arr[i * col + j]);
        }
    }
}


//print the matrix arr
void printMatrix(double arr[], size_t row, size_t col)
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
