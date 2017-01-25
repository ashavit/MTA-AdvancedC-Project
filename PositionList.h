#ifndef  __POSITIONS_LIST__
#define __POSITIONS_LIST__

#include <stdio.h>
#include "Commons.h"
#include "Board.h"

typedef struct _positionListCell {
	Position position;
	struct _positionListCell *next;
} PositionListCell;

typedef struct _positionList {
	PositionListCell *head, *tail;
} PositionList;


PositionList* allocatePositionList();
void freePositionList(PositionList *list);

void insertDataToBeginingList(PositionList *lst, Position dataPtr);
void printList(PositionList * lst);

#endif
