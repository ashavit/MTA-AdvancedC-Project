#include "Interface.h"
#include "Board.h"

#define EXIT_CODE 7

static void performAction(int option, Board board);

void loadMenu()
{
    Board board = { { 97, 104, 56, 105 },{ 103, 57, 50, 122 },{ 121, 97, 65, 98 },{ 53, 115, 50, 52 } };
    int option;
    
    printf("1. Load a board from file\n");
    printf("2. Enter a source postition and destination\n");
    printf("3. Find a greedy cheap pah between the source and destination\n");
    printf("4. Create a tree of all possible paths starting from the source position\n");
    printf("5. Find all sorted path prices starting from source\n");
    printf("6. Find he cheapest path between source and destination\n");
    printf("7. Exit\n");
    printf("Select option:\n");
    
    do
    {
        scanf("%d", &option);
        performAction(option, board);
    }
    while (option != EXIT_CODE);
}

static void performAction(int option, Board board)
{
    switch (option)
    {
        case 3:
        {
//            Position* src1, *src2;
//            Position* dst1, *dst2;
//            
//            src1 = allocatePositionObject('A', '4');
//            dst1 = allocatePositionObject('D', '1');
//            PositionArray *posArray1 = greedyCheapPath(board, src1, dst1); /* Should return empty list */
//            freePositionArray(posArray1);
//            
//            src2 = allocatePositionObject('A', '4');
//            dst2 = allocatePositionObject('C', '3');
//            PositionArray *posArray2 = greedyCheapPath(board, src2, dst2); /* Should return null */
//            printPostionionsArray(posArray2);
//            freePositionArray(posArray2);
            break;
        }
        case 4:
        {
//            Position* src1;
//            pathTree tree1;
//            src1 = allocatePositionObject('A', '4');
//            tree1 = findAllPossiblePaths(board, src1);
//            printInOrder(tree1);
        }
            
        default:
            break;
    }
}

