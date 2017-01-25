#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "TestClass.h"

static void testCheap(Board board);
static void testPathTree(Board board);
static void testFindSortedPrices(Board board, pathTree *tree, Position *dst);
static void testSortedPathPricesPath2x2();
static void testSortedPathPricesPath3x3();
static void testFindTheCheapestPathEndNode2x2();
static void testFindTheCheapestPathEndNode3x3();
static void testFindTheCheapestPathList2x2();
static void testFindTheCheapestPathList3x3();


void runTests()
{
//    run2x2Tests();
    run3x3Tests();
//    run4x4Tests();
}

void run2x2Tests()
{
    testSortedPathPricesPath2x2();
    testFindTheCheapestPathEndNode2x2();
    testFindTheCheapestPathList2x2();
}

void run3x3Tests()
{
    testSortedPathPricesPath3x3();
    testFindTheCheapestPathEndNode3x3();
    testFindTheCheapestPathList3x3();
}

void run4x4Tests()
{
    Board board = { { 97, 104, 56, 105 },{ 103, 57, 50, 122 },{ 121, 97, 65, 98 },{ 53, 115, 50, 52 } };
    printBoard(board);
    
    testCheap(board);
    testPathTree(board);
}

static void testCheap(Board board)
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

static void testPathTree(Board board)
{
    Position* src1;
    pathTree tree1;
    src1 = allocatePositionObject('A', '4');
    Position* dst1 = allocatePositionObject('B', '4');
    tree1 = findAllPossiblePaths(board, src1);
    //    printInOrder(tree1);
    
    testFindSortedPrices(board, &tree1, dst1);
}

static void testFindSortedPrices(Board board, pathTree *tree, Position *dst)
{
    int *prices;
    int count = findAllPathsSortedPrices(board, tree, dst, &prices);
    
    printf("Price array size = %d:\n", count);
    for (int i = 0; i < count; ++i)
    {
        printf("%d  ", prices[i]);
    }
    printf("\n\n");
    free(prices);
}


static void testSortedPathPricesPath2x2()
{
    Board board2x2 = { { 97, 104 },{ 103, 57 } };
    printBoard(board2x2);
    
    Position *src2x2 = allocatePositionObject('B', '2');
    Position *dst2x2 = allocatePositionObject('B', '1');
    pathTree tree2x2 = findAllPossiblePaths(board2x2, src2x2);
    
    testFindSortedPrices(board2x2, &tree2x2, dst2x2);
}

static void testSortedPathPricesPath3x3()
{
    Board board3x3 = { { 97, 104, 56 },{ 103, 57, 50 },{ 121, 97, 65 }};
    //    Board board3x3 = { { 1,2, 3 },{ 4, 5,6 },{ 7, 8, 9 } };
    printBoard(board3x3);
    
    Position *src3x3 = allocatePositionObject('A', '1');
    Position *dst3x3 = allocatePositionObject('C', '3');
    pathTree tree3x3 = findAllPossiblePaths(board3x3, src3x3);
    
    testFindSortedPrices(board3x3, &tree3x3, dst3x3);
}


static void testFindTheCheapestPathEndNode2x2()
{
    Board board2x2 = { { 97, 104 },{ 103, 57 } };
    printBoard(board2x2);
    Position *src2x2 = allocatePositionObject('B', '2');
    Position *dst2x2 = allocatePositionObject('B', '1');
    pathTree tree2x2 = findAllPossiblePaths(board2x2, src2x2);
    treeNode *cheapestNode;
    //printInOrder(currTree);
    cheapestNode = findTheCheapestPathEndNode(board2x2, tree2x2.root, dst2x2);
    printf("cheapestNode: %p for dst: %c%c\n", cheapestNode, cheapestNode->position[0], cheapestNode->position[1]);
}

static void testFindTheCheapestPathEndNode3x3()
{
    Board board3x3 = { { 1,2, 3 },{ 4, 5,6 },{ 7, 8, 9 } };
    printBoard(board3x3);
    pathTree currTree;
    treeNode *cheapestNode;
    Position *src3x3 = allocatePositionObject('A', '1');
    Position *dst3x3 = allocatePositionObject('C', '3');
    currTree = findAllPossiblePaths(board3x3, src3x3);
    //printInOrder(currTree);
    cheapestNode = findTheCheapestPathEndNode(board3x3, currTree.root, dst3x3);
    printf("cheapestNode: %p for dst: %c%c\n", cheapestNode, cheapestNode->position[0], cheapestNode->position[1]);
}


static void testFindTheCheapestPathList2x2()
{
    Board board2x2 = { { 97, 104 },{ 103, 57 } };
    printBoard(board2x2);
    Position *src2x2 = allocatePositionObject('B', '2');
    Position *dst2x2 = allocatePositionObject('B', '1');
    pathTree tree2x2 = findAllPossiblePaths(board2x2, src2x2);
    PositionList *pathList = findTheCheapestPath(board2x2, &tree2x2, dst2x2);
    printList(pathList);
    freePositionList(pathList);
}

static void testFindTheCheapestPathList3x3()
{
    Board board3x3 = { { 97, 122, 56 },{ 103, 57, 50 },{ 121, 97, 65 }};
    //    Board board3x3 = { { 1,2, 3 },{ 4, 5,6 },{ 7, 8, 9 } };
    printBoard(board3x3);
    Position *src3x3 = allocatePositionObject('A', '1');
    Position *dst3x3 = allocatePositionObject('C', '3');
    pathTree tree3x3 = findAllPossiblePaths(board3x3, src3x3);
    PositionList *pathList = findTheCheapestPath(board3x3, &tree3x3, dst3x3);
    printList(pathList);
    freePositionList(pathList);
}
