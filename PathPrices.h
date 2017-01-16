#ifndef  __PATH_PRICES_H__
#define __PATH_PRICES_H__

#include <stdio.h>
#include "pathTree.h"

int findAllPathsSortedPrices(Board board, pathTree *tree, Position *dst, int **prices);
void freePricesArray(int *prices);

#endif
