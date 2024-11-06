#ifndef UTILS
#define UTILS
void swap(float *a, float *b);
int partition(float *Tab, int low, int high);
void quicksort(float *Tab, int low, int high);
void swapDict(float *a, float *b, int *intArrayI, int *intArrayJ, int n_cols);
int partitionDict(float *Tab, int **intArray, int low, int high, int n_cols);
void quicksortDict(float *Tab, int **intArray, int low, int high, int n_cols);
float max(float *arr, int size);
float min(float *arr, int size);
int indexOfMax(float *arr, int size);
int indexOfMin(float *arr, int size);
void printIntTable(int** table, int n_row, int n_col, char* message);
void printDoubleTable(double** table, int n_row, int n_col, char* message);
void printFloatTable(float* table, int n_cols, char* message);
void print1DIntTable(int*  table, int n_cols, char* message);
void free2DTable(void** table, int size) ;
#endif