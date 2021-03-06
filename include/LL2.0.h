#ifndef _LL2_
#define _LL2_

#include "utilities.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



/*****SECTION FOR GENERATING THE MIN HEIGH ROOT LADDER***/
struct b{
    
    bool set;
    bool beenSwapped;
    int vals[2];

    int rowIndex;
    int colIndex;

};
typedef struct b B;
typedef B* Bar;

struct l{

    int numRows;
    int numCols;
    int numBars;

    Bar** ladder;

    PrintFunc print;
    DeleteFunc del;
    void (*add)(struct l*, Bar, int, int);
};
typedef struct l L;
typedef L* Ladder;



/***Constructors***/
Bar new_bar(int valOne, int valTwo);
Bar dummy_bar(void);

Ladder new_ladder( int numCols);

Bar clone_bar(Bar b);

Ladder clone_ladder(Ladder l);
/***DESTROYERS**/
void delete_ladder(void* l);

/***PRINTERS***/
char* print_bar(void* b);
char* print_ladder(void* l);
char *printLadderTwo(void *l);
void printError(char* l);

void printLadder(char* l);

void printLadders(char l[1000][1000], int n);
void printLaddderNoColor(char* l);

/***SETTERS***/
void add_to_ladder(Ladder l, Bar b, int rowIndex, int colIndex);
 
void setRowIndex(Bar b, int index);
void setColIndex(Bar b, int index);

/*GETTERS*/

int getColIndex(int c);

int getRowIndex(Ladder l, int colIndex);

int getLargestIndex(int* arr, int size);

Bar getBar(Ladder l, int row, int col);

Bar getTopBar(Ladder l);

Bar getUpperBar(Ladder l, Bar b);

Bar getRightBar(Ladder l, Bar b);

/***Driver and run**/
void driver(Ladder l, int* permutation,  int size);

void run(int* perm, int size);

/****END SECTION***/


/****SECTION TO DO A RIGHT SWAP****/

/***Reconfigure the ladder to account for the right swap**/



/**Perform a right swap of bar b***/
void readjustLadder(Ladder l, Ladder ll, Bar b);

void rightSwap(Ladder l, Bar b, int rowToGo, int colIndex);

void leftSwap(Ladder l, Bar b, int rowToGo, int colToGo);



void getSwapIndex( Bar topBar, int vals[]);

/** Find the first turn bar in the root ladder**/
void getFirstTurnBarIndex(Ladder root, int* perm, int vals[]);


void setFirstTurnBar(Ladder l, int currElem, int rowIndex, int colIndex, int vals[]);

/**Fix the clean level Done after a right swap***/

void fixCleanLevel(Ladder l, int cleanLevel);

void resetCleanLevel(Ladder l, Bar b, int rowNum, int cleanLevel);

/***called at beginning of right swap to fix row and col of each bar**/
void resetAllRows(Ladder l);

void findRowAndCol(Ladder l, Bar b, int* arr);

void removeRow(Ladder l, int row);



bool sameBar(Bar b1, Bar b2);

Bar findBar(Ladder l, Bar b);

bool emptyRow(Bar* row, int size);
int getEmptyRow(Ladder l);

bool emptyBar(Bar b);


bool canBeMovedUp(Ladder l, Bar b);




/****TEST FUNCTIONS FOR NON-CANONICAL FORM****/


void generate_test_root(Ladder root, int* perm, int size);

void add_empty_row(Ladder l, int n);

/**Once the active bar is found, it is nececssary to find out where to right swap it to**/
void setSwapIndeciesOfActiveBar(Ladder l, Bar b,  int* activeRegion, int* indecies);

/***Function to set the start and end row of the active region, lower index will be set to ar[0], upper index will be set to ar[1]**/
void setActiveRegion(Ladder l, Bar activeBar, int cleanLevel, int min,  int maxVal, int* arr);

void setUpperRegion(Ladder l, Bar activeBar, int level, int* arr);
/**sets the indecies of the active bar in l given the level/cleanLevel**/
void setActiveBar(Ladder l, int level, int* index);

void setActiveBars(Ladder l, int level, Bar* bars, int* numBars);

/**Checks if a bar, b, is downward visible from the path of the clean level in the ladder**/
bool isDownWardVisible(Ladder l, Bar b, int level);

/**Gets the clean level of the ladder l, given the original permutation**/
int getCleanLevel(int* perm, Ladder l);

/*Finds the maximum row of value v in ladder l*/
int findMaxRowOfVal(Ladder l, int val);

int findMinRowOfVal(Ladder l, int val);



/****Algorithm from Paper***/

void findAllChildren(Ladder l, int* perm, Bar currBar, int currRow, int currCol, int k, int size, int Level);

void runProg( int* perm, int size);

bool doubleLadder(char* l, char ladders[1000][1000], int count);


void addToLadders(char ladders[1000][1000], char* l, int count);


#endif