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


int isEmptyList(PositionList * lst);
void insertDataToBeginingList(PositionList *lst, Position dataPtr);
void insertNodeToBeginingListNode(PositionList *lst, PositionListCell *newHead);
PositionListCell * createNewListNode(Position position, PositionListCell *next);
void printList(PositionList * lst);
void makeEmptyList(PositionList *lst);

#endif
