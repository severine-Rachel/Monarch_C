#ifndef BESTWORST
#define BESTWORST
void determineBestMonarch(int ** population, double ** costTable, double ** delayTable, int num_cols, float bin, int ** bestMonarch, int num_rows);
int determineWorstMonarch(int ** Population, double ** costTable, double ** delayTable, int num_cols, int num_rows);
#endif