// is_dominated(i1, i2, monarch1, monarch2):
#ifndef MONARCHSORT
#define MONARCHSORT


int is_dominated(int i1, int i2, int * monarch1, int *monarch2, double ** costTable, double ** delayTable, int num_cols);
void dominationSort(int ** GroupMonarchs, double ** costTable, double ** delayTable, int num_cols, int *** Front, int ***Second, int *frontSize, int *secondSize, int n_rows);
void sortingMonarch(int ** Population, float** SortCost, float** SortDelay, int*** SortFront, int* frontSize, double ** costTable, double ** delayTable, int num_cols, int num_rows);

#endif