
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "PositionList.h"

static BOOL isEmptyList(PositionList * lst);
static void insertNodeToBeginingListNode(PositionList *lst, PositionListCell *newHead);
static PositionListCell* createNewListNode(Position position);

PositionList* allocatePositionList()
{
    PositionList *list = (PositionList*)malloc(sizeof(PositionList));
    if (!list)
    {
        printf("Could not allocate PositionList\n");
        exit(MALLOC_ERROR);
    }
    
    list->head = list->tail = NULL;
    return list;
}

void freePositionList(PositionList *lst)
{
    if (!lst)
        return;
    
    PositionListCell *curr = lst->head;
    PositionListCell *next = NULL;
    while (curr)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(lst);
}

void printList(PositionList *lst)
{
    PositionListCell *curr = lst->head;
    while (curr)
    {
        printf("%c%c ", curr->position[0], curr->position[1]);
        curr = curr->next;
    }
    printf("\n");
}

//The function receive position data and inserts it to the begining of list
void insertDataToBeginingList(PositionList *lst, Position pos)
{
    PositionListCell *newHead = createNewListNode(pos);
    insertNodeToBeginingListNode(lst, newHead);
}

static BOOL isEmptyList(PositionList * lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

//The function receive node and enter it to the list
static void insertNodeToBeginingListNode(PositionList *lst, PositionListCell *newHead)
{
	if (isEmptyList(lst))
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
static PositionListCell* createNewListNode(Position position)
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
	res->next = NULL;
	return res;
}

