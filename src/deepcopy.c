#include <stdio.h>
#include <stdlib.h>
#include "deepcopy.h"
// Fonction de deepcopy pour un tableau 2D de taille n_rows x n_cols
int **deepcopy(int **source, int n_rows, int n_cols) {
    // Allocation du tableau de lignes pour le clone
    int **clone = (int **)malloc(n_rows * sizeof(int *));
    if (clone == NULL) {
        perror("Erreur d'allocation de mémoire pour clone");
        exit(EXIT_FAILURE);
    }

    // Allocation et copie des données pour chaque ligne
    for (int i = 0; i < n_rows; i++) {
        clone[i] = (int *)malloc(n_cols * sizeof(int));
        if (clone[i] == NULL) {
            perror("Erreur d'allocation de mémoire pour clone[i]");
            // Libération de la mémoire déjà allouée en cas d'échec
            for (int j = 0; j < i; j++) {
                free(clone[j]);
            }
            free(clone);
            exit(EXIT_FAILURE);
        }

        // Copie des éléments de source[i] vers clone[i]
        for (int j = 0; j < n_cols; j++) {
            clone[i][j] = source[i][j];
        }
    }
    
    return clone;
}
