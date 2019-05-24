#include "utilities.h"
#include "DynamicString.h"
#include "StringArray.h"
#include "Numbers.h"
#include "LL2.0.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



/***STATIC FUNCTIONS***/

static void copyArray(int** write, int * read, int largestIndex, int size)
{
    int* temp = *write;
    int i = 0;
    forall(size)
    {
        if(x != largestIndex)
        {
            temp[i] = read[x];
            i++;
        }
    }
}

/***END**/


/****SECTION FOR GENERATING THE MIN HEIGHT ROOT LADDER***/
Bar new_bar(int valOne, int valTwo)
{
    new_object(Bar, b, 1);
    b->vals[0] = valOne;
    b->vals[1] = valTwo;

    b->set = true;
    return b;
}

Bar dummy_bar(void)
{
    new_object(Bar, b, 1);
    b->rowIndex = -1;
    b->colIndex = -1;
    b->set = false;
    return b;
}

Ladder new_ladder(int numCols)
{
    new_object(Ladder, l, 1);

    l->numBars = 0;
    l->numRows = 0;

    l->numCols = numCols;

    l->print = print_ladder;
    l->del = delete_ladder;
    l->add = add_to_ladder;

    return l;
}

char *print_bar(void *b)
{
    Bar bb = (Bar)b;

    char *s = calloc(10, sizeof(char));
    char temp[10];
    strcpy(s, "(");
    sprintf(temp, "%d", bb->vals[0]);
    strcat(s, temp);
    strcat(s, ",");
    sprintf(temp, "%d", bb->vals[1]);
    strcat(s, temp);
    strcat(s, ")");
    strcat(s, " ");
    return s;
}
char *print_ladder(void *l)
{
    char *s = calloc(10, sizeof(char));
    char *temp = NULL;
    char stat[100];

    int memSize = 40;

    Ladder ll = (Ladder)l;
    forall(ll->numCols)
    {
        memSize+=10;
        sprintf(stat, "%d", x+1);
        s = realloc(s, memSize*sizeof(char));
        strcat(s, "  ");
        strcat(s, stat);
        strcat(s, "   ");
    }
    strcat(s, "\n");
    

    

    for (int i = 0; i < ll->numRows; i++)
    {
        for (int j = 0; j < ll->numCols; j++)
        {
            temp = print_bar(ll->ladder[i][j]);
            memSize += strlen(temp) + 5;
            s = realloc(s, memSize * sizeof(char));
            strcat(s, temp);
            free(temp);
        }
        strcat(s, "\n");
    }

    return s;
}

void delete_ladder(void *l)
{
    Ladder ll = (Ladder)l;

    for (int i = 0; i < ll->numRows; i++)
    {
        for (int j = 0; j < ll->numCols; j++)
        {
            free(ll->ladder[i][j]);
        }
        free(ll->ladder[i]);
    }
    free(ll->ladder);
    free(ll);
}

void add_to_ladder(Ladder l, Bar b, int rowIndex, int colIndex)
{
    /*If adding the first bar to the ladder*/
    if (l->numBars == 0)
    {
        new_object(Bar **, ladder, 1);
        l->ladder = ladder;
        l->ladder[0] = calloc(l->numCols, sizeof(Bar));
        forall(l->numCols)
        {
            l->ladder[0][x] = dummy_bar();
        }
        free(l->ladder[rowIndex][colIndex]);
        l->ladder[rowIndex][colIndex] = b;

        l->numBars++;
        l->numRows++;
        return;
    }

    /*If a new row needs to be added to the ladder*/
    if (rowIndex >= l->numRows)
    {
        int memSize = rowIndex + 1;
        l->ladder = realloc(l->ladder, memSize * sizeof(Bar **));
        l->ladder[rowIndex] = calloc(l->numCols, sizeof(Bar));
        forall(l->numCols)
        {
            l->ladder[rowIndex][x] = dummy_bar();
        }
        free(l->ladder[rowIndex][colIndex]);
        l->ladder[rowIndex][colIndex] = b;

        l->numBars++;
        l->numRows++;
    }

    /*If the bar can fit on a row that is already in the ladder*/
    else
    {
        free(l->ladder[rowIndex][colIndex]);
        l->ladder[rowIndex][colIndex] = b;
        l->numBars++;
    }
}

/***GETTERS***/

int getColIndex(int c)
{
    if (c == 0)
        return 0;
    return c - 1;
}

int getRowIndex(Ladder l, int colIndex)
{
    int left;
    int right;

    int rowIndex = 0;

    /*If there are no bars in the ladder yet, then the first bar will go in row 0*/
    if (l->numBars == 0)
    {
        return rowIndex;
    }

    /**used to iterate and check left values**/
    if (colIndex == 0)
    {
        left = 0;
    }
    else
    {
        left = colIndex - 1;
    }

    /**used to iterate and check right values of the collumn that the bar will go in**/
    if (colIndex == l->numCols - 1)
    {
        right = colIndex;
    }
    else
    {
        right = colIndex + 1;
    }

    /**Check if there is a bar to the left of the columnIndex, check if there is a bar to the right of the columnIndex
     * check if there is a bar in the current columnIndex. If all are false then the bar can go at the current row in the 
     * column index. Otherwise go to the next row in the ladder*/

    int startIndex = l->numRows - 1;
    while ((l->ladder[startIndex][left]->set == false) && (l->ladder[startIndex][right]->set == false) && (l->ladder[startIndex][colIndex]->set == false))
    {
        if (startIndex == 0)
        {
            break;
        }
        startIndex--;
    }

    rowIndex = startIndex + 1;
    return rowIndex;
}

int getLargestIndex(int *arr, int size)
{
    int largestIndex = -1;
    int largest = -1;
    forall(size)
    {
        if (arr[x] > largest)
        {
            largestIndex = x;
            largest = arr[x];
        }
    }
    return largestIndex;
}

/****MAIN DRIVER***/

void driver(Ladder l, int *permutation, int size)
{
    if (size == 1)
    {
        char *s = l->print(l);
        print(s);
        clear(s);
        return;
    }

    else
    {
        int largestIndex = getLargestIndex(permutation, size);

        /*add all the bars to the ladder based on inversions in the permutation*/
        foreach (largestIndex, size)
        {
            if (permutation[largestIndex] > permutation[x])
            {
                Bar b = new_bar(permutation[largestIndex], permutation[x]);
                int colIndex = getColIndex(x);
                int rowIndex = getRowIndex(l, colIndex);
                b->colIndex = colIndex;
                b->rowIndex = rowIndex;
                l->add(l, b, rowIndex, colIndex);
            }
        }

        int* arr = calloc(size-1, sizeof(int));
        copyArray(&arr, permutation, largestIndex, size);
        driver(l, arr, size-1);
        free(arr);

    }
}



void run(int* perm, int size)
{
    printf("\n");
    forall(size)
    {
        printf("%d ", perm[x]);
    }
    printf("\n");
    Ladder l = new_ladder(size-1);
    driver(l, perm, size);
    l->del(l);
}


/*****END SECTION****/





void rightSwap(Ladder l, Bar b, int rowIndex, int colIndex)
{
    if(rowIndex < 0)return;
    if(colIndex >= l->numCols)return;

    int prevRow = b->rowIndex;
    int prevCol = b->colIndex;

    free(l->ladder[rowIndex][colIndex]);

    setColIndex(b, colIndex);
    setRowIndex(b, rowIndex);
    l->ladder[rowIndex][colIndex] = b;

    l->ladder[prevRow][prevCol] = dummy_bar();
}


void getSwapIndex(Bar topBar, int vals[])
{

    vals[0] = topBar->rowIndex+1;

    vals[1] = topBar->colIndex;

}

