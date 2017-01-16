#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "Commons.h"
#include "Board.h"
#include "PositionArray.h"
#include "pathTree.h"
#include "PathPrices.h"

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

void testFindSortedPrices(Board board, pathTree *tree, Position *dst)
{
    int *prices;
    int count = findAllPathsSortedPrices(board, tree, dst, &prices);
    
    printf("Price array size = %d:\n", count);
    for (int i = 0; i < count; ++i)
    {
        printf("%d  ", prices[i]);
    }
    printf("\n\n");
}

void testPathTree(Board board)
{
    Position* src1;
    pathTree tree1;
    src1 = allocatePositionObject('A', '4');
    Position* dst1 = allocatePositionObject('B', '4');
    tree1 = findAllPossiblePaths(board, src1);
//    printInOrder(tree1);
    
    testFindSortedPrices(board, &tree1, dst1);
}

void testSortedPathPricesPath2x2()
{
    Board board2x2 = { { 97, 104 },{ 103, 57 } };
    printBoard(board2x2);
    
    Position* src2x2 = allocatePositionObject('B', '2');
    Position *dst2x2 = allocatePositionObject('B', '1');
    pathTree tree2x2 = findAllPossiblePaths(board2x2, src2x2);

    testFindSortedPrices(board2x2, &tree2x2, dst2x2);
}

void testSortedPathPricesPath3x3()
{
    Board board3x3 = { { 97, 104, 56 },{ 103, 57, 50 },{ 121, 97, 65 }};
    printBoard(board3x3);
    
    Position* src3x3 = allocatePositionObject('A', '1');
    Position *dst3x3 = allocatePositionObject('C', '3');
    pathTree tree3x3 = findAllPossiblePaths(board3x3, src3x3);

    testFindSortedPrices(board3x3, &tree3x3, dst3x3);
}

void test()
{
    testSortedPathPricesPath2x2();
    testSortedPathPricesPath3x3();

    Board board = { { 97, 104, 56, 105 },{ 103, 57, 50, 122 },{ 121, 97, 65, 98 },{ 53, 115, 50, 52 } };
    printBoard(board);
    
    testCheap(board);
    testPathTree(board);
}

