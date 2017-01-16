#ifndef  __PATH_H__
#define __PATH_H__

#include "Board.h"

typedef struct  _treeNode
{
	Position position;
	struct _treeNode *up, *down, *right, *left;
} treeNode;

typedef struct _pathTree {
	treeNode *root;
} pathTree;

pathTree findAllPossiblePaths(Board board, Position *startingPosition);
void printInOrder(pathTree tree);

#endif
