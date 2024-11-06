float Cost(double ** tab_instance, int * monarch, int num_cols)
{
    /*
    printf(" cost table \n");
    for (int j = 1; j< 200; j++){
        printf(" %f ", tab_instance[0][j]);
    }
        printf("\n");
    printf("\n num_cols : %d \n", num_cols);
    */
    float TotalCost = 0;
    for(int index = 0; index< num_cols; index++)
    {

        int Task = monarch[index];
        TotalCost = TotalCost + tab_instance[Task-1][index];
    }
    return TotalCost;
}
float Delay(double **tab_instance, int *monarch, int num_cols) {
    float *TotalTime = calloc(13, sizeof(float));  // Initialiser à zéro
    if (TotalTime == NULL) {
        perror("Erreur d'allocation de mémoire pour TotalTime");
        exit(EXIT_FAILURE);
    }
    
    for(int index = 0; index < num_cols; index++) {
        int Task = monarch[index];
        TotalTime[Task-1] += tab_instance[Task-1][index];
    }

    float maxTime = 0;
    for (int index = 0; index < 13; index++) {
        if (TotalTime[index] > maxTime) maxTime = TotalTime[index];
    }

    free(TotalTime);
    return maxTime;
}