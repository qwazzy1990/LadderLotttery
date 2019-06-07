#ifndef _LL2_
#define _LL2_

#include "utilities.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



/*****SECTION FOR GENERATING THE MIN HEIGH ROOT LADDER***/
struct b{
    
    bool set;
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


/***DESTROYERS**/
void delete_ladder(void* l);

/***PRINTERS***/
char* print_bar(void* b);
char* print_ladder(void* l);

/***SETTERS***/
void add_to_ladder(Ladder l, Bar b, int rowIndex, int colIndex);
 
void setRowIndex(Bar b, int index);
void setColIndex(Bar b, int index);

/*GETTERS*/

int getColIndex(int c);

int getRowIndex(Ladder l, int colIndex);

int getLargestIndex(int* arr, int size);

/***Driver and run**/
void driver(Ladder l, int* permutation,  int size);

void run(int* perm, int size);

/****END SECTION***/


/****SECTION TO DO A RIGHT SWAP****/

/***Reconfigure the ladder to account for the right swap**/



/**Perform a right swap of bar b***/
void readjustLadder(Ladder l, Ladder ll, Bar b);

void rightSwap(Ladder l, Bar b, int rowToGo, int colIndex);


void getSwapIndex( Bar topBar, int vals[]);

/** Find the first turn bar in the root ladder**/
void getFirstTurnBarIndex(Ladder root, int* perm, int vals[]);


void setFirstTurnBar(Ladder l, int currElem, int rowIndex, int colIndex, int vals[]);

/**Fix the clean level Done after a right swap***/

void fixCleanLevel(Ladder l, int cleanLevel);

void resetCleanLevel(Ladder l, Bar b, int rowNum, int cleanLevel);

/***called at beginning of right swap to fix row and col of each bar**/
void resetAllRows(Ladder l);

/***Done after a right swap**/
void resetLadder(Ladder l);

void removeMultiple(Ladder l);

void removeMultipleTwo(Ladder l, Bar b, int row, int col);

void mainAlgorithm(Ladder root, int* perm);

bool sameBar(Bar b1, Bar b2);

bool emptyRow(Bar* row, int size);

bool canBeMovedUp(Ladder l, Bar b);

void removeEmptyRows(Ladder l);



/****TEST FUNCTIONS FOR NON-CANONICAL FORM****/


void generate_test_root(Ladder root, int* perm, int size);

void add_empty_row(Ladder l, int n);

/**Once the active bar is found, it is nececssary to find out where to right swap it to**/
void setSwapIndeciesOfActiveBar(Ladder l, int* activeRegion, int* indecies);

/***Function to set the start and end row of the active region, lower index will be set to ar[0], upper index will be set to ar[1]**/
void setActiveRegion(Ladder l, int cleanLevel, int min,  int maxVal, int* arr);
/**sets the indecies of the active bar in l given the level/cleanLevel**/
void setActiveBar(Ladder l, int level, int* index);

/**Checks if a bar, b, is downward visible from the path of the clean level in the ladder**/
bool isDownWardVisible(Ladder l, Bar b, int level);

/**Gets the clean level of the ladder l, given the original permutation**/
int getCleanLevel(int* perm, Ladder l);

/*Finds the maximum row of value v in ladder l*/
int findMaxRowOfVal(Ladder l, int val);

int findMinRowOfVal(Ladder l, int val);


#endif