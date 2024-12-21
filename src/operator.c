
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operator.h"

int**  migration_operator(int **NP1, int **NP2,int n_rows, int n_cols, float p){
    printf("n_rows = %d, n_cols = %d, p = %f\n", n_rows, n_cols, p);
    for (int indexMonarch = 0; indexMonarch < n_rows; indexMonarch++) {
        for (int indexGenome = 0; indexGenome < n_cols; indexGenome++) {
            float tirage = (float)rand()/(float)(RAND_MAX);
            printf("tirage = %f\n",tirage);
            if (0.5 < p) {
                int autremonarch = rand() % n_rows;
                printf("autremonarch = %d\n",autremonarch);
                NP1[indexMonarch][indexGenome] = NP1[autremonarch][indexGenome];
            } else {
                int autremonarch = rand() % n_rows;
                NP1[indexMonarch][indexGenome] = NP2[autremonarch][indexGenome];
            }
        }
    }
    return NP1;
} 



            

// vérifier qu'il n'y a pas d'erreur entre n_rows et n_cols
int** adjusting_operator(int **NP1, int **NP2, int ** population, float p, int bin, int n_rows, int n_cols, double ** costTable, double ** delayTable) {
    for (int indexMonarch = 0; indexMonarch < n_rows; indexMonarch++) {
        for (int indexGenome = 0; indexGenome < n_cols; indexGenome++) {
            float tirage = (float)rand() / RAND_MAX;
            if (tirage < p) {
                int *bestMonarch = (int *)calloc(n_cols, sizeof(int));
                determineBestMonarch(population, costTable, delayTable, n_cols, bin, &bestMonarch, n_rows);
                NP2[indexMonarch][indexGenome] = bestMonarch[indexGenome];
                free(bestMonarch);
            } else {
                int autremonarch = rand() % n_rows;
                NP2[indexMonarch][indexGenome] = NP2[autremonarch][indexGenome];
            }
        }
    }
    return NP2;
}
