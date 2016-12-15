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

int arrayColNumber(char cCol)
{
    return (cCol - '1');
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
    
    *ptr[0] = row;
    *ptr[1] = col;

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

#pragma mark Comparisons

int isPositionsEqual(Position *a, Position *b)
{
    return (a[0] == b[0] && a[1] == b[1]);
}

#pragma mark - Public Methods

void loadMenu()
{
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
            break;
            
        default:
            break;
    }
}

PositionArray *greedyCheapPath(Board board, Position *src, Position *dst)
{
    return NULL;
}
