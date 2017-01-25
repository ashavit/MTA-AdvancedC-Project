#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "PathTree.h"

static TreeNode *createNewTNode(Position currPosition, TreeNode *left, TreeNode *right, TreeNode *up, TreeNode *down);
static PathTree allocateEmptyTree(void);
static TreeNode * findAllPossiblePathsHelper(Board board, Position *startingPosition);
static void printInOrderAux(TreeNode* root);

void printInOrder(PathTree tree)
{
    if (tree.root != NULL)
        printInOrderAux(tree.root);
    printf("\n");
}

static void printInOrderAux(TreeNode* root)
{
    // Print Position
    printf("%c%c ", root->position[0], root->position[1]);
    
    if (root->left != NULL)
        printInOrderAux(root->left);
    if (root->right != NULL)
        printInOrderAux(root->right);
    if (root->up != NULL)
        printInOrderAux(root->up);
    if (root->down != NULL)
        printInOrderAux(root->down);
}

static PathTree allocateEmptyTree(void) {
    PathTree emptyTree;
    emptyTree.root = NULL;
    return emptyTree;
}

//the function create new tree node
static TreeNode *createNewTNode(Position currPosition, TreeNode *left, TreeNode *right, TreeNode *up, TreeNode *down)
{
    TreeNode *res;
    res = (TreeNode*)malloc(sizeof(TreeNode));
    if (!res)
    {
        printf("Could not allocate Position object");
        exit(MALLOC_ERROR);
    }
    res->position[0] = currPosition[0];
    res->position[1] = currPosition[1];
    res->left = left;
    res->right = right;
    res->up = up;
    res->down = down;
    return res;
}

PathTree findAllPossiblePaths(Board board, Position *startingPosition)
{
    PathTree possiblePathsTree = allocateEmptyTree();
    possiblePathsTree.root = findAllPossiblePathsHelper(board, startingPosition);
    return possiblePathsTree;
}

static TreeNode * findAllPossiblePathsHelper(Board board, Position *startingPosition)
{
    TreeNode *res;
    Position *leftPos, *rightPos, *upPos, *downPos;
    res = createNewTNode(*startingPosition, NULL, NULL, NULL, NULL);
    int curRow = arrayRowNumber((*startingPosition)[0]);
    int curCol = arrayColNumber((*startingPosition)[1]);
    
    // Check if up is possible
    if (!validatePosition(board, startingPosition, "left") && !validatePosition(board, startingPosition, "right")
        && !validatePosition(board, startingPosition, "up") && !validatePosition(board, startingPosition, "down"))
    {
        return res;
    }
    else
    {
        char tempPrice = getPriceOfCell(board, startingPosition);
        setPriceOfCell(board, startingPosition, '0');
        
        if (validatePosition(board, startingPosition, "left"))
        {
            leftPos = allocatePositionObject(arrayRowIndex(curRow), arrayColIndex(curCol - 1));
            res->left = findAllPossiblePathsHelper(board, leftPos);
        }
        if (validatePosition(board, startingPosition, "right"))
        {
            rightPos = allocatePositionObject(arrayRowIndex(curRow), arrayColIndex(curCol + 1));
            res->right = findAllPossiblePathsHelper(board, rightPos);
        }
        if (validatePosition(board, startingPosition, "up"))
        {
            upPos = allocatePositionObject(arrayRowIndex(curRow - 1), arrayColIndex(curCol));
            res->up = findAllPossiblePathsHelper(board, upPos);
        }
        if (validatePosition(board, startingPosition, "down"))
        {
            downPos = allocatePositionObject(arrayRowIndex(curRow + 1), arrayColIndex(curCol));
            res->down = findAllPossiblePathsHelper(board, downPos);
        }
        
        setPriceOfCell(board, startingPosition, tempPrice);
        return res;
    }
    
}
