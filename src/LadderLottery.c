

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "LadderLottery.h"
#include "utilities.h"
#include "Numbers.h"

int height = 0;
int barIndex = 0;

int currRow = 0;
int currCol = 0;

/**STATIC/HELPER FUNCTIONS*****/

// crates the bars for currLargest value
static void create_bars(int array[], int currLargest, int currIndex, int lastIndex, Bar **ladder)
{
    foreach (currIndex, lastIndex)
    {
        // if inversion found
        if (array[x] < currLargest)
        {
            // create a bar labelled with currLagrest and array[x]
            // column of bar is calculated as and offset from the current index = to the index of the inversion minus
            //the currrent index, index of current largest value
            Bar *b = new_bar(currLargest, array[x], x, height);
            char *s = print_bar(b);
            print(s);
            clear(s);
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
            // return index
            return x;
    }
    return -1;
}

static int get_largest(int arr[], int size)
{
    int largest = -1;
    forall(size)
    {
        if (arr[x] > largest)
        {
            largest = arr[x];
        }
    }

    return largest;
}

static int get_largest_index(int *arr, int size)
{
    int largest = -1;
    int index = -1;
    forall(size)
    {
        if (arr[x] > largest)
        {
            largest = arr[x];
            index = x;
        }
    }
    return index;
}

static void reset_row(int **table)
{
    while ((table[currRow][currCol + 1] != 1 && table[currRow][currCol - 1] != 1 && table[currRow][currCol] != 1) && (currRow != 0))
    {
        currRow--;
    }
    if (currRow != 0)
        currRow++;
}

static bool check_to_add(Table *t)
{
    if (t == NULL)
        return false;
    else if (t->table == NULL)
    {
        t->table = calloc(1, sizeof(Bar **));
        t->table[t->numRows] = calloc(t->numCols, sizeof(Bar *));
        forall(t->numCols)
        {
            t->table[t->numRows][x] = new_dummy_bar();
        }
        return true;
    }

    int maxCol = 0;
    int minCol = 0;

    if (currCol == t->numCols - 1)
    {
        maxCol = currCol;
    }
    else
    {
        maxCol = currCol + 1;
    }

    if (currCol == 0)
    {
        minCol = currCol;
    }
    else
    {
        minCol = currCol - 1;
    }

    if ((t->table[currRow][maxCol]->set == false) && (t->table[currRow][minCol]->set = false))
    {
        return true;
    }
    else
    {
        return false;
    }
}
/****************END STATIC/HELPER FUNCTIONS**************/

/*****CONSTRUCTOR********/
Bar *new_bar(int valOne, int valTwo, int column, int row)
{
    new_object(Bar *, b, 1);
    height++;
    b->height = row;
    b->column = column;
    b->values[0] = valOne;
    b->values[1] = valTwo;
    b->set = true;
    return b;
}

Bar *new_dummy_bar()
{
    new_object(Bar *, b, 1);
    b->set = false;
    return b;
}

Table *new_table(int numCols)
{
    new_object(Table *, t, 1);
    t->table = NULL;
    t->numRows = 0;
    t->numBars = 0;
    t->numCols = numCols;

    t->print = printTable;
    t->delete = deleteTable;
    t->compare = compareTables;
    t->add = add_to_table;
    return t;
}
/*******END CONSTRUCTORS*****/

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

char *printTable(void *table)
{
    Table *t = (Table *)table;
    char *s = calloc(100000, sizeof(char));
    char *temp = NULL;
    for (int i = 0; i < t->numRows; i++)
    {
        for (int j = 0; j < t->numCols; j++)
        {
            temp = print_bar(t->table[i][j]);
            strcat(s, temp);
        }
        strcat(s, "\n");
    }
    return s;
}
/***End Printers***/

/****DESTROYERS*******/
void deleteTable(void *t)
{
    delete_bars(t);
    Table *table = (Table *)t;
    forall(table->numRows)
    {
        clear(table->table[x]);
    }
    clear(table->table);
    clear(table);
    return;
}

int compareTables(const void *t1, const void *t2)
{
    return -1;
}
void delete_bars(void *t)
{
    Table *table = (Table *)t;
    for (int i = 0; i < table->numRows; i++)
    {
        for (int j = 0; j < table->numCols; j++)
        {
            free(table->table[i][j]);
        }
    }
}
/*******END DESTROYERS*********/

/**********SETTERS**********/
int res_row(Table *t, int col, int row)
{
    if (t->numBars == 0)
    {
        return 1;
    }
    int maxCol = 0;
    int minCol = 0;

    if (col >= t->numCols - 1)
    {
        maxCol = col;
    }
    else
    {
        maxCol = col + 1;
    }
    if (col <= 0)
    {
        minCol = 0;
    }
    else
    {
        minCol = col - 1;
    }

    int rowNum = 0;
    forall(t->numRows)
    {
        if((t->table[x][minCol]->set = true) || (t->table[x][maxCol]->set == true) || (t->table[x][col]->set==true))
        {
            rowNum++;
        }
        else{
            break;
        }
    }

    return rowNum+1;
}

void add_to_table(Table *t, Bar *b, int row, int col)
{
    
    int maxCols = t->numCols;

    if (t->numBars == 0)
    {
        t->table = calloc(1, sizeof(Bar **));
        t->table[t->numRows] = calloc(maxCols, sizeof(Bar *));

        forall(maxCols)
        {
            t->table[row][x] = new_dummy_bar();
        }
        free(t->table[row][col]);
        t->table[row][col] = b;
        t->numBars++;
        t->numRows++;
        return;
    }
    else
    {
        if (row >= t->numRows)
        {
            int memSize = row + 1;
            printf("%d\n", t->numRows);

            t->table = (Bar ***)realloc(t->table, memSize);
            t->table[row] = calloc(maxCols, sizeof(Bar *));
            forall(maxCols)
            {
                t->table[row][x] = new_dummy_bar();
            }
            //free(t->table[row][col]);
            t->table[row][col] = b;
            t->numBars++;
            t->numRows++;
            return;
        }
        else
        {
            free(t->table[row][col]);
            t->table[row][col] = b;
            t->numBars++;
            return;
        }
    }
}
/**********END SETTERS**********/

/****Main program to generate the optimal root ladder for a given permutation****/
/****array is the permutation. currLargest is the current largest value in the array***/
/*****size is the size of the array****/
void driver(int array[], int currLargest, int size, Bar **ladder)
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
    driver(arr, get_largest(arr, size - 1), (size - 1), ladder);

    // free the array
    free(arr);
}

// user enters a permutation to run the program
void create_root_ladder(void *permutation)
{
    Int perm = (Int)permutation;
    char *s = perm->print(perm);
    print(s);
    clear(s);

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

    new_object(Bar **, ladder, 1000);
    // driver
    driver(arr, get_largest(arr, size), size, ladder);

    // free memory
    forall(1000)
    {
        free(ladder[x]);
    }
    free(ladder);
}

void minHeightLadder(void *permutation, int size)
{
    int *temp = permutation;

    /*int **table = calloc(7, sizeof(int *));
    int numCols = size - 1;
    forall(7)
    {
        table[x] = calloc(numCols, sizeof(int));
        for (int i = 0; i < numCols; i++)
        {
            table[x][i] = 0;
        }
    }

    driver_two(table, (int *)permutation, size, get_largest_index(permutation, size));*/
    Table *table = new_table(size - 1);
    driver_three(table, (int *)permutation, size, get_largest_index((int *)permutation, size));
}

void driver_two(int **table, int *perm, int size, int largestIndex)
{
    if (size == 1)
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                printf("%d ", table[i][j]);
            }
            printf("\n");
        }
        return;
    }
    else
    {
        for (int i = largestIndex; i < size; i++)
        {
            if (perm[largestIndex] > perm[i])
            {
                currCol = i - 1;
                if (table[currRow][currCol + 1] == 0 && table[currRow][currCol - 1] == 0)
                {
                    reset_row(table);
                    table[currRow][currCol] = 1;
                }
                else
                {
                    currRow++;
                    table[currRow][currCol] = 1;
                }
            }
        }

        new_object(int *, arr, size - 1);
        remove_largest(arr, perm, perm[largestIndex], size);

        driver_two(table, arr, size - 1, get_largest_index(arr, size - 1));
        free(arr);
    }
}

// Driver for min height in two d-table representation of ladder containing the information about each bar
void driver_three(Table *t, int *perm, int size, int largestIndex)
{
    if (size == 1)
    {
        char *s = t->print(t);
        print(s);
        clear(s);
        return;
    }
    else
    {
        for (int i = largestIndex; i < size; i++)
        {
            if (perm[largestIndex] > perm[i])
            {
                currCol = i - 1;
                if (check_to_add(t))
                {

                    height = currRow;
                    Bar *b = new_bar(perm[largestIndex], perm[i], currCol, res_row(t, currCol, t->numRows));
                    t->add(t, b, currRow, currCol);
                }
                else
                {
                    currRow++;
                    height = currRow;
                    Bar *b = new_bar(perm[largestIndex], perm[i], currCol, res_row(t, currCol, t->numRows));

                    t->add(t, b, currRow, currCol);
                }
            }
        }

        new_object(int *, arr, size - 1);
        remove_largest(arr, perm, perm[largestIndex], size);
        char *s = t->print(t);
        print(s);
        clear(s);
        driver_three(t, arr, size - 1, get_largest_index(arr, size - 1));
        free(arr);
    }
}
