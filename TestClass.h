#ifndef __TEST_CLASS_H__
#define __TEST_CLASS_H__

#include <stdio.h>

#include "Commons.h"
#include "Board.h"
#include "PositionArray.h"
#include "PathTree.h"
#include "PathPrices.h"
#include "PositionList.h"

void runTests();

void run2x2Tests();
void run3x3Tests();
void run4x4Tests();
void runTestLoadBoards();
void runTestSaveBoards();

#endif /* TestClass_h */
