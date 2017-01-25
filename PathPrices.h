#ifndef  __PATH_PRICES_H__
#define __PATH_PRICES_H__

#include <stdio.h>
#include "PositionList.h"
#include "PathTree.h"

int findAllPathsSortedPrices(Board board, PathTree *tree, Position *dst, int **prices);
TreeNode *findTheCheapestPathEndNode(Board board, TreeNode *node, Position *dst);
PositionList *findTheCheapestPath(Board board, PathTree *tree, Position *dst);

#endif
