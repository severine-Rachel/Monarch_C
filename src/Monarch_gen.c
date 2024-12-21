#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Monarch_gen.h" 

void generate_solution(int *solution, int num_tasks) {
    for (int index = 0; index < num_tasks; index++) {
        solution[index] = rand() % 13 + 1; //random nodes allocated to the task
    }
}

int ** generate_population(int num_tasks, int num_monarch) {
    srand(time(NULL));
    int **Population = malloc(num_monarch * sizeof(int *));
    
    for (int i = 0; i < num_monarch; i++) {
        Population[i] = malloc(num_tasks * sizeof(int)); 
    }

    for (int i = 0; i < num_monarch; i++) {
        generate_solution(Population[i], num_tasks);
    }
    


    return Population;
}
