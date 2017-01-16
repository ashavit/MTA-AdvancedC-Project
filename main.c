#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "Commons.h"
#include "Board.h"
#include "PositionArray.h"
#include "pathTree.h"

typedef struct _PositionListCell
{
    Position position;
    struct _PositionListCell *next;
} PositionListCell;

typedef struct _PositionList
{
    PositionListCell *head, *tail;
} PositionList;

void test();

#pragma mark - Main

int main()
{
    // insert code here...
    printf("Hello, World!\n");
    
    test();
    
    return 0;
}

#pragma mark - Public Methods

void testCheap(Board board)
{
    Position* src1, *src2;
    Position* dst1, *dst2;
    
    src1 = allocatePositionObject('A', '4');
    dst1 = allocatePositionObject('D', '1');
    PositionArray *posArray1 = greedyCheapPath(board, src1, dst1); /* Should return empty list */
    freePositionArray(posArray1);
    
    src2 = allocatePositionObject('A', '4');
    dst2 = allocatePositionObject('C', '3');
    PositionArray *posArray2 = greedyCheapPath(board, src2, dst2); /* Should return null */
    printPostionionsArray(posArray2);
    freePositionArray(posArray2);
}

void testPathTree(Board board)
{
    Position* src1;
    pathTree tree1;
    src1 = allocatePositionObject('A', '4');
    tree1 = findAllPossiblePaths(board, src1);
    printInOrder(tree1);
}

void test()
{
    Board board = { { 97, 104, 56, 105 },{ 103, 57, 50, 122 },{ 121, 97, 65, 98 },{ 53, 115, 50, 52 } };
    printBoard(board);
    
    testCheap(board);
    testPathTree(board);
}

