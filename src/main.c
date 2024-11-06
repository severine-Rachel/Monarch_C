#include "instance_gen.h"
#include "Monarch_gen.h"
#include "cost_delay.h"
#include "Monarch_sort.h"
#include "deepcopy.h"
#include "operator.h"
#include "best_worst.h"
#include "utils.h"
#include "Monarch_selec.h"
#include "instance_gen.c"
#include "Monarch_gen.c"
#include "cost_delay.c"
#include "Monarch_sort.c"
#include "deepcopy.c"
#include "operator.c"
#include "best_worst.c"
#include "utils.c"
#include "Monarch_selec.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** Assembler(int ** population, int ** swarm1, int ** swarm2, int num_monarch, int num_swarm, int num_tasks){
    int n_all = num_monarch + num_swarm*2;
    int **AllMonarch = (int **)malloc(n_all * sizeof(int *));
    for (int i = 0; i < n_all; i++) {
        AllMonarch[i] = (int *)malloc(num_tasks * sizeof(int));
    }
    for (int i = 0; i < num_swarm; i++) {
        for (int j = 0; j < num_tasks; j++) {
            AllMonarch[i][j] = swarm1[i][j];
        }
    }
    for (int i = num_swarm; i < num_monarch; i++) {
        for (int j = 0; j < num_tasks; j++) {
            AllMonarch[i][j] = swarm2[i - num_swarm][j];
        }
    }
    for (int i = num_monarch; i < n_all; i++) {
        for (int j = 0; j < num_tasks; j++) {
            AllMonarch[i][j] = population[i - num_monarch][j];
        }
    }
    return AllMonarch;
}

int main() {
   // INITIALISATION 
    printf("\n ________________________________________\n\n INITIALISATION \n ________________________________________\n");
    double ** costTable = task_from_file("../Datasets/dataset_200/CostTable_R_200_0.csv");
    double ** delayTable = task_from_file("../Datasets/dataset_200/ExecutionTable_R_200_0.csv");
    int num_nodes = get_row("../Datasets/dataset_200/CostTable_R_200_0.csv");
    int num_tasks = get_col("../Datasets/dataset_200/CostTable_R_200_0.csv");
    int num_monarch = 4;
    int num_swarm = num_monarch/2;
    int ** population = generate_population(num_tasks, num_monarch);

    //printDoubleTable(costTable, num_nodes, num_tasks, "Cost table :\n");
    //printIntTable(population, num_monarch, num_tasks, "Population table :\n");

    int **swarm1 = (int **)malloc(num_swarm * sizeof(int *));
    int **swarm2 = (int **)malloc(num_swarm * sizeof(int *));
    for (int i = 0; i < num_swarm; i++) {
        swarm1[i] = (int *)malloc(num_tasks * sizeof(int));
        swarm2[i] = (int *)malloc(num_tasks * sizeof(int));
    }
    for (int i = 0; i < num_swarm; i++) {
        for (int j = 0; j < num_tasks; j++) {
            swarm1[i][j] = population[i][j];
        }
    }

    //printIntTable(swarm1, num_swarm, num_tasks, "Swarm 1 :\n");
    
    for (int i = num_swarm; i < num_monarch; i++) {
        for (int j = 0; j < num_tasks; j++) {
            swarm2[i - num_swarm][j] = population[i][j];
        }
    }
    
    //printIntTable(swarm1, num_swarm, num_tasks, "Swarm 1 :\n");
    //printIntTable(swarm2, num_swarm, num_tasks, "Swarm 2 :\n");

    swarm1 = migration_operator(swarm1, swarm2, num_swarm, num_tasks, 0.5);
    swarm2 = adjusting_operator(swarm1, swarm2, population, 0.5, 1, num_swarm, num_tasks, costTable, delayTable);

    printf("\n ________________________________________\n\n POST MIGRATION \n ________________________________________\n ");
    //printIntTable(swarm1, num_swarm, num_tasks, "Swarm 1 :\n");
    //printIntTable(swarm2, num_swarm, num_tasks, "Swarm 2 :\n");
    int n_all = num_monarch+num_swarm*2;
    int ** AllMonarch = Assembler(population, swarm1, swarm2, num_monarch, num_swarm, num_tasks);
    //printIntTable(AllMonarch, n_all, num_tasks, "All Monarch :\n");


    PopulationSelection(&population, AllMonarch, num_monarch, n_all, costTable, delayTable, num_tasks);
    //printIntTable(population, num_monarch, num_tasks, "Population table :\n");
    printf("\n ________________________________________\n\n FIN \n ________________________________________\n ");
    free2DTable((void**)costTable, num_nodes);
    free2DTable((void**)delayTable, num_nodes);
    
    free2DTable((void**)swarm1, num_swarm);
    free2DTable((void**)swarm2, num_swarm);
    free2DTable((void**)AllMonarch, n_all);
    

    free2DTable((void**)population, num_monarch);
    return 0;
    
}