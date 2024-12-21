#ifndef COSTDELAY
#define COSTDELAY


float Cost(double ** tab_instance, int * monarch, int num_cols);
float Delay(double ** tab_instance, int * monarch, int num_cols);
int findMinCost(int ** population, int num_rows, int num_cols, double ** costTable);
int findMinDelay(int ** population, int num_rows, int num_cols, double ** delayTable);
#endif