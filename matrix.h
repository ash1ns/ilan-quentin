#ifndef MATRIX_H
#define MATRIX_H
void copy(float res[], size_t res_row, size_t res_col, float arr[], size_t arr_row, size_t arr_col);
void add(float res[], size_t res_row, size_t res_col, float arr1[], size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t arr2_col);
void subtract(float res[], size_t res_row, size_t res_col, float arr1[], size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t arr2_col);
void multiply(float res[], size_t res_row, size_t res_col, float arr1[], size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t arr2_col);
void multiplyByScalar(float k, float res[], size_t res_row, size_t res_col, float arr[], size_t arr_row, size_t arr_col);
void elementWise(float res[], size_t res_row, size_t res_col, float arr1[], size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_row, size_t arr2_col);
void sigmoid_arr(float arr[], size_t row, size_t col);
void transpose(float res[], size_t res_row, size_t res_col, float arr[], size_t arr_row, size_t arr_col);
void printMatrix(float arr[], size_t row, size_t col);
void initMatrix(float arr[], size_t row, size_t col);
#endif
