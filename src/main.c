#include "instance_gen.h"
#include "Monarch_gen.h"
#include "cost_delay.h"
#include "Monarch_sort.h"
#include "deepcopy.h"
#include "operator.h"
#include "best_worst.h"
#include "utils.h"
#include "Monarch_selec.h"
#include "Monarch_algo.h"
#include "register_csv.h"

#include "instance_gen.c"
#include "Monarch_gen.c"
#include "cost_delay.c"
#include "Monarch_sort.c"
#include "deepcopy.c"
#include "operator.c"
#include "best_worst.c"
#include "utils.c"
#include "Monarch_selec.c"
#include "Monarch_algo.c"
#include "register_csv.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




int main() {
   // INITIALISATION 
   //int monarch1[200] = {9, 11,  7, 13, 13,  7,  6,  5,  9, 11,  5,  3,  6,  5,  5,  9,  2, 11,  11,  5, 10,  3,  3,  5,  8,  2, 12, 11,  8,  7,  9,  7,  7,  6,  3, 10,  11,  6,  9,  1,  3,  2,  6,  3,  9,  3,  6, 11, 11,  3,  2,  5,  2,  8,  11, 11,  3,  6,  3, 10,  4,  2,  3, 10,  1,  2, 13,  3,  3,  8,  4,  5,  11,  3,  7, 10,  3,  9,  6,  9, 11,  8,  5, 13,  1,  8, 10, 13,  3,  9,   6,  5,  2,  5,  5,  9,  9,  8,  8,  6,  7,  2,  8, 13, 10, 11, 11,  7,  10,  7,  7, 11,  9,  4,  5, 11,  7,  3,  1,  8, 10, 12,  6,  8,  6,  3,   3,  6,  9,  6,  6,  6,  3,  8,  5,  2,  3,  1, 10, 13,  5,  3,  3,  9,   1,  5,  5,  2, 11,  8,  8, 13,  2,  9,  1,  9,  5, 13, 11,  7,  7,  8,  11,  4,  5,  3, 10,  5,  9, 13,  7,  3,  5,  5,  5,  2,  2,  9,  9,  7,   8,  2, 10, 11, 13,  3, 11,  9, 10,  6,  6,  5,  5, 11,  6, 11,  6,  9,  10, 11};
    #ifdef false
   double ** costTable_t = task_from_file("../Datasets/CostTable40.csv");
   int num_nodes = get_col("../Datasets/CostTable40.csv");
   printf("num node = %d ", num_nodes);
    float cost = Cost(costTable_t, monarch1, num_nodes);
    printf("\n%f\n", cost);
    free2DTable((void**)costTable_t, num_nodes);
    #endif
    double ** costTable = task_from_file("../Datasets/dataset_200/CostTable_R_200_0.csv");
    double ** delayTable = task_from_file("../Datasets/dataset_200/ExecutionTable_R_200_0.csv");
    
    int num_nodes = get_row("../Datasets/dataset_200/CostTable_R_200_0.csv");
    int num_tasks = get_col("../Datasets/dataset_200/CostTable_R_200_0.csv");
    //float cost = Cost(costTable, monarch1, num_tasks);
    //float delay = Delay(delayTable, monarch1, num_tasks);
    //printf("%f %f\n", cost, delay);
    int num_monarch = 20;
    int num_swarm = num_monarch/2; 
    int n_iter = 500;
    float bin = 1;
    float p = 0.5;
    clock_t start = clock();
    int ** population = MonarchAlgorithm(n_iter, costTable, delayTable, num_nodes, num_tasks, num_monarch, num_swarm, p, bin);
    printIntTable(population, num_monarch, num_tasks, "population = \n");
    float * costPareto = (float*)malloc(num_monarch * sizeof(float));
    float * delayPareto = (float*)malloc(num_monarch * sizeof(float));
    for (int i = 0; i < num_monarch; i++){
        costPareto[i] = Cost(costTable, population[i], num_tasks);
        delayPareto[i] = Delay(delayTable, population[i], num_tasks);
    }
    clock_t end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printFloatTable(costPareto, num_monarch, "pareto de cout de la population : \n");
    printFloatTable(delayPareto, num_monarch, "pareto de delais de la population : \n");

    printf("Temps écoulé : %f secondes\n", cpu_time_used);
    free(costPareto);
    free(delayPareto);
    free2DTable((void**)population, num_monarch);
    free2DTable((void**)costTable, num_nodes);
    free2DTable((void**)delayTable, num_nodes);
    return 0;
    
}