#ifndef  __PATH_TREE_H__
#define __PATH_TREE_H__

#include "Board.h"

typedef struct  _treeNode
{
    Position position;
    struct _treeNode *up, *down, *right, *left;
} TreeNode;

typedef struct _pathTree {
    TreeNode *root;
} PathTree;

PathTree findAllPossiblePaths(Board board, Position *startingPosition);
void printInOrder(PathTree tree);

#endif
