#ifndef  __PATH_PRICES_H__
#define __PATH_PRICES_H__

#include <stdio.h>
#include "PositionList.h"
#include "pathTree.h"

int findAllPathsSortedPrices(Board board, pathTree *tree, Position *dst, int **prices);
treeNode *findTheCheapestPathEndNode(Board board, treeNode *node, Position *dst);
PositionList *findTheCheapestPath(Board board, pathTree *tree, Position *dst);
void freePricesArray(int *prices);

#endif
