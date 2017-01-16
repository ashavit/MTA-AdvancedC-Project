#ifndef  __BOARD_H__
#define __BOARD_H__

#include <stdio.h>
#include "Commons.h"

#define BOARD_SIZE 4

#pragma mark - Data Model

typedef char Position[2];
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

Position* allocatePositionObject(char row, char col);
void freePositionObject(Position *pos);

int arrayRowNumber(char cRow);
int arrayColNumber(char cCol);
char arrayRowIndex(int row);
char arrayColIndex(int col);

void printBoard(Board board);

BOOL isPositionsEqual(Position *a, Position *b);
Position* findCheapestCellNeighbor(Board board, Position *src);

unsigned char getPriceOfCell(Board board, Position *pos);
void setPriceOfCell(Board board, Position *pos, unsigned char price);
BOOL validatePosition(Board board, Position *pos, char *str);

#endif
