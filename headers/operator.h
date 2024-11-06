#ifndef OPERATOR
#define OPERATOR

int** migration_operator(int **NP1, int **NP2,int n_rows, int n_cols, float p);
int** adjusting_operator(int **NP1, int **NP2, int ** Population, float p, int bin, int n_rows, int n_cols, double ** costTable, double ** delayTable);
#endif