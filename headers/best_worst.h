#ifndef BESTWORST
#define BESTWORST
void determineBestMonarch(int ** population, double ** costTable, double ** delayTable, int num_cols, int bin, int ** bestMonarch);
int determineWorstMonarch(int ** Population, double ** costTable, double ** delayTable, int num_cols);
#endif