#include <stdio.h>
#include <stdlib.h>
#include "deepcopy.h"
// Fonction de deepcopy pour un tableau 2D de taille n_rows x n_cols
int **deepcopy(int **source, int n_rows, int n_cols) {
    int **clone = (int **)malloc(n_rows * sizeof(int *));
    for (int i = 0; i < n_rows; i++) {
        clone[i] = (int *)malloc(n_cols * sizeof(int));
        for (int j = 0; j < n_cols; j++) {
            clone[i][j] = source[i][j];
        }
    }
    return clone;
}
