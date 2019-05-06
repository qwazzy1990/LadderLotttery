

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "LadderLottery.h"
#include "utilities.h"
#include "Numbers.h"

int height = 0;
int barIndex = 0;

/**STATIC/HELPER FUNCTIONS*****/

// crates the bars for currLargest value
static void create_bars(int array[], int currLargest, int currIndex, int lastIndex, Bar** ladder)
{
    foreach (currIndex, lastIndex)
    {
        // if inversion found
        if (array[x] < currLargest)
        {
            // create a bar labelled with currLagrest and array[x]
            // column of bar is calculated as and offset from the current index = to the index of the inversion minus
            //the currrent index/ index of current largest value
            Bar *b = new_bar(currLargest, array[x], ((x - currIndex) + currIndex));
            ladder[barIndex] = b;
            barIndex++;
        }
    }
}

// remove the largest value from the current array/read by copying every other value to other array/write
static void remove_largest(int *write, int read[], int val, int size)
{
    int count = 0;
    forall(size)
    {
        if (read[x] != val)
        {
            write[count] = read[x];
            count++;
        }
    }
}

// get index of value
static int get_index(int array[], int value, int size)
{
    forall(size)
    {
        if (array[x] == value)
            return x;
    }
    return -1;
}

static int get_largest(int arr[], int size)
{
    int largest = -1;
    forall(size)
    {
        if(arr[x] > largest)
        {
            largest = arr[x];
        }
    }

    return largest;
}
/****************END STATIC/HELPER FUNCTIONS**************/

/*****CONSTRUCTOR********/
Bar *new_bar(int valOne, int valTwo, int column)
{
    new_object(Bar *, b, 1);
    height++;
    b->height = height;
    b->column = column;
    b->values[0] = valOne;
    b->values[1] = valTwo;
    return b;
}

/******PRINTER*******/
char *print_bar(void *bar)
{
    if (bar == NULL)
        return NULL;

    Bar *temp = (Bar *)bar;

    new_object(char *, s, 1000);
    char t[100];
    strcpy(s, "(");
    sprintf(t, "%d", temp->height);
    strcat(s, t);
    strcat(s, ":");
    sprintf(t, "%d", temp->values[0]);
    strcat(s, t);
    strcat(s, ",");
    sprintf(t, "%d", temp->values[1]);
    strcat(s, t);
    strcat(s, ":");
    sprintf(t, "%d", temp->column);
    strcat(s, t);
    strcat(s, ")");
    return s;
}




/****Main program to generate the optimal root ladder for a given permutation****/
/****array is the permutation. currLargest is the current largest value in the array***/
/*****size is the size of the array****/
void driver(int array[], int currLargest, int size, Bar** ladder)
{
    /** if there is only one elment in the array  then return**/
    if (size == 1)
        return;

    // find the bars for the current largest
    create_bars(array, currLargest, get_index(array, currLargest, size), size, ladder);

    // remove the current largest from the array and add remainder of array to arr
    // remove_largest also shifts the right values of removed value to the left by 1
    new_object(int *, arr, size - 1);
    remove_largest(arr, array, currLargest, size);

    // reduce the size of the array by 1
    // get the largest value in the new array and its index
    // recursive call
    driver(arr, get_largest(arr, size-1), (size-1), ladder);

    // free the array
    free(arr);

}




// user enters a permutation to run the program
void create_root_ladder(void* permutation)
{
    Int perm = (Int)permutation;
    
    // get number of elements in permutation
    int size = perm->size;
   
    // copy over the elements 
    int arr[size];
    forall(size)
    {
        arr[x] = perm->ints[x];
    }
    
    // free memory
    perm->destroy(perm);

    new_object(Bar**, ladder, 1000);
    // driver
    driver(arr, get_largest(arr, size), size, ladder);

    // free memory
    forall(1000)
    {
        free(ladder[x]);
    }
    free(ladder);
}
