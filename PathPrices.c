#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "Board.h"
#include "PathPrices.h"

static int findAllPathsRec(Board board, treeNode *root, Position *dst, int *prices);
static int* allocatePricesArray(size_t size);
static void reallocatePricesArray(int **prices, size_t size);
static void mergeSort(int *prices, int left, int right);

int findAllPathsSortedPrices(Board board, pathTree *tree, Position *dst, int **prices)
{
    *prices = allocatePricesArray(100);
    
    int size = 0;
    if (tree->root)
        size = findAllPathsRec(board, tree->root, dst, *prices);

    // Reduce memory size of array
    reallocatePricesArray(prices, size);
    
    // Sort array
    mergeSort(*prices, 0, size - 1);
    
    return size;
}

void freePricesArray(int *prices)
{
    free(prices);
}

static int* allocatePricesArray(size_t size)
{
    int *prices = (int*)malloc(sizeof(int) * size);
    if (!prices)
    {
        printf("Malloc Error");
        exit(MALLOC_ERROR);
    }
    return prices;
}

static void reallocatePricesArray(int **prices, size_t size)
{
    *prices = (int*)realloc(*prices, sizeof(int) * size);
    if (!prices)
    {
        printf("Malloc Error");
        exit(MALLOC_ERROR);
    }
}


static int findAllPathsRec(Board board, treeNode *root, Position *dst, int *prices)
{
    // Base case - destination is found
    if (isPositionsEqual(&root->position, dst))
    {
        prices[0] = getPriceOfCell(board, dst);
        return 1;
    }
    // Base case 2 - root is a leaf, destination not found
    else if (!root->left && !root->right && !root->up && !root->down)
    {
        return 0;
    }
    
    int dstCount = 0;
    
    if (root->left)
    {
        dstCount += findAllPathsRec(board, root->left, dst, prices + dstCount);
    }
    if (root->right)
    {
        dstCount += findAllPathsRec(board, root->right, dst, prices + dstCount);
    }
    if (root->up)
    {
        dstCount += findAllPathsRec(board, root->up, dst, prices + dstCount);
    }
    if (root->down)
    {
        dstCount += findAllPathsRec(board, root->down, dst, prices + dstCount);
    }
    
    for (int i = 0; i < dstCount; ++i)
    {
        prices[i] += getPriceOfCell(board, &root->position);
    }
    
    return dstCount;
}

static void merge(int *prices, int left, int mid, int right)
{
    int *temp = allocatePricesArray(right - left + 1);
    
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (prices[i] <= prices[j])
            temp[k++] = prices[i++];
        else
            temp[k++] = prices[j++];
    }
    while (i <= mid)
        temp[k++] = prices[i++];
    
    while (j <= right)
        temp[k++] = prices[j++];
    
    while (k--, k >= 0)
        prices[left + k] = temp[k];
    
    freePricesArray(temp);
}

static void mergeSort(int *prices, int left, int right)
{
    if (right <= left)
        return;
    
    int mid = (right + left)/2;
    mergeSort(prices, left, mid);
    mergeSort(prices, mid + 1, right);
    merge(prices, left, mid, right);
}
