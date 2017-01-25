#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "Board.h"
#include "PathPrices.h"

typedef struct _sumAndPosArray
{
    unsigned int sum;
    treeNode *node;
} SumAndPosArray;


static int* allocatePricesArray(unsigned int size);
static SumAndPosArray* allocatePricesAndNodesArray(unsigned int size);
static void reallocatePricesAndNodesArray(SumAndPosArray **arr, unsigned int size);
static void doublePriceNodesArray(SumAndPosArray **arr, unsigned int *size);

static int findAllPathsAndNodesRec(Board board, treeNode *root, Position *dst, SumAndPosArray **arr, unsigned int *size, unsigned int index);
static void mergeSortPricesAndNode(SumAndPosArray *arr, int left, int right);
static BOOL findTheCheapestPathRec(PositionList **cheapestPathList, treeNode *root, treeNode *dstNode);


int findAllPathsSortedPrices(Board board, pathTree *tree, Position *dst, int **prices)
{
    unsigned int size = 1;
    SumAndPosArray *arr = allocatePricesAndNodesArray(size);
    
    int count = 0;
    if (tree->root)
        count = findAllPathsAndNodesRec(board, tree->root, dst, &arr, &size, count);

    // Reduce memory size of array
    reallocatePricesAndNodesArray(&arr, count);
    
    // Sort array
    mergeSortPricesAndNode(arr, 0, count - 1);
    
    // Final array size by count of price-node structs found
    *prices = allocatePricesArray(count);
    for (int i = 0; i < count; i++)
        *(*prices + i) = arr[i].sum;
    
    // Free price-node array
    free(arr);
    
    return count;
}

treeNode *findTheCheapestPathEndNode(Board board, treeNode *node, Position *dst)
{
    unsigned int size = 1;
    SumAndPosArray *arr = allocatePricesAndNodesArray(size);
    
    int count = 0;
    if (node)
        count = findAllPathsAndNodesRec(board, node, dst, &arr, &size, count);
    
    // Reduce memory size of array
    reallocatePricesAndNodesArray(&arr, count);
    
    // Sort array
    mergeSortPricesAndNode(arr, 0, count - 1);
    treeNode *result = (arr[0]).node;
    
    // Free price-node array
    free(arr);

    return result;
}

PositionList *findTheCheapestPath(Board board, pathTree *tree, Position *dst)
{
    if (!tree || !tree->root || !dst)
        return NULL;
    
    treeNode *dstNode = findTheCheapestPathEndNode(board, tree->root, dst);
    PositionList *cheapestPathList = allocatePositionList();
    
    BOOL pathFound = FALSE;
    pathFound = findTheCheapestPathRec(&cheapestPathList, tree->root, dstNode);
    return cheapestPathList;
}

static int* allocatePricesArray(unsigned int size)
{
    int *prices = (int*)malloc(sizeof(int) * size);
    if (!prices)
    {
        printf("Malloc Error");
        exit(MALLOC_ERROR);
    }
    return prices;
}

static SumAndPosArray* allocatePricesAndNodesArray(unsigned int size)
{
    SumAndPosArray *arr = (SumAndPosArray*)malloc(sizeof(SumAndPosArray) * size);
    if (!arr)
    {
        printf("Malloc Error");
        exit(MALLOC_ERROR);
    }
    return arr;
}

static void reallocatePricesAndNodesArray(SumAndPosArray **arr, unsigned int size)
{
    *arr = (SumAndPosArray*)realloc(*arr, sizeof(SumAndPosArray) * size);
    if (!arr)
    {
        printf("Malloc Error");
        exit(MALLOC_ERROR);
    }
}

static void doublePriceNodesArray(SumAndPosArray **arr, unsigned int *size)
{
    unsigned int newSize = *size * 2;
    reallocatePricesAndNodesArray(arr, newSize);
    *size = newSize;
}

static int findAllPathsAndNodesRec(Board board, treeNode *root, Position *dst, SumAndPosArray **arr, unsigned int *size, unsigned int index)
{
    // Base case - destination is found
    if (isPositionsEqual(&root->position, dst))
    {
        if (index == *size)
        {
            doublePriceNodesArray(arr, size);
        }
        (*(*arr + index)).sum = getPriceOfCell(board, dst);
        (*(*arr + index)).node = root;
        return 1;
    }
    // Base case 2 - root is a leaf, destination not found
    else if (!root->left && !root->right && !root->up && !root->down)
    {
        return 0;
    }
    
    int dstCount = 0;
    
    // Recursive calls to find paths by children
    if (root->left)
        dstCount += findAllPathsAndNodesRec(board, root->left, dst, arr, size, index + dstCount);

    if (root->right)
        dstCount += findAllPathsAndNodesRec(board, root->right, dst, arr, size, index + dstCount);

    if (root->up)
        dstCount += findAllPathsAndNodesRec(board, root->up, dst, arr, size, index + dstCount);

    if (root->down)
        dstCount += findAllPathsAndNodesRec(board, root->down, dst, arr, size, index + dstCount);

    
    // Add current cell price to all children paths
    for (int i = 0; i < dstCount; ++i)
        (*(*arr + index + i)).sum += getPriceOfCell(board, &root->position);
    
    return dstCount;
}

static void mergePricesAndNodes(SumAndPosArray *arr, int left, int mid, int right)
{
    SumAndPosArray *temp = allocatePricesAndNodesArray(right - left + 1);
    
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if ((arr[i]).sum <= (arr[j]).sum)
            temp[k++] = (arr[i++]);
        else
            temp[k++] = (arr[j++]);
    }
    while (i <= mid)
        temp[k++] = (arr[i++]);
    
    while (j <= right)
        temp[k++] = (arr[j++]);
    
    while (k--, k >= 0)
        (arr[left + k]) = temp[k];
    
    if (temp != NULL)
        free(temp);
}

static void mergeSortPricesAndNode(SumAndPosArray *arr, int left, int right)
{
    if (right <= left)
        return;
    
    int mid = (right + left) / 2;
    mergeSortPricesAndNode(arr, left, mid);
    mergeSortPricesAndNode(arr, mid + 1, right);
    mergePricesAndNodes(arr, left, mid, right);
}

static BOOL findTheCheapestPathRec(PositionList **cheapestPathList, treeNode *root, treeNode *dstNode)
{
    //PositionListCell *newNode;
    BOOL nodeWasFoundUp = FALSE, nodeWasFoundDown = FALSE, nodeWasFoundRight = FALSE, nodeWasFoundLeft = FALSE;
    
    if (root == dstNode)
    {
        insertDataToBeginingList(*cheapestPathList, root->position);
        return TRUE;
    }
    else if (!root->left && !root->right && !root->up && !root->down)
    {
        return FALSE;
    }
    else {
        if (root->down)
            nodeWasFoundDown = findTheCheapestPathRec(cheapestPathList, root->down, dstNode);
        if (root->up)
            nodeWasFoundUp = findTheCheapestPathRec(cheapestPathList, root->up, dstNode);
        if (root->right)
            nodeWasFoundRight = findTheCheapestPathRec(cheapestPathList, root->right, dstNode);
        if (root->left)
            nodeWasFoundLeft = findTheCheapestPathRec(cheapestPathList, root->left, dstNode);
        
        if (nodeWasFoundDown || nodeWasFoundLeft || nodeWasFoundRight || nodeWasFoundUp) {
            insertDataToBeginingList(*cheapestPathList, root->position);
            return TRUE;
        }
        else
            return FALSE;
    }
}
