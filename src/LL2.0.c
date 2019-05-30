#include "utilities.h"
#include "DynamicString.h"
#include "StringArray.h"
#include "Numbers.h"
#include "LL2.0.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/***STATIC FUNCTIONS***/

static void copyArray(int **write, int *read, int largestIndex, int size)
{
    int *temp = *write;
    int i = 0;
    forall(size)
    {
        if (x != largestIndex)
        {
            temp[i] = read[x];
            i++;
        }
    }
}

static int compInts(const void *a, const void *b)
{
    int *v1 = (int *)a;
    int *v2 = (int *)b;

    int numOne = *v1;
    int numTwo = *v2;

    return (numOne - numTwo);
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

Bar clone_bar(Bar b)
{
    new_object(Bar, clone, 1);

    clone->set = b->set;
    clone->rowIndex = b->rowIndex;
    clone->colIndex = b->colIndex;

    clone->vals[0] = b->vals[0];
    clone->vals[1] = b->vals[1];

    return clone;
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

    int memSize = 400;

    Ladder ll = (Ladder)l;
    forall(ll->numCols)
    {
        memSize += 10;
        sprintf(stat, "%d", x + 1);
        s = realloc(s, memSize * sizeof(char));
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

        int *arr = calloc(size - 1, sizeof(int));
        copyArray(&arr, permutation, largestIndex, size);
        driver(l, arr, size - 1);
        free(arr);
    }
}

void run(int *perm, int size)
{
    printf("\n");
    forall(size)
    {
        printf("%d ", perm[x]);
    }
    printf("\n");
    Ladder l = new_ladder(size - 1);
    driver(l, perm, size);
    int arr[2];

    getFirstTurnBarIndex(l, perm, arr);

    printf("%d %d\n", arr[0], arr[1]);
    rightSwap(l, l->ladder[arr[0]][arr[1]], arr[0] - 3, arr[1] + 1);
    char* s = l->print(l);
    print(s);
    clear(s);

    fixCleanLevel(l, 6);

    s = l->print(l);
    print(s);
    clear(s);
    //l->del(l);
}

/*****END SECTION****/

/***SETTERS***/

void setRowIndex(Bar b, int index)
{
    b->rowIndex = index;
}

void setColIndex(Bar b, int index)
{
    b->colIndex = index;
}

void getSwapIndex(Bar topBar, int vals[])
{

    vals[0] = topBar->rowIndex + 1;

    vals[1] = topBar->colIndex;
}

/**For finding the first turn bar***/
void getFirstTurnBarIndex(Ladder l, int *perm, int vals[])
{

    int startRow = l->numRows - 1;
    int numElements = l->numCols + 1;

    int currElem = -1;

    qsort(perm, numElements, sizeof(int), compInts);

    /***Go through each elem in the perm**/
    for (int i = 0; i < numElements; i++)
    {
        currElem = perm[i];
        /***Go through each collumn in the ladder***/
        for (int j = 0; j < l->numCols; j++)
        {
            /***Go through each row in that collumn***/
            for (int k = startRow; k >= 0; k--)
            {
                Bar b = l->ladder[k][j];
                if (b == NULL)
                    continue;
                if (b->set == false)
                    continue;
                int v1 = b->vals[0];
                int v2 = b->vals[1];
                if (currElem == v1 || currElem == v2)
                {
                    setFirstTurnBar(l, currElem, k, j, vals);
                }
            }
        }
    }
}

void setFirstTurnBar(Ladder l, int currElem, int rowIndex, int colIndex, int vals[])
{
    /**Check the remaining updward bars from rowIndex in that coluum*/
    for (int i = rowIndex - 1; i >= 0; i--)
    {
        /*Get the next upward bar*/
        Bar b = l->ladder[i][colIndex];
        if (b->set == false)
            continue;
        int valOne = b->vals[0];
        int valTwo = b->vals[1];

        /**if the bar above the current bar contains the current element then the current bar is the 
         * turn bar, else it is not***/
        if (currElem == valOne || currElem == valTwo)
        {
            vals[0] = rowIndex;
            vals[1] = colIndex;
        }
        else
        {
            break;
        }
    }
}
/***End finding the first turn bar***/

void readjustLadder(Ladder ll, Ladder l, Bar b)
{

    ll->add(ll, b, b->rowIndex, b->colIndex);
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar bb = l->ladder[i][j];
            if (bb->vals[0] == b->vals[0] && b->vals[1] == bb->vals[1])
            {
                continue;
            }
            setRowIndex(bb, i + 1);
            setColIndex(bb, j);

            ll->add(ll, bb, bb->rowIndex, bb->colIndex);
        }
    }
    free(l->ladder);
    l->ladder = ll->ladder;
    l->numBars = ll->numBars;
    l->numCols = ll->numCols;
    l->numRows = ll->numRows;
}

void rightSwap(Ladder l, Bar b, int rowToGo, int colIndex)
{
    resetAllRows(l);
    if (colIndex >= l->numCols)
        return;

    if (colIndex < 0)
        return;

    /**If a new row needs to be added to the ladder**/
    if (rowToGo < 0)
    {
        b->rowIndex = 0;
        b->colIndex = colIndex;
        Ladder ll = new_ladder(l->numCols);
        readjustLadder(ll, l, b);
        resetAllRows(l);
        //return;
    }

    /**Get the current row and column**/
    else
    {
        int currentRow = b->rowIndex;
        int currentCol = b->colIndex;

        /***Make sure there is a dummy bar in the current position of the bar that is about to be moved**/
        Bar clone = clone_bar(b);
        Bar leftBar = NULL;
        Bar rightBar = NULL;
        Bar midBar = NULL;

        /***Get the left, right and middle bar relative to where the current bar needs to go**/
        if (colIndex > 0)
        {
            leftBar = l->ladder[rowToGo][colIndex - 1];
        }
        midBar = l->ladder[rowToGo][colIndex];

        if (colIndex < l->numCols - 1)
        {
            rightBar = l->ladder[rowToGo][colIndex + 1];
        }

       

        /***Set the location to go to the bar**/
        setColIndex(clone, colIndex);
        setRowIndex(clone, rowToGo);
        l->ladder[rowToGo][colIndex] = clone;

        /**If the bar to the left of where the bar needs to go is set, then you need to move the leftBar up a row**/
        if ((leftBar != NULL) && leftBar->set)
        {
            int rowIndex = leftBar->rowIndex - 1;
            rightSwap(l, leftBar, rowIndex, leftBar->colIndex);
        }

        /**If the bar to the place of where the bar needs to go is set, then you need to move the midBar up a row**/

        if (midBar->set)
        {
            int rowIndex = midBar->rowIndex - 1;
            rightSwap(l, midBar, rowIndex, midBar->colIndex);
        }

        /**If the bar to the right of the place of where the bar needs to go is set, then you need to move the rightBar up a row**/

        if ((rightBar != NULL) && rightBar->set)
        {
            int rowIndex = rightBar->rowIndex - 1;
            rightSwap(l, rightBar, rowIndex, rightBar->colIndex);
        }
         /***Get set the current position of the bar to the dummy value***/
        Bar curr = l->ladder[currentRow][currentCol];
        if(sameBar(curr, b))
        {
            l->ladder[currentRow][currentCol] = dummy_bar();
            setRowIndex(l->ladder[currentRow][currentCol], currentRow);
            setColIndex(l->ladder[currentRow][currentCol], currentCol);
        }
        
    }
}

void resetAllRows(Ladder l)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            b->rowIndex = i;
        }
    }
}

void fixCleanLevel(Ladder l, int cleanLevel)
{
    int temp = l->numRows;
    for (int i = 0; i < temp; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            /*printf("%d\n", b->vals[0]);
            printf("%d\n", b->vals[1]);
            printf("%d\n", b->rowIndex);
            printf("\n");*/

            if ((b->vals[0] == cleanLevel) || (b->vals[1] == cleanLevel))
            {
                resetCleanLevel(l, b, b->rowIndex, cleanLevel);
            }
        }
    }
}

void resetCleanLevel(Ladder l, Bar b, int rowNum, int cleanLevel)
{
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar bb = l->ladder[i][j];
            if (bb->set == false)
                continue;
            if ((bb->vals[0] < cleanLevel) && (bb->vals[1] < cleanLevel))
            {
                rightSwap(l, b, bb->rowIndex - 1, b->colIndex);
            }
        }
    }
}

/**END SETTERS***/

void mainAlgorithm(Ladder root, int *perm)
{
    int arr[2];

    getFirstTurnBarIndex(root, perm, arr);

    printf("%d %d\n", arr[0], arr[1]);
    rightSwap(root, root->ladder[arr[0]][arr[1]], arr[0] - 3, arr[1] + 1);

    fixCleanLevel(root, 6);
}







bool sameBar(Bar b1, Bar b2)
{
    if(b1->vals[0] == b2->vals[0] && (b1->vals[1] == b2->vals[1]))return true;
    return false;
}
