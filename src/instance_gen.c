#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instance_gen.h"

double **  task_from_file(char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int skip_header = 1;
    int num_rows = 0;
    int num_cols = 0;
    double **data;

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
    }

    // Count the number of rows and columns
    num_cols = get_col(filename);
    num_rows = get_row(filename);

    // Allocate memory for the data array
    data = (double **)malloc(num_rows * sizeof(double *));
    for (int i = 0; i < num_rows; i++) {
        data[i] = (double *)malloc(num_cols * sizeof(double));
    }

    // Rewind the file and read the data
    rewind(fp);
    skip_header = 1;
    int row = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (skip_header) {
            skip_header = 0;
            continue;
        }
        char *token = strtok(line, ",");
        int col = 0;
        while (token != NULL) {
            data[row][col] = atof(token);
            col++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    
    // Free memory and close the file
    free(line);
    int t = fclose(fp);
    
    return data;
}

int get_row(char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int skip_header = 1;
    int num_rows = 0;
    int num_cols = 0;
    int dim[2];

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
    }
    // Count the number of rows and columns
    while ((read = getline(&line, &len, fp)) != -1) {
        num_rows++;
    }
    free(line);
    fclose(fp);
    return num_rows - 1;
}

int get_col(char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int skip_header = 1;
    int num_cols = 0;

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
    }
    // Count the number of rows and columns
    while ((read = getline(&line, &len, fp)) != -1) {
        if (skip_header) {
            skip_header = 0;
            continue;
        }
        char *token = strtok(line, ",");
        num_cols = 0;
        while (token != NULL) {
            num_cols++;
            token = strtok(NULL, ",");
        }
    }
    free(line);
    fclose(fp);
    return num_cols;
}