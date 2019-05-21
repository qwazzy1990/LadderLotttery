/*
    Ladder Lotteries are a way of sorting a random permutation based on the number of inverseions.
    Each line, or 0, represents the starting point of a path of an element in the given permutation.
    An element travels from the top of a line, 0, to the bottom of the ladder. Whenever the element comes across
    a bar, or n>0, the element must cross the bar. The number of bars is equal to the number of inversions
    in the original permutation. Each bar is crossed by exactly two unique elements in the inversion, thus making
    each bar distinct.

    Given a permutation, generate a ladder lottery in the form of 0130256070 for example, where 0 are lines and 
    n > 0 are bars such that the number represents the height of the bar.

    Let p = 52341
    Number of inverseions = 7.
    
*/


#ifndef LADDER_LOTTERY
#define LADDER_LOTTERY

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>




struct bar{
    int height;
    int column;
    int values[2];
    // Fix me later
    bool set;
};
typedef struct bar Bar;

Bar* new_bar(int valOne, int valTwo, int column);

char* print_bar(void* bar);


char* print_ladder(void* bars);


void driver(int array[], int currLargest, int size, Bar** bars);


/** the only function the user will need to call is the one below.
 **/

void create_root_ladder(void* permutation);

// Create ladder lotteries with minimum height in a 2-d array representation

void minHeightLadder(void* permutation, int size);

void driver_two(int** table, int* perm, int size, int largestIndex);


// Driver for min height in two d-table representation of ladder containing the information about each bar

void driver_three(Bar*** ladder, int* perm, int size, int largestIndex);
#endif