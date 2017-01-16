#ifndef __POSITION_ARRAY_H__
#define __POSITION_ARRAY_H__

#include <stdio.h>
#include "Commons.h"
#include "Board.h"

typedef struct _PositionArray
{
    unsigned int logical_size, pysical_size;
    Position *positions;
} PositionArray;

PositionArray* allocatePositionArrayObject();
void freePositionArray(PositionArray *array);
void clearPositionArray(PositionArray *array);
void printPostionionsArray(PositionArray* posArr);

PositionArray *greedyCheapPath(Board board, Position *src, Position *dst);

#endif
