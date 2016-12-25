//
//  Board.c
//  Advanced Programming - Project
//
//  Created by Amir Shavit on 25/12/2016.
//  Copyright © 2016 Amir Shavit. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "Board.h"

#pragma mark - Private Declarations

static int arrayRowNumber(char cRow);
static int arrayColNumber(char cCol);
static char arrayRowIndex(int row);
static char arrayColIndex(int col);

static void recursiveGreedyCheapPath(Board board, Position *src, Position *dst, PositionArray* posArr);
static void addPositionToPositionArray(PositionArray* posArr, Position* pos);
static void doublePositionsArraySize(Position **array, unsigned int *size);

static int isPositionsEqual(Position *a, Position *b);
/* Return cheaper cell if exist, or null if doesn't exist or if price is 0 */
static Position* cheaperCellPosition(Board board, Position *a, Position *b);
static Position* findCheapestCellNeighbor(Board board, Position *src);

#pragma mark - Public Methods

Position* allocatePositionObject(char row, char col)
{
    Position *ptr = (Position*)malloc(sizeof(Position));
    if (!ptr)
    {
        printf("Could not allocate Position object");
        exit(MALLOC_ERROR);
    }
    
    (*ptr)[0] = row;
    (*ptr)[1] = col;
    
    return ptr;
}

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

void clearPositionArray(PositionArray *array)
{
    /// TODO: Amir: This is not working
    
    array->positions = NULL;
    array->logical_size = array->pysical_size = 0;
}

PositionArray *greedyCheapPath(Board board, Position *src, Position *dst)
{
    PositionArray *posArray = allocatePositionArrayObject();
    
    recursiveGreedyCheapPath(board, src, dst, posArray);
    
    return posArray;
}

void printBoard(Board board)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            printf("%4d", board[row][col]);
        }
        printf("\n");
    }
}

unsigned char getPriceOfCell(Board board, Position *pos)
{
    int row = arrayRowNumber((*pos)[0]);
    int col = arrayColNumber((*pos)[1]);
    return (board[row][col]);
}

void setPriceOfCell(Board board, Position *pos, unsigned char price)
{
    int row = arrayRowNumber((*pos)[0]);
    int col = arrayColNumber((*pos)[1]);
    board[row][col] = price;
}

#pragma mark - Helper Methods

static int arrayRowNumber(char cRow)
{
    return (cRow - 'A');
}

static char arrayRowIndex(int row)
{
    return (row + 'A');
}

static int arrayColNumber(char cCol)
{
    return (cCol - '1');
}

static char arrayColIndex(int col)
{
    return (col + '1');
}

static void doublePositionsArraySize(Position **array, unsigned int *size)
{
    unsigned int newSize = (*size * 2) + 1;
    *array = (Position*)realloc(*array, newSize * sizeof(Position*));
    if (!array)
    {
        printf("Could not allocate Positions array");
        exit(MALLOC_ERROR);
    }
    *size = newSize;
}

#pragma mark Comparisons

static int isPositionsEqual(Position *a, Position *b)
{
    return ((*a)[0] == (*b)[0] && (*a)[1] == (*b)[1]);
}

/* Return cheaper cell if exist, or null if doesn't exist or if price is 0 */
static Position* cheaperCellPosition(Board board, Position *a, Position *b)
{
    if (!a && !b)
        return NULL;
    
    unsigned char priceA = 0;
    unsigned char priceB = 0;
    
    if (!a)
    {
        // Make sure b has valid price
        priceB = getPriceOfCell(board, b);
        return (priceB ? b : NULL);
    }
    
    if (!b)
    {
        // Make sure a has valid price
        priceA = getPriceOfCell(board, a);
        return (priceA ? a : NULL);
    }
    
    priceA = getPriceOfCell(board, a);
    priceB = getPriceOfCell(board, b);
    
    // Compare price and validity
    if (priceA && priceB) /* Compare 2 valid prices */
        return (priceA < priceB ? a : b);
    else if (priceA) /* Only a has valid price */
        return a;
    else if (priceB) /* Only b has valid price */
        return b;
    else /* Neither have valid price */
        return NULL;
}

static Position* findCheapestCellNeighbor(Board board, Position *src)
{
    Position *cheapest = NULL;
    Position *curr = NULL;
    
    int curRow = arrayRowNumber((*src)[0]);
    int curCol = arrayColNumber((*src)[1]);
    
    // Check if up is possible
    if (curRow - 1 >= 0)
    {
        // Check if top neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow - 1), arrayColIndex(curCol));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    // Check if down is possible
    if (curRow + 1 < BOARD_SIZE)
    {
        // Check if bottom neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow + 1), arrayColIndex(curCol));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    // Check if left is possible
    if (curCol - 1 >= 0)
    {
        // Check if left neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow), arrayColIndex(curCol - 1));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    // Check if right is possible
    if (curCol + 1 < BOARD_SIZE)
    {
        // Check if right neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow), arrayColIndex(curCol + 1));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    return cheapest;
}

#pragma mark -
static void addPositionToPositionArray(PositionArray* posArr, Position* pos)
{
    // Check if we have space
    if (posArr->logical_size == posArr->pysical_size)
    {
        doublePositionsArraySize(&(posArr->positions), &(posArr->pysical_size));
    }
    
    unsigned int p = posArr->logical_size;
    
    /// TODO: Amir: This is ugly ?!?
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
        /// TODO: Amir: This is copy right? so do we need to keep track?
        unsigned char keep = getPriceOfCell(board, src);
        setPriceOfCell(board, src, 0);
        
        // Recusive call with neighbor as src
        recursiveGreedyCheapPath(board, cheapestNeighbor, dst, posArr);
        
        // restore source value
        setPriceOfCell(board, src, keep);
    }
}

