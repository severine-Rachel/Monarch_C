#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Monarch_sort.h"
#include "cost_delay.h"
#include "utils.h"


/*
Unsorted_Pareto p = {NULL, NULL};


void truc() {

Unsorted_Pareto* p2;
p2->Front = (int**) malloc (4* sizeof(int));
(*p2).Front = NULL;

Unsorted_Pareto p3;
p3.Front = NULL;
Unsorted_Pareto p4 = function();
}
*/
int is_dominated(int i1, int i2, int * monarch1, int *monarch2, double ** costTable, double ** delayTable, int num_cols)
{
    float CostMonarch1 = Cost(costTable, monarch1, num_cols);
    float TimeMonarch1 = Delay(delayTable, monarch1, num_cols);
    float CostMonarch2 = Cost(costTable, monarch2, num_cols);
    float TimeMonarch2 = Delay(delayTable, monarch2, num_cols);
    if (CostMonarch1 >= CostMonarch2 && TimeMonarch1 > TimeMonarch2) return 1;
    if (CostMonarch1 > CostMonarch2 && TimeMonarch1 >= TimeMonarch2) return 1;
    if (i2 > i1 && CostMonarch1 == CostMonarch2 && TimeMonarch1 == TimeMonarch2) return 1;
    return 0;
}

//vérifier que la fonction prend bien des population de monarch de toutes tailles
void dominationSort(int ** GroupMonarchs, double ** costTable, double ** delayTable, int num_cols, int *** Front, int ***Second, int *frontSize, int *secondSize, int n_rows)
{
    *frontSize = 0;
    *secondSize = 0;
    for (int i1 = 0; i1 < n_rows; i1++) {
        int dominated_coeffiscient = 0;
        for (int i2 = 0; i2 < n_rows; i2++) 
                dominated_coeffiscient += is_dominated(i1, i2, GroupMonarchs[i1], GroupMonarchs[i2], costTable, delayTable, num_cols);
        if (dominated_coeffiscient == 0) 
            (*frontSize)++;
        else 
            (*secondSize)++;
    }
    *Front = (int **)calloc(*frontSize, sizeof(int *));
    *Second = (int **)calloc(*secondSize, sizeof(int *));

    int a = 0, b = 0;
    for (int i1 = 0; i1 < n_rows; i1++) {
        int dominated_coeffiscient = 0;
        for (int i2 = 0; i2 < n_rows; i2++) 
            dominated_coeffiscient += is_dominated(i1, i2, GroupMonarchs[i1], GroupMonarchs[i2], costTable, delayTable, num_cols);
        if (dominated_coeffiscient == 0) {
            (*Front)[a] = (int *)malloc(num_cols * sizeof(int));
            for (int j = 0; j < num_cols; j++) 
                (*Front)[a][j] = GroupMonarchs[i1][j];
            a++;
        }
        else {
            (*Second)[b] = (int *)malloc(num_cols * sizeof(int));
            for (int j = 0; j < num_cols; j++) 
                (*Second)[b][j] = GroupMonarchs[i1][j];

            b++;
        }
    }
}


/*
struct Pareto{
    int **SortCost;
    int **SortDelay;
    int **SortFront;
};
typedef struct Pareto Unsorted_Pareto;


Unsorted_Pareto sortingMonarch(int ** Pop, int ** Front, int ** Second)
{
    Unsorted_Pareto p = {NULL, NULL, NULL};
    
}
*/

void sortingMonarch(int ** population, float** sortCost, float** sortDelay, int *** Front, int *frontSize, double ** costTable, double ** delayTable, int num_cols, int num_rows)
{
        int **Second = NULL;
        
        int secondSize = 0;
        dominationSort(population, costTable, delayTable, num_cols, Front, &Second, frontSize, &secondSize, num_rows);

        free2DTable((void**)Second, secondSize);

        (*sortCost) = (float *)malloc((*frontSize) * sizeof(float));
        (*sortDelay) = (float *)malloc((*frontSize) * sizeof(float));
        
        for (int i = 0; i < (*frontSize); i++)
        {
            float costMonarch = Cost(costTable, (*Front)[i], num_cols);
            float delayMonarch = Delay(delayTable, (*Front)[i], num_cols); 
            (*sortCost)[i] = costMonarch;
            (*sortDelay)[i] = delayMonarch;
        }

        quicksortDict((*sortCost), (*Front), 0, (*frontSize) - 1, num_cols);
        quicksort((*sortDelay), 0, (*frontSize) - 1);


}