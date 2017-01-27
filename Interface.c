#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "Interface.h"
#include "Board.h"
#include "PositionArray.h"
#include "PathPrices.h"
#include "pathTree.h"

#define EXIT_CODE 7

static void performAction(int option, Board board, Position **src, Position **dst, BOOL *valSrc, BOOL *valDst);

void loadMenu()
{
    Board board;
    int option;
    char src[3], dst[3];
    Position *srcPos, *dstPos;
    BOOL validSrc = FALSE, validDst = FALSE;
    
    printf("1. Load a board from file\n");
    printf("2. Enter a source postition and destination\n");
    printf("3. Find a greedy cheap pah between the source and destination\n");
    printf("4. Create a tree of all possible paths starting from the source position\n");
    printf("5. Find all sorted path prices starting from source\n");
    printf("6. Find he cheapest path between source and destination\n");
    printf("7. Exit\n");
    
    do
    {
        printf("\nSelect option:\n");
        scanf("%d", &option);
        printf("\n");
        
        if (option == 2)
        {
            scanf("%s", src);
            scanf("%s", dst);
            srcPos = allocatePositionObject(src[0], src[1]);
            dstPos = allocatePositionObject(dst[0], dst[1]);
            validSrc = validatePosition(board, srcPos, "keep");
            validDst = validatePosition(board, dstPos, "keep");
            if (!validDst || !validSrc)
                printf("Invalid Positions");
        }
        performAction(option, board, &srcPos, &dstPos, &validSrc, &validDst);
    } while (option != EXIT_CODE);
    
}

static void performAction(int option, Board board, Position **src, Position **dst, BOOL *valSrc, BOOL *valDst)
{
    PositionArray *posArray1;
    PathTree tree;
    int *prices;
    char newSrc[3], newDst[3];
    int count = 0;
    PositionList *pathList = (PositionList*)malloc(sizeof(PositionList));
    if (!pathList)
    {
        printf("Could not allocate PositionArray object");
        exit(MALLOC_ERROR);
    }
    
    switch (option)
    {
        case 1:
        {
            char fileName[255] = { 0 };
            printf("Please enter name of binary file:\n");
            scanf("%s", fileName);
            loadBoardFromFile(fileName, board);
            printBoard(board);
            printf("Loaded file\n");
            break;
        }
        case 3:
            if (!(*valDst) || !(*valSrc))
            {
                printf("Please Enter Vaid Positions\n");
                scanf("%s", newSrc);
                scanf("%s", newDst);
                *src = allocatePositionObject(newSrc[0], newSrc[1]);
                *dst = allocatePositionObject(newDst[0], newDst[1]);
                *valDst = TRUE;
                *valSrc = TRUE;
                
            }
            posArray1 = greedyCheapPath(board, *src, *dst);
            if (posArray1->logical_size)
                printPostionionsArray(posArray1);
            else
                printf("Greedy Cheap Path not found\n");
            break;
        case 4:
            if (!(*valDst) || !(*valSrc))
            {
                printf("Please Enter Vaid Positions\n");
                scanf("%s", &newSrc);
                scanf("%s", &newDst);
                *src = allocatePositionObject(newSrc[0], newSrc[1]);
                *dst = allocatePositionObject(newDst[0], newDst[1]);
                *valDst = TRUE;
                *valSrc = TRUE;
                
            }
            tree = findAllPossiblePaths(board, *src);
//            printInOrder(tree);
            printf("Finished building tree");
            break;
        case 5:
            if (!(*valDst) || !(*valSrc))
            {
                printf("Please Enter Vaid Positions\n");
                scanf("%s", &newSrc);
                scanf("%s", &newDst);
                *src = allocatePositionObject(newSrc[0], newSrc[1]);
                *dst = allocatePositionObject(newDst[0], newDst[1]);
                *valDst = TRUE;
                *valSrc = TRUE;
                
            }
            tree = findAllPossiblePaths(board, *src);
            count = findAllPathsSortedPrices(board, &tree, *dst, &prices);
            printf("Price array size = %d:\n", count);
//            for (int i = 0; i < count; ++i)
//            {
//                printf("%d  ", prices[i]);
//            }
//            printf("\n\n");
            break;
        case 6:
            if (!(*valDst) || !(*valSrc))
            {
                printf("Please Enter Vaid Positions\n");
                scanf("%s", &newSrc);
                scanf("%s", &newDst);
                *src = allocatePositionObject(newSrc[0], newSrc[1]);
                *dst = allocatePositionObject(newDst[0], newDst[1]);
                *valDst = TRUE;
                *valSrc = TRUE;
            }
            pathList = allocatePositionList();
            tree = findAllPossiblePaths(board, *src);
            pathList = findTheCheapestPath(board, &tree, *dst);
            printList(pathList);
            break;
    }
    
}
