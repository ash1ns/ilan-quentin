#ifndef MATRIX_H
#define MATRIX_H
void copy(float res[], float arr[], size_t len);
void add(float res[], float arr1[], float arr2[], size_t len);
void subtract(float res[], float arr1[], float arr2[], size_t len);
void multiplyByScalar(float k, float res[], float arr[], size_t len);
void multiply(float res[], float arr1[], size_t arr1_row, size_t arr1_col, float arr2[], size_t arr2_col);
void elementWise(float res[], float arr1[], float arr2[], size_t len);
void sigmoidArr(float arr[], size_t len);
void transpose(float res[], float arr[], size_t arr_row, size_t arr_col);
void printMatrix(float arr[], size_t row, size_t col);
void printMatrixInt(float arr[], size_t row, size_t col);
void initMatrix(float arr[], size_t row, size_t col);
#endif
