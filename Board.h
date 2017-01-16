#ifndef  __BOARD_H__
#define __BOARD_H__

#include <stdio.h>

#define MALLOC_ERROR -1
#define BOARD_SIZE 4

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#pragma mark - Data Model

typedef char Position[2];
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef struct _PositionArray
{
    unsigned int logical_size, pysical_size;
    Position *positions;
} PositionArray;


Position* allocatePositionObject(char row, char col);
void freePositionObject(Position *pos);
PositionArray* allocatePositionArrayObject();
void freePositionArray(PositionArray *array);
void clearPositionArray(PositionArray *array);
void printPostionionsArray(PositionArray* posArr);

int arrayRowNumber(char cRow);
int arrayColNumber(char cCol);
char arrayRowIndex(int row);
char arrayColIndex(int col);

void printBoard(Board board);
PositionArray *greedyCheapPath(Board board, Position *src, Position *dst);

unsigned char getPriceOfCell(Board board, Position *pos);
void setPriceOfCell(Board board, Position *pos, unsigned char price);
BOOL validatePosition(Board board, Position *pos, char *str);

#endif
