#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


//faire des tests unitaire pour chaque fonctions

// Fonction pour échanger deux éléments
void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction de partition pour le quicksort
int partition(float *Tab, int low, int high) {
    float pivot = Tab[high]; // Choisir le dernier élément comme pivot
    int i = (low - 1); // Indice du plus petit élément

    for (int j = low; j < high; j++) {
        if (Tab[j] < pivot) {
            i++;
            swap(&Tab[i], &Tab[j]); // Échanger si l'élément est plus petit que le pivot
        }
    }
    swap(&Tab[i + 1], &Tab[high]); // Échanger le pivot avec le bon endroit
    return (i + 1); // Retourner l'indice du pivot
}

// Fonction principale du quicksort
void quicksort(float *Tab, int low, int high) {
    if (low < high) {
        // Partitionner le tableau
        int pi = partition(Tab, low, high);

        // Trier les éléments séparément avant et après la partition
        quicksort(Tab, low, pi - 1);
        quicksort(Tab, pi + 1, high);
    }
}




// Fonction pour échanger deux éléments dans le tableau de float et dans le tableau d'int
void swapDict(float *a, float *b, int *intArrayI, int *intArrayJ, int n_cols) {
    float tempFloat = *a;
    *a = *b;
    *b = tempFloat;

    // Échanger les valeurs dans le tableau d'int
    for (int index = 0; index < n_cols; index ++){
        int temp = intArrayI[index];
        intArrayI[index] =  intArrayJ[index];
        intArrayJ[index] = temp;
    }
}

// Fonction de partition pour le quicksort
int partitionDict(float *Tab, int **intArray, int low, int high, int n_cols) {
    float pivot = Tab[high]; // Choisir le dernier élément comme pivot
    int i = (low - 1); // Indice du plus petit élément

    for (int j = low; j < high; j++) {
        if (Tab[j] < pivot) {
            i++;
            swapDict(&Tab[i], &Tab[j], intArray[i], intArray[j], n_cols); // Échanger si l'élément est plus petit que le pivot
        }
    }
    swapDict(&Tab[i + 1], &Tab[high], intArray[i + 1], intArray[high], n_cols); // Échanger le pivot avec le bon endroit
    return (i + 1); // Retourner l'indice du pivot
}

// Fonction principale du quicksort
void quicksortDict(float *Tab, int **intArray, int low, int high, int n_cols) {
    if (low < high) {
        // Partitionner le tableau
        int pi = partitionDict(Tab, intArray, low, high, n_cols);

        // Trier les éléments séparément avant et après la partition
        quicksortDict(Tab, intArray, low, pi - 1, n_cols);
        quicksortDict(Tab, intArray, pi + 1, high, n_cols);
    }
}






// Fonction pour trouver le maximum dans un tableau de floats
float max(float *arr, int size) {
    float maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// Fonction pour trouver le minimum dans un tableau de floats
float min(float *arr, int size) {
    float minVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

int indexOfMax(float *arr, int size) {
    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i; // Mettre à jour l'indice du maximum
        }
    }
    return maxIndex;
}

int indexOfMin(float *arr, int size){
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i; // Mettre à jour l'indice du minimum
        }
    }
    return minIndex;
}


void printIntTable(int** table, int n_row, int n_col, char* message){
    printf("%s", message);
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n\n");
    }
}

void printDoubleTable(double** table, int n_row, int n_col, char* message) {
    printf("%s", message);
    for (int i = 0; i < n_row; i++){
        for (int j = 1; j< n_col; j++){
            printf(" %f ", table[i][j]);
        }
        printf("\n");
    }
}

void printFloatTable(float* table, int n_cols, char* message){
    printf("%s", message);
    for (int i = 0; i< n_cols; i++){
        printf(" %f", table[i]);
    }
    printf("\n\n");
}
void print1DIntTable(int*  table, int n_cols, char* message){
    printf("%s", message);
    for (int i = 0; i< n_cols; i++){
        printf(" %d", table[i]);
    }
    printf("\n\n");
}
void free2DTable(void** table, int size) {
    for (int i = 0; i < size; i++) {
        free(table[i]);
    }
    free(table);
}