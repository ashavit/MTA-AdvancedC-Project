#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Board.h"

#define READ_FILE_ERROR 2
#define WRITE_FILE_ERROR 3

#pragma mark - Private Declarations

/* Return cheaper cell if exist, or null if doesn't exist or if price is 0 */
static Position* cheaperCellPosition(Board board, Position *a, Position *b);

static FILE* openFile(const char* fileName, char *rights);
static void closeFile(FILE *filePtr);
static unsigned char* allocateZeroCharArray(int size);
static unsigned char createMask(int msb, int lsb);
static unsigned int binReadChar(unsigned char* chars, unsigned int size, FILE *filePtr);
static unsigned int binWriteChar(unsigned char* chars, unsigned int size, FILE *filePtr);

#pragma mark - Public Methods

Position* allocatePositionObject(char row, char col)
{
    Position *ptr = (Position*)malloc(sizeof(Position));
    if (!ptr)
    {
        printf("Could not allocate Position object");
        exit(MALLOC_ERROR);
    }
    
    (*ptr)[0] = row;
    (*ptr)[1] = col;
    
    return ptr;
}

void freePositionObject(Position *pos)
{
    free(pos);
}

/* Read data bin file in chunks of 7 bytes = 4 cell * 14 bits each */
void loadBoardFromFile(const char *fileName, Board board)
{
    FILE *filePtr = openFile(fileName, "rb");
    
    int cellCount = BOARD_SIZE * BOARD_SIZE;
    int positionsLoaded = 0;
    int readItteration = 0;
    
    while (positionsLoaded < cellCount)
    {
        // Positions to read in this itteration
        readItteration = (cellCount - positionsLoaded > 4 ? 4 : cellCount - positionsLoaded);

        unsigned char *data = allocateZeroCharArray(7);
        int readBytes = ceil(readItteration * 14.0 / 8);
        binReadChar(data, readBytes, filePtr);
        
        for (int t = 0; t < 7; ++t)
        {
            printf("%d, ", data[t]);
        }
        printf("\n");
        
        for (int i = 0; i < readItteration; ++i)
        {
            char row = 0, col = 0;
            unsigned char value = 0;
            
            int rowBitIndex, rowByte, rowFirstBit, rowLastBit;
            rowBitIndex = 14 * i;
            rowByte = rowBitIndex / 8;
            rowFirstBit = rowBitIndex % 8;
            rowLastBit = rowFirstBit + 2;
            
            if (rowLastBit < 8)
            {
                row |= ((data[rowByte] & createMask(rowLastBit, rowFirstBit)) >> rowFirstBit);
            }
            else
            {
                row |= ((data[rowByte] & createMask(7, rowFirstBit)) >> rowFirstBit);
                row |= ((data[rowByte+1] & createMask(rowLastBit - 8, 0)) << (8 - rowFirstBit));
            }
            
            int colBitIndex, colByte, colFirstBit, colLastBit;
            colBitIndex = (14 * i) + 3;
            colByte = colBitIndex / 8;
            colFirstBit = colBitIndex % 8;
            colLastBit = colFirstBit + 2;
            
            if (colLastBit < 8)
            {
                col |= ((data[colByte] & createMask(colLastBit, colFirstBit)) >> colFirstBit);
            }
            else
            {
                col |= ((data[colByte] & createMask(7, colFirstBit)) >> colFirstBit);
                col |= ((data[colByte+1] & createMask(colLastBit - 8, 0)) << (8 - colFirstBit));
            }
            
            int valBitIndex, valByte, valFirstBit, valLastBit;
            valBitIndex = (14 * i) + 6;
            valByte = valBitIndex / 8;
            valFirstBit = valBitIndex % 8;
            valLastBit = valFirstBit + 7;
            
            if (valLastBit < 8)
            {
                value = data[valByte];
            }
            else
            {
                value |= ((data[valByte] & createMask(7, valFirstBit)) >> valFirstBit);
                value |= ((data[valByte+1] & createMask(valLastBit - 8, 0)) << (8 - valFirstBit));
            }
            
            board[row][col] = value;
            ++positionsLoaded;
            printf("Loaded value %d to %d,%d\n", value, row, col);
        }
        free(data);
    }

    closeFile(filePtr);
}

void saveBoardToFile(const char *fileName, Board board)
{
    FILE *filePtr = openFile(fileName, "wb");
    
    int cellCount = BOARD_SIZE * BOARD_SIZE;
    int maxBytes = ((cellCount * 14 % 8) ? (cellCount * 14 / 8 + 1) : (cellCount * 14 / 8));
    unsigned char *data = allocateZeroCharArray(maxBytes);

    int i = 0;
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            int rowBitIndex, rowByte, rowFirstBit, rowLastBit;
            rowBitIndex = 14 * i;
            rowByte = rowBitIndex / 8;
            rowFirstBit = rowBitIndex % 8;
            rowLastBit = rowFirstBit + 2;
            
            if (rowLastBit < 8)
            {
                data[rowByte] |= ((row & createMask(2, 0)) << rowFirstBit);
            }
            else
            {
                data[rowByte]   |= ((row & createMask(7 - rowFirstBit, 0)) << rowFirstBit);
                data[rowByte+1] |= ((row & createMask(2, 8 - rowFirstBit)) >> (8 - rowFirstBit));
            }
            
            int colBitIndex, colByte, colFirstBit, colLastBit;
            colBitIndex = (14 * i) + 3;
            colByte = colBitIndex / 8;
            colFirstBit = colBitIndex % 8;
            colLastBit = colFirstBit + 2;
            
            if (colLastBit < 8)
            {
                data[colByte] |= ((col & createMask(2, 0)) << colFirstBit);
            }
            else
            {
                data[colByte]   |= ((col & createMask(7 - colFirstBit, 0)) << colFirstBit);
                data[colByte+1] |= ((col & createMask(2, 8 - colFirstBit)) >> (8 - colFirstBit));
            }
            
            int valBitIndex, valByte, valFirstBit, valLastBit;
            valBitIndex = (14 * i) + 6;
            valByte = valBitIndex / 8;
            valFirstBit = valBitIndex % 8;
            valLastBit = valFirstBit + 7;
            unsigned char value = board[row][col];
            
            if (valLastBit < 8)
            {
                data[valByte] = value;
            }
            else
            {
                data[valByte]   |= ((value & createMask(7 - valFirstBit, 0)) << valFirstBit);
                data[valByte+1] |= ((value & createMask(7, 8 - valFirstBit)) >> (8 - valFirstBit));
            }
            
            ++i;
        }
    }
    
    for (int t = 0; t < maxBytes; ++t)
    {
        printf("%d, ", data[t]);
    }
    printf("\n");
    
    binWriteChar(data, maxBytes, filePtr);
    closeFile(filePtr);
    free(data);
}

void printBoard(Board board)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            printf("%4d", board[row][col]);
        }
        printf("\n");
    }
}

unsigned char getPriceOfCell(Board board, Position *pos)
{
    int row = arrayRowNumber((*pos)[0]);
    int col = arrayColNumber((*pos)[1]);
    return (board[row][col]);
}

void setPriceOfCell(Board board, Position *pos, unsigned char price)
{
    int row = arrayRowNumber((*pos)[0]);
    int col = arrayColNumber((*pos)[1]);
    board[row][col] = price;
}

//The function return true if position is legal and if the position price is not 0
BOOL validatePosition(Board board, Position *pos, char *str)
{
    Position *next;
    int curRow = arrayRowNumber((*pos)[0]);
    int curCol = arrayColNumber((*pos)[1]);
    
    int nextRow = curRow;
    int nextCol = curCol;
    
    if (strcmp(str, "left") == 0)
        nextCol--;
    else if (strcmp(str, "right") == 0)
        nextCol++;
    else if (strcmp(str, "up") == 0)
        nextRow--;
    else if (strcmp(str, "down") == 0)
        nextRow++;
    
    BOOL res = FALSE;
    if (nextRow >= 0 && nextRow < BOARD_SIZE && nextCol >= 0 && nextCol < BOARD_SIZE)
    {
        
        next = allocatePositionObject(arrayRowIndex(nextRow), arrayColIndex(nextCol));
        if (getPriceOfCell(board, next) != '0')
            res = TRUE;
        else
            res = FALSE;
        
        freePositionObject(next);
    }
    return res;
}

#pragma mark - Conversion

int arrayRowNumber(char cRow)
{
    return (cRow - 'A');
}

char arrayRowIndex(int row)
{
    return (row + 'A');
}

int arrayColNumber(char cCol)
{
    return (cCol - '1');
}

char arrayColIndex(int col)
{
    return (col + '1');
}

#pragma mark Comparisons

BOOL isPositionsEqual(Position *a, Position *b)
{
    return ((*a)[0] == (*b)[0] && (*a)[1] == (*b)[1]);
}

Position* findCheapestCellNeighbor(Board board, Position *src)
{
    Position *cheapest = NULL;
    Position *curr = NULL;
    
    int curRow = arrayRowNumber((*src)[0]);
    int curCol = arrayColNumber((*src)[1]);
    
    // Check if up is possible
    if (curRow - 1 >= 0)
    {
        // Check if top neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow - 1), arrayColIndex(curCol));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    // Check if down is possible
    if (curRow + 1 < BOARD_SIZE)
    {
        // Check if bottom neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow + 1), arrayColIndex(curCol));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    // Check if left is possible
    if (curCol - 1 >= 0)
    {
        // Check if left neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow), arrayColIndex(curCol - 1));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    // Check if right is possible
    if (curCol + 1 < BOARD_SIZE)
    {
        // Check if right neibor has valid price
        curr = allocatePositionObject(arrayRowIndex(curRow), arrayColIndex(curCol + 1));
        cheapest = cheaperCellPosition(board, cheapest, curr);
    }
    
    return cheapest;
}

#pragma mark - Private

/* Return cheaper cell if exist, or null if doesn't exist or if price is 0 */
static Position* cheaperCellPosition(Board board, Position *a, Position *b)
{
    if (!a && !b)
        return NULL;
    
    unsigned char priceA = 0;
    unsigned char priceB = 0;
    
    if (!a)
    {
        // Make sure b has valid price
        priceB = getPriceOfCell(board, b);
        return (priceB ? b : NULL);
    }
    
    if (!b)
    {
        // Make sure a has valid price
        priceA = getPriceOfCell(board, a);
        return (priceA ? a : NULL);
    }
    
    priceA = getPriceOfCell(board, a);
    priceB = getPriceOfCell(board, b);
    
    // Compare price and validity
    if (priceA && priceB) /* Compare 2 valid prices */
        return (priceA < priceB ? a : b);
    else if (priceA) /* Only a has valid price */
        return a;
    else if (priceB) /* Only b has valid price */
        return b;
    else /* Neither have valid price */
        return NULL;
}

#pragma mark - Files and Masks

static FILE* openFile(const char* fileName, char *rights)
{
    FILE *filePtr = fopen(fileName, rights);
    if (!filePtr)
    {
        printf("Error opening file %s for %s\n", fileName, rights);
        exit(READ_FILE_ERROR);
    }
    return filePtr;
}

static void closeFile(FILE *filePtr)
{
    fclose(filePtr);
}

static unsigned char* allocateZeroCharArray(int size)
{
    unsigned char *result = (unsigned char*)malloc(sizeof(unsigned char) * size);
    if (!result)
    {
        printf("Could not allocate char array object");
        exit(MALLOC_ERROR);
    }
    
    for (int i = 0; i < size; ++i)
        result[i] = 0;
    
    printf("Allocated zero array with %d chars\n", size);
    return result;
}

static unsigned char createMask(int msb, int lsb)
{
    unsigned char mask = (  (1 << (msb + 1)) - (1 << lsb) );
    return mask;
}

static unsigned int binReadChar(unsigned char* chars, unsigned int maxSize, FILE *filePtr)
{
    unsigned long read = fread(chars, sizeof(char), maxSize, filePtr);
    if (!read)
    {
        printf("Error reading string file\n");
        exit(READ_FILE_ERROR);
    }
    return (unsigned int)read;
}

static unsigned int binWriteChar(unsigned char* chars, unsigned int size, FILE *filePtr)
{
    unsigned long written = fwrite(chars, sizeof(char), size, filePtr);
    if (written != size)
    {
        printf("Error writing chars to file (written %ld)\n", written);
        exit(WRITE_FILE_ERROR);
    }
    return size;
}

