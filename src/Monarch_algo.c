#include <stdio.h>
#include <stdlib.h>

#include "Monarch_algo.h"

int ** MonarchAlgorithm(int n_iter, double ** costTable, double ** delayTable, int num_nodes, int num_tasks, int num_monarch, int num_swarm, float p, float bin){
    int ** population = generate_population(num_tasks, num_monarch);
    int **swarm1 = (int **)malloc(num_swarm * sizeof(int *));
    int **swarm2 = (int **)malloc(num_swarm * sizeof(int *));
    float * tabCostMin = (float*)malloc(n_iter * sizeof(float));
    float * tabDelayMin = (float*)malloc(n_iter * sizeof(float));
    for (int i = 0; i < num_swarm; i++) {
        swarm1[i] = (int *)malloc(num_tasks * sizeof(int));
        swarm2[i] = (int *)malloc(num_tasks * sizeof(int));
    }
    dividePop(population, swarm1, swarm2, num_monarch, num_swarm, num_tasks);

    for(int iter = 0; iter < n_iter; iter ++)
    {   
        swarm1 = migration_operator(swarm1, swarm2, num_swarm, num_tasks, p);
        swarm2 = adjusting_operator(swarm1, swarm2, population, p, bin, num_swarm, num_tasks, costTable, delayTable);

        int n_all = num_monarch+num_swarm*2;
        int ** AllMonarch = Assembler(population, swarm1, swarm2, num_monarch, num_swarm, num_tasks);

        PopulationSelection(&population, AllMonarch, num_monarch, n_all, costTable, delayTable, num_tasks);
        float minCost = findMinCost(population, num_monarch, num_tasks, costTable);
        float minDelay = findMinDelay(population, num_monarch, num_tasks, delayTable);
        tabCostMin[iter] = minCost;
        tabDelayMin[iter] = minDelay;
        dividePop(population, swarm1, swarm2, num_monarch, num_swarm, num_tasks);
    }
    //size_t size = sizeof(tabDelayMin) / sizeof(tabDelayMin[0]);
    //save_to_csv("delayMin.csv", tabDelayMin, size);
    
    free(tabCostMin);
    free(tabDelayMin);
    free2DTable((void**)swarm1, num_swarm);
    free2DTable((void**)swarm2, num_swarm);
    return population;

}