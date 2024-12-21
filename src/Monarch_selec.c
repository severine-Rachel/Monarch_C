#include <stdlib.h>
#include <stdio.h>
#include "Monarch_selec.h"



void PopulationSelection(int *** population, int ** allMonarch, int n_pop, int n_all, double ** costTable, double ** delayTable, int n_cols){
    int newPopSize = 0;
    while (newPopSize < n_pop){
        
        //printIntTable(allMonarch, n_all, n_cols, "All monarch 1 :\n");
        int **Front = NULL;
        int **Second = NULL;
        int frontSize = 0, secondSize = 0;
        dominationSort(allMonarch, costTable, delayTable, n_cols, &Front, &Second, &frontSize, &secondSize, n_all);
        //printIntTable(Front, frontSize, n_cols, "Front 1 :\n");
        if (frontSize + newPopSize > n_pop){
            while(frontSize + newPopSize  > n_pop){
                int indexWorstMonarch = determineWorstMonarch(Front, costTable, delayTable, n_cols, frontSize);     
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
                Front = newFront; 
            }
        }

        //printf("%d", frontSize);
        //printIntTable(Front, frontSize, n_cols, "Front 2 :\n");
        for(int i = 0; i < frontSize; i++){
            for(int j = 0; j < n_cols; j++){
                (*population)[i + newPopSize][j] =  Front[i][j];
            }
        }
        int **newAllMonarch = deepcopy(Second, secondSize, n_cols);
        free2DTable((void**)allMonarch, n_all);
        allMonarch = newAllMonarch;
        //free2DTable((void**)newAllMonarch, n_all);
        n_all = secondSize;
        //printIntTable(allMonarch, n_all, n_cols, "All monarch 2 :\n");
        free2DTable((void**)Front, frontSize);
        free2DTable((void**)Second, secondSize);
        newPopSize = newPopSize + frontSize;
        //printIntTable((*population), newPopSize, n_cols, "Population après ajout :\n");
        
        #ifdef false
        
        #endif
    }
    free2DTable((void**)allMonarch, n_all);
 }
