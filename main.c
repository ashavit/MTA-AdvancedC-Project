//
//  main.c
//  Advanced Programming - Project
//
//  Created by Amir Shavit on 28/11/2016.
//  Copyright © 2016 Amir Shavit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR -1
#define BOARD_SIZE 4

#pragma mark - Data Model

typedef char Position[2];
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef struct _PositionArray
{
    unsigned int logical_size, pysical_size;
    Position *positions;
} PositionArray;

typedef struct _PositionListCell
{
    Position position;
    struct _PositionListCell *next;
} PositionListCell;

typedef struct _PositionList
{
    PositionListCell *head, *tail;
} PositionList;

#pragma mark - Main

void loadMenu();
PositionArray *greedyCheapPath(Board board, Position *src, Position *dst);

int main()
{
    // insert code here...
    printf("Hello, World!\n");
    
    loadMenu();
    
    return 0;
}

#pragma mark - Helper Methods

int arrayRowNumber(char cRow)
{
    return (cRow - 'A');
}

char arrayRowIndex(int row)
{
    return (row + 'A');
}

int arrayColNumber(char cCol)
{
    return (cCol - '1');
}

char arrayColIndex(int col)
{
    return (col + '1');
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

#pragma mark Allcations

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

void doublePositionsArraySize(Position **array, unsigned int *size)
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

void clearPositionArray(PositionArray *array)
{
    /// TODO: Amir: This is not working
    
    array->positions = NULL;
    array->logical_size = array->pysical_size = 0;
}

#pragma mark Comparisons

int isPositionsEqual(Position *a, Position *b)
{
    return ((*a)[0] == (*b)[0] && (*a)[1] == (*b)[1]);
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

/* Return cheaper cell if exist, or null if doesn't exist or if price is 0 */
Position* cheaperCellPosition(Board board, Position *a, Position *b)
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

Position* findCheapestCellNeighbor(Board board, Position *src)
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
void addPositionToPositionArray(PositionArray* posArr, Position* pos)
{
    // Check if we have space
    if (posArr->logical_size == posArr->pysical_size)
    {
        doublePositionsArraySize(&(posArr->positions), &(posArr->pysical_size));
    }
    
    unsigned int p = posArr->logical_size;

    /// TODO: Amir: This is ugly ?!?
    posArr->positions[p][0] = (*pos)[0];
    posArr->positions[p][1] = (*pos)[1];
    ++(posArr->logical_size);
}

void recursiveGreedyCheapPath(Board board, Position *src, Position *dst, PositionArray* posArr)
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

#pragma mark - Public Methods

void loadMenu()
{
    Board board = { { 97, 104, 56, 105 }, { 103, 57, 50, 122 }, { 121, 97, 65, 98 }, { 53, 115, 50, 52 } };
    printBoard(board);
    int option;
    
    printf("1. Load a board from file\n");
    printf("2. Enter a source postition and destination\n");
    printf("3. Find a greedy cheap pah between the source and destination\n");
    printf("4. Create a tree of all possible paths starting fmor the source position\n");
    printf("5. Find all sorted path prices starting frmo source\n");
    printf("6. Find he cheapest path between source and destination\n");
    printf("7. Exit\n");
    scanf("%d", &option);
    
    switch (option)
    {
        case 3:
        {
            Position* src = allocatePositionObject('A', '4');
            Position* dst = allocatePositionObject('D', '1');
            
//            greedyCheapPath(board, src, src);
            greedyCheapPath(board, src, dst);
//            greedyCheapPath(board, src, dst);
            break;
        }
            
        default:
            break;
    }
}

PositionArray *greedyCheapPath(Board board, Position *src, Position *dst)
{
    PositionArray *posArray = allocatePositionArrayObject();
    
    recursiveGreedyCheapPath(board, src, dst, posArray);
    
    return posArray;
}
