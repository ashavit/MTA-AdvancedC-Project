#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "PositionArray.h"

#pragma mark - Private Declarations

static void recursiveGreedyCheapPath(Board board, Position *src, Position *dst, PositionArray* posArr);
static void addPositionToPositionArray(PositionArray* posArr, Position* pos);
static void doublePositionsArraySize(Position **array, unsigned int *size);

#pragma mark - Public Methods

PositionArray* allocatePositionArrayObject()
{
    PositionArray *ptr = (PositionArray*)malloc(sizeof(PositionArray));
    if (!ptr)
    {
        printf("Could not allocate PositionArray object");
        exit(MALLOC_ERROR);
    }
    
    ptr->positions = NULL;
    ptr->logical_size = ptr->pysical_size = 0;
    return ptr;
}

void freePositionArray(PositionArray *array)
{
    clearPositionArray(array);
    free(array);
}

void clearPositionArray(PositionArray *array)
{
    if (array->positions)
    {
        free(array->positions);
        array->positions = NULL;
    }
    
    array->logical_size = array->pysical_size = 0;
}

void printPostionionsArray(PositionArray* posArr)
{
    printf("The cheapest path is:\n");
    for (int i = 0; i < posArr->logical_size; ++i)
    {
        printf("%d. %c%c\n", i + 1, posArr->positions[i][0], posArr->positions[i][1]);
    }
    printf("\n");
}

PositionArray *greedyCheapPath(Board board, Position *src, Position *dst)
{
    PositionArray *posArray = allocatePositionArrayObject();
    
    recursiveGreedyCheapPath(board, src, dst, posArray);
    
    return posArray;
}

#pragma mark - Private Methods

static void doublePositionsArraySize(Position **array, unsigned int *size)
{
    unsigned int newSize = (*size * 2) + 1;
    *array = (Position*)realloc(*array, newSize * sizeof(Position));
    if (!array)
    {
        printf("Could not allocate Positions array");
        exit(MALLOC_ERROR);
    }
    *size = newSize;
}

static void addPositionToPositionArray(PositionArray* posArr, Position* pos)
{
    // Check if we have space
    if (posArr->logical_size == posArr->pysical_size)
    {
        doublePositionsArraySize(&(posArr->positions), &(posArr->pysical_size));
    }
    
    unsigned int p = posArr->logical_size;
    
    strcpy(posArr->positions[p], *pos);
    ++(posArr->logical_size);
}

static void recursiveGreedyCheapPath(Board board, Position *src, Position *dst, PositionArray* posArr)
{
    if (isPositionsEqual(src, dst))
    {
        addPositionToPositionArray(posArr, dst);
        return;
    }
    
    // Find cheapest neighbor cell
    Position* cheapestNeighbor = findCheapestCellNeighbor(board, src);
    
    // If no next move - clear
    if (!cheapestNeighbor)
    {
        clearPositionArray(posArr);
        return;
    }
    else
    {
        // Add source to path
        addPositionToPositionArray(posArr, src);
        
        // Save source value as temp
        unsigned char keep = getPriceOfCell(board, src);
        setPriceOfCell(board, src, 0);
        
        // Recusive call with neighbor as src
        recursiveGreedyCheapPath(board, cheapestNeighbor, dst, posArr);
        
        // restore original value from temp
        setPriceOfCell(board, src, keep);
    }
}
