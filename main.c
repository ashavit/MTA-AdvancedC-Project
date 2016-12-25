//
//  main.c
//  Advanced Programming - Project
//
//  Created by Amir Shavit on 28/11/2016.
//  Copyright © 2016 Amir Shavit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "Board.h"

typedef struct _PositionListCell
{
    Position position;
    struct _PositionListCell *next;
} PositionListCell;

typedef struct _PositionList
{
    PositionListCell *head, *tail;
} PositionList;

#pragma mark - Main

void loadMenu();

int main()
{
    // insert code here...
    printf("Hello, World!\n");
    
    loadMenu();
    
    return 0;
}

#pragma mark - Public Methods

void loadMenu()
{
    Board board = { { 97, 104, 56, 105 }, { 103, 57, 50, 122 }, { 121, 97, 65, 98 }, { 53, 115, 50, 52 } };
    printBoard(board);
    int option;
    
    printf("1. Load a board from file\n");
    printf("2. Enter a source postition and destination\n");
    printf("3. Find a greedy cheap pah between the source and destination\n");
    printf("4. Create a tree of all possible paths starting fmor the source position\n");
    printf("5. Find all sorted path prices starting frmo source\n");
    printf("6. Find he cheapest path between source and destination\n");
    printf("7. Exit\n");
    scanf("%d", &option);
    
    switch (option)
    {
        case 3:
        {
            Position* src;
            Position* dst;
            
//            greedyCheapPath(board, src, src);
            src = allocatePositionObject('A', '4');
            dst = allocatePositionObject('D', '1');
            PositionArray *posArray = greedyCheapPath(board, src, dst);
            
//            greedyCheapPath(board, src, dst);
            break;
        }
            
        default:
            break;
    }
}

