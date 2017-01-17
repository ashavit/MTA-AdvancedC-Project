#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "Board.h"
#include "PathPrices.h"

static int findAllPathsRec(Board board, treeNode *root, Position *dst, int **prices, unsigned int *size, unsigned int index);
static int* allocatePricesArray(unsigned int size);
static void reallocatePricesArray(int **prices, unsigned int size);
static void doublePricesArray(int **prices, unsigned int *size);
static void mergeSort(int *prices, int left, int right);

int findAllPathsSortedPrices(Board board, pathTree *tree, Position *dst, int **prices)
{
    unsigned int size = 1;
    *prices = allocatePricesArray(size);
    
    int count = 0;
    if (tree->root)
        count = findAllPathsRec(board, tree->root, dst, prices, &size, count);

    // Reduce memory size of array
    reallocatePricesArray(prices, count);
    
    // Sort array
    mergeSort(*prices, 0, count - 1);
    
    return count;
}

void freePricesArray(int *prices)
{
    free(prices);
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

static void reallocatePricesArray(int **prices, unsigned int size)
{
    *prices = (int*)realloc(*prices, sizeof(int) * size);
    if (!prices)
    {
        printf("Malloc Error");
        exit(MALLOC_ERROR);
    }
}

static void doublePricesArray(int **prices, unsigned int *size)
{
    int newSize = *size * 2;
    reallocatePricesArray(prices, newSize);
    *size = newSize;
}

static int findAllPathsRec(Board board, treeNode *root, Position *dst, int **prices, unsigned int *size, unsigned int index)
{
    // Base case - destination is found
    if (isPositionsEqual(&root->position, dst))
    {
        if (index == *size)
        {
            doublePricesArray(prices, size);
        }
        *(*prices+index) = getPriceOfCell(board, dst);
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
    {
        dstCount += findAllPathsRec(board, root->left, dst, prices, size, index + dstCount);
    }
    if (root->right)
    {
        dstCount += findAllPathsRec(board, root->right, dst, prices, size, index + dstCount);
    }
    if (root->up)
    {
        dstCount += findAllPathsRec(board, root->up, dst, prices, size, index + dstCount);
    }
    if (root->down)
    {
        dstCount += findAllPathsRec(board, root->down, dst, prices, size, index + dstCount);
    }
    
    // Add current cell price to all children paths
    for (int i = 0; i < dstCount; ++i)
    {
        *(*prices + index + i) += getPriceOfCell(board, &root->position);
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
