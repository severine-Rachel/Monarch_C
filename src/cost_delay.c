float Cost(double ** tab_instance, int * monarch, int num_cols)
{
    float TotalCost = 0;
    for(int index = 1; index<num_cols; index++)
    {   
        int Task = monarch[index-1];
        //printf("%d : ",Task);
        TotalCost = TotalCost + tab_instance[Task-1][index];
        //printf("%f\n", tab_instance[Task-1][index]);
    }
    return TotalCost;
}
float Delay(double **tab_instance, int *monarch, int num_cols) {

    float *TotalTime = calloc(13, sizeof(float));  // Initialiser à zéro
    for(int index = 1; index < num_cols; index++) {
        int Task = monarch[index-1];
        TotalTime[Task-1] += tab_instance[Task-1][index];
    }

    float maxTime = 0;
    for (int index = 0; index < 13; index++) {
        if (TotalTime[index] > maxTime) maxTime = TotalTime[index];
    }

    free(TotalTime);
    return maxTime;
}


int findMinCost(int ** population, int num_rows, int num_cols, double ** costTable){
    float minCost = Cost(costTable, population[0], num_cols);
    for (int i = 1; i < num_rows; i++){
        float currentCost = Cost(costTable, population[i], num_cols);
        if (currentCost < minCost) {
            minCost = currentCost;
        }
    }
    return minCost;
}

int findMinDelay(int ** population, int num_rows, int num_cols, double ** delayTable){
    float minDelay = Cost(delayTable, population[0], num_cols);
    for (int i = 1; i < num_rows; i++){
        float currentDelay = Cost(delayTable, population[i], num_cols);
        if (currentDelay < minDelay) {
            minDelay = currentDelay;
        }
    }
    return minDelay;
}