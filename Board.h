//
//  Board.h
//  Advanced Programming - Project
//
//  Created by Amir Shavit on 25/12/2016.
//  Copyright © 2016 Amir Shavit. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <stdio.h>

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


Position* allocatePositionObject(char row, char col);
void freePositionObject(Position *pos);
PositionArray* allocatePositionArrayObject();
void freePositionArray(PositionArray *array);
void clearPositionArray(PositionArray *array);
void printPostionionsArray(PositionArray* posArr);

void printBoard(Board board);
PositionArray *greedyCheapPath(Board board, Position *src, Position *dst);


unsigned char getPriceOfCell(Board board, Position *pos);
void setPriceOfCell(Board board, Position *pos, unsigned char price);


#endif /* Board_h */
