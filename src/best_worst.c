#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "best_worst.h"
#include "utils.h"
#include "Monarch_sort.h"

// faire un test unitaire de cette fonction

void determineBestMonarch(int ** population, double ** costTable, double ** delayTable, int num_cols, int bin, int ** bestMonarch, int num_rows){
    float proba = (float)rand() / RAND_MAX;
    if (proba > bin){ //Random selection of Monarch of the Front
        int **Front = NULL;
        int **Second = NULL;
        int frontSize = 0, secondSize = 0;
        dominationSort(population, costTable, delayTable, num_cols, &Front, &Second, &frontSize, &secondSize, num_rows);
        free2DTable((void**)Second, secondSize);
        
        int min_front = 0;
        int max_front = frontSize;

        srand(time(NULL)); // Seed the random number generator
        int selectRandom = rand() % (max_front - min_front) + min_front;
        (*bestMonarch) = Front[selectRandom];
        free2DTable((void**)Front, frontSize);

    }
    else { //Selection by Crowding distance
        
        int ** Front = NULL;
        float * sortCost;
        float * sortDelay;
        int frontSize = 0;
        sortingMonarch(population, &sortCost, &sortDelay, &Front, &frontSize, costTable, delayTable, num_cols, num_rows);
        float *Crowding = (float *)calloc(frontSize, sizeof(float));
        
        if (frontSize > 0.5){
            for (int i = 0; i < frontSize; i++){
                if (i == 0 || i == frontSize - 1)
                    Crowding[i] = 0.0;
                else{
                    Crowding[i] = fabs(Cost(costTable, Front[i + 1], num_cols) - Cost(costTable, Front[i - 1], num_cols)) / (max(sortCost, frontSize) - min(sortCost, frontSize));
                    Crowding[i] = Crowding[i] + fabs(Delay(delayTable, Front[i + 1], num_cols) - Delay(delayTable, Front[i - 1], num_cols)) / (max(sortDelay, frontSize) - min(sortDelay, frontSize));
                }
            }
        }
        for (int i = 0; i < num_cols; i++){
            (*bestMonarch)[i] = Front[indexOfMax(Crowding, frontSize)][i];
        }
        free(sortCost);
        free(sortDelay);
        free2DTable((void**)Front, frontSize);
        free(Crowding);
    }
}



int determineWorstMonarch(int ** population, double ** costTable, double ** delayTable, int num_cols, int num_rows){
    int ** Front = NULL;
    float * sortCost;
    float * sortDelay;
    int frontSize = 0;
    sortingMonarch(population, &sortCost, &sortDelay, &Front, &frontSize, costTable, delayTable, num_cols, num_rows);
    float *Crowding = (float *)calloc(frontSize, sizeof(float));


    if (frontSize > 0.5){
        for (int i = 0; i < frontSize; i++){
            if (i == 0 || i == frontSize - 1)
                Crowding[i] = 0;
            else{
                Crowding[i] = fabs(Cost(costTable, Front[i + 1], num_cols) - Cost(costTable, Front[i - 1], num_cols)) / (max(sortCost, frontSize) - min(sortCost, frontSize));
                Crowding[i] = Crowding[i] + fabs(Delay(delayTable, Front[i + 1], num_cols) - Delay(delayTable, Front[i - 1], num_cols)) / (max(sortDelay, frontSize) - min(sortDelay, frontSize));
            }
        }
    }
    #ifdef false
    int *worstMonarch = (int *)calloc(num_cols, sizeof(int));
    for (int i = 0; i < num_cols; i++){
        worstMonarch[i] = Front[indexOfMin(Crowding, frontSize)][i];
    }
    #endif
    int indexWorstMonarch = indexOfMin(Crowding, frontSize);
    free(sortCost);
    free(sortDelay);
    free2DTable((void**)Front, frontSize);
    free(Crowding);
    return indexWorstMonarch;
}
