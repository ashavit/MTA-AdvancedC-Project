
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "PositionList.h"

int isEmptyList(PositionList * lst)
{
	if (lst->head == NULL)
		return 1;
	else
		return 0;
}

//The funbction receive data and insert it to the end of lise
void insertDataToBeginingList(PositionList *lst, Position dataPtr)
{
	PositionListCell *newHead;
	newHead = createNewListNode(dataPtr, NULL);
	insertNodeToBeginingListNode(lst, newHead);
}
//The function receive node and enter it to the list
void insertNodeToBeginingListNode(PositionList *lst, PositionListCell *newHead)
{
	int num;
	num = isEmptyList(lst);
	if (num == 1)
	{
		lst->head = lst->tail = newHead;
	}
	else
	{
		newHead->next = lst->head;
		lst->head = newHead;
	}

}


//The function create a new List Node
PositionListCell * createNewListNode(Position position, PositionListCell *next)
{
	PositionListCell *res;
	res = (PositionListCell*)malloc(sizeof(PositionListCell));
	if (!res)
	{
		printf("Could not allocate PositionArray object");
		exit(MALLOC_ERROR);
	}
	res->position[0] = position[0];
	res->position[1] = position[1];
	res->next = next;
	return res;
}
//The function print the list
void printList(PositionList * lst)
{
	PositionListCell *curr;
	curr = lst->head;
	while (curr != NULL)
	{
		printf("%c%c ", curr->position[0], curr->position[1]);
		curr = curr->next;
	}
	printf("\n");
}
//The function receive list and empty it
void makeEmptyList(PositionList *lst)
{
	lst->head = lst->tail = NULL;

}
