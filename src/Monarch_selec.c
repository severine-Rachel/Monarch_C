#include <stdlib.h>
#include <stdio.h>
#include "Monarch_selec.h"



void PopulationSelection(int *** population, int ** allMonarch, int n_pop, int n_all, double ** costTable, double ** delayTable, int n_cols){
    int newPopSize = 0;
    
    while (newPopSize < n_pop){
        printIntTable(allMonarch, n_all, n_cols, "All monarch 1 :\n");
        int **Front = NULL;
        int **Second = NULL;
        int frontSize = 0, secondSize = 0;
        dominationSort(allMonarch, costTable, delayTable, n_cols, &Front, &Second, &frontSize, &secondSize);
        for(int i = 0 + newPopSize; i < frontSize + newPopSize; i++){
            for(int j = 0; j < n_cols; j++){
                (*population)[i][j] =  Front[i - newPopSize][j];
            }
        }

        free2DTable((void**)allMonarch, n_all);
        int **allMonarch = deepcopy(Second, secondSize, n_cols); 
        free2DTable((void**)Front, frontSize);
        free2DTable((void**)Second, secondSize);
        newPopSize = newPopSize + frontSize;
        
        #ifdef false
        if (frontSize > n_pop){
            while(frontSize > n_pop){
                int indexWorstMonarch = determineWorstMonarch(Front, costTable, delayTable, n_cols);     
                int **newFront = malloc((frontSize - 1) * sizeof(int *));
                int newRow = 0;
                for (int i = 0; i < frontSize; i++) {
                    if (i == indexWorstMonarch) {
                        continue; // Ignorer la ligne à retirer
                    }
                    newFront[newRow] = malloc(n_cols * sizeof(int));
                    for (int j = 0; j < n_cols; j++) {
                        newFront[newRow][j] = Front[i][j];
                    }
                    newRow++;
                }
                free2DTable((void**)Front, frontSize);
                frontSize--;
                int **Front = deepcopy(newFront, frontSize, n_cols); 
                free2DTable((void**)newFront, frontSize);
                frontSize--;
            }
        }
        #endif
    }
 }
