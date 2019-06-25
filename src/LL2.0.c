#include "utilities.h"
#include "DynamicString.h"
#include "StringArray.h"
#include "Numbers.h"
#include "Color.h"
#include "LL2.0.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/***GLOBAL VARIABLES**/

/***STATIC FUNCTIONS***/

int recursionCount = 0;
int ladderCount = 1;

int globalCount = 0;
char ladders[1000][1000];

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

static void swapVals(int *v1, int *v2)
{
    int temp = *(v1);
    *v1 = *v2;
    *v2 = temp;
}
/***END**/

/****SECTION FOR GENERATING THE MIN HEIGHT ROOT LADDER***/
Bar new_bar(int valOne, int valTwo)
{
    new_object(Bar, b, 1);
    b->vals[0] = valOne;
    b->vals[1] = valTwo;

    b->set = true;
    b->beenSwapped = false;
    return b;
}

Bar dummy_bar(void)
{
    new_object(Bar, b, 1);
    b->rowIndex = -1;
    b->colIndex = -1;
    b->set = false;
    b->beenSwapped = false;
    return b;
}

Bar clone_bar(Bar b)
{
    new_object(Bar, clone, 1);

    clone->set = b->set;
    clone->beenSwapped = b->beenSwapped;
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

Ladder clone_ladder(Ladder l)
{
    new_object(Ladder, clone, 1);

    clone->add = l->add;
    clone->print = l->print;
    clone->del = l->del;
    clone->numCols = l->numCols;

    for (int i = 0; i < l->numRows; i++)
        for (int j = 0; j < l->numCols; j++)
        {
            Bar temp = clone_bar(l->ladder[i][j]);
            clone->add(clone, temp, temp->rowIndex, temp->colIndex);
        }

    return clone;
}

char *print_bar(void *b)
{
    Bar bb = (Bar)b;

    char *s = calloc(10, sizeof(char));
    char temp[10];
    if (bb->set)
        strcpy(s, "(");
    else
        strcpy(s, "[");

    sprintf(temp, "%d", bb->vals[0]);
    strcat(s, temp);
    strcat(s, ",");
    sprintf(temp, "%d", bb->vals[1]);
    strcat(s, temp);
    if (bb->set)
        strcat(s, ")");
    else
        strcat(s, "]");

    strcat(s, " ");
    return s;
}
char *print_ladder(void *l)
{
    char *s = calloc(100, sizeof(char));
    strcpy(s, "Ladder Number:");
    char *temp = NULL;
    char stat[100];
    sprintf(stat, "%d", ladderCount);
    strcat(s, stat);
    strcat(s, "\n");
    ladderCount++;

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

char *printLadderTwo(void *l)
{
    char *s = calloc(100, sizeof(char));
    strcpy(s, "Ladder Number:");
    char *temp = NULL;
    char stat[100];
    sprintf(stat, "%d", ladderCount);
    strcat(s, stat);
    strcat(s, "\n");
    ladderCount++;

    int memSize = 100;

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

    forall(ll->numRows)
    {
        Bar *row = ll->ladder[x];
        if (emptyRow(row, ll->numCols) == false)
        {
            for (int i = 0; i < ll->numCols; i++)
            {
                temp = print_bar(ll->ladder[x][i]);
                memSize += strlen(temp) + 5;
                s = realloc(s, memSize * sizeof(char));
                strcat(s, temp);
                free(temp);
            }
            strcat(s, "\n");
        }
    }

    return s;
}
void printLadder(char *l)
{
    forall(strlen(l))
    {
        char c = l[x];
        if (isdigit(c) && c != '0')
        {
            printf(GREEN "%c" COLOR_RESET, c);
        }
        else if (c == '(' || c == ')')
        {
            printf(GREEN "%c" COLOR_RESET, c);
        }
        else
        {
            printf("%c", c);
        }
    }
}

void printLadderNoColor(char* l)
{
    forall(strlen(l))
    {
        printf("%c", l[x]);
    }
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
    if (l->numBars == 0 && l->numRows == 0)
    {
        new_object(Bar **, ladder, 1);
        l->ladder = ladder;
        l->ladder[0] = calloc(l->numCols, sizeof(Bar));
        forall(l->numCols)
        {
            l->ladder[0][x] = dummy_bar();
            Bar b = l->ladder[0][x];
            setRowIndex(b, 0);
            setColIndex(b, x);
        }
        free(l->ladder[rowIndex][colIndex]);
        setRowIndex(b, rowIndex);
        setColIndex(b, colIndex);
        l->ladder[rowIndex][colIndex] = b;

        l->numBars++;
        l->numRows++;

        return;
    }

    /*If a new row needs to be added to the ladder*/
    if (rowIndex >= l->numRows)
    {
        int memSize = rowIndex + 1;
        l->ladder = realloc(l->ladder, memSize * sizeof(Bar *));
        l->ladder[rowIndex] = calloc(l->numCols, sizeof(Bar));
        forall(l->numCols)
        {
            l->ladder[rowIndex][x] = dummy_bar();
            Bar b = l->ladder[rowIndex][x];
            setRowIndex(b, rowIndex);
            setColIndex(b, x);
        }
        free(l->ladder[rowIndex][colIndex]);
        setRowIndex(b, rowIndex);
        setColIndex(b, colIndex);
        l->ladder[rowIndex][colIndex] = b;

        l->numBars++;
        l->numRows++;
    }

    /*If the bar can fit on a row that is already in the ladder*/
    else
    {

        free(l->ladder[rowIndex][colIndex]);
        setRowIndex(b, rowIndex);
        setColIndex(b, colIndex);
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
    if (l->numRows == 0)
        return rowIndex;

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

Bar getBar(Ladder l, int row, int col)
{
    if (row < 0 || row > l->numRows || col < 0 || col > l->numCols)
        return NULL;
    return l->ladder[row][col];
}

Bar getTopBar(Ladder l)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            if (l->ladder[i][j]->set)
            {
                return getBar(l, i, j);
            }
        }
    }
    return NULL;
}

Bar getUpperBar(Ladder l, Bar b)
{
    int rowIndex = b->rowIndex - 1;
    int colIndex = b->colIndex;

    Bar upperBar = NULL;
    while (rowIndex >= 0)
    {
        upperBar = l->ladder[rowIndex][colIndex];

        if (emptyBar(upperBar) == false)
        {
            return upperBar;
        }
        rowIndex--;
    }
    return NULL;
}

Bar getRightBar(Ladder l, Bar b)
{
    int rowIndex = b->rowIndex - 1;
    int colIndex = b->colIndex + 1;

    if (rowIndex < 0 || colIndex >= l->numCols)
        return NULL;

    Bar upperBar = NULL;
    while (rowIndex >= 0)
    {
        upperBar = l->ladder[rowIndex][colIndex];

        if (emptyBar(upperBar) == false)
        {
            return upperBar;
        }
        rowIndex--;
    }
    return NULL;
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

void rightSwap(Ladder l, Bar b, int rowToGo, int colIndex)
{
    if (colIndex >= l->numCols)
        return;

    if (colIndex < 0)
        return;

    /**If a new row needs to be added to the ladder**/
    if (rowToGo < 0)
    {

        //create a new ladder = to current ladder size + 1
        Bar **ladder = calloc(l->numRows + 1, sizeof(Bar *));
        ladder[0] = calloc(l->numCols, sizeof(Bar));

        //set the ladder[0] to a new row with the bar to swap
        forall(l->numCols)
        {
            if (x != colIndex)
            {
                ladder[0][x] = dummy_bar();
                setRowIndex(ladder[0][x], 0);
                setColIndex(ladder[0][x], x);
            }
            else
            {
                ladder[0][x] = clone_bar(b);
                setRowIndex(ladder[0][x], 0);
                setColIndex(ladder[0][x], x);

                int row = b->rowIndex;
                int col = b->colIndex;
                Bar dummy = getBar(l, row, col);
                //free(dummy);
                dummy = dummy_bar();
                l->ladder[row][col] = dummy;
            }
        }
        //set each ladder[x] from 1 to size = to prev ladder[x-1]
        int count = 1;
        forall(l->numRows)
        {
            ladder[count] = l->ladder[x];
            count++;
        }

        //free the prev ladder
        free(l->ladder);

        //set the prev ladde to the new ladder
        l->ladder = ladder;

        //numrows++
        l->numRows++;
        resetAllRows(l);
    }

    /**Get the current row and column**/
    else
    {

        /***Make sure there is a dummy bar in the current position of the bar that is about to be moved**/
        Bar clone = clone_bar(b);
        free(l->ladder[b->rowIndex][b->colIndex]);
        l->ladder[clone->rowIndex][clone->colIndex] = dummy_bar();
        Bar temp = l->ladder[clone->rowIndex][clone->colIndex];
        setRowIndex(temp, clone->rowIndex);
        setColIndex(temp, clone->colIndex);

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
    }
    resetAllRows(l);
}

void leftSwap(Ladder l, Bar b, int rowToGo, int colToGo)
{

    if (rowToGo > l->numRows || rowToGo < 0 || colToGo > l->numCols || colToGo < 0)
        return;
    /***Make sure there is a dummy bar in the current position of the bar that is about to be moved**/

    Bar bb = findBar(l, b);
    if (bb == NULL)
        return;
    int rowIndex = bb->rowIndex;
    int colIndex = bb->colIndex;
    l->ladder[rowIndex][colIndex] = dummy_bar();
    l->ladder[rowToGo][colToGo] = bb;
    resetAllRows(l);
}

void resetAllRows(Ladder l)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            b->rowIndex = i;
            b->colIndex = j;
        }
    }
}

void removeRow(Ladder l, int row)
{

    Bar **ladder = calloc(l->numRows, sizeof(Bar *));
    forall(l->numRows)
    {
        if (x != row)
        {
            ladder[x] = calloc(l->numCols, sizeof(Bar));
            ladder[x] = l->ladder[x];
        }
    }

    free(l->ladder);
    l->ladder = ladder;
    l->numRows--;
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

bool sameBar(Bar b1, Bar b2)
{
    if (b1->vals[0] == b2->vals[0] && (b1->vals[1] == b2->vals[1]))
    {
        return true;
    }
    return false;
}

Bar findBar(Ladder l, Bar b)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar temp = l->ladder[i][j];
            if (sameBar(temp, b))
            {
                return temp;
            }
        }
    }
    return NULL;
}

bool emptyRow(Bar *row, int size)
{
    if (row == NULL)
        return false;
    forall(size)
    {
        if (row[x]->set == true)
            return false;
    }
    return true;
}

int getEmptyRow(Ladder l)
{
    forall(l->numRows)
    {
        if (emptyRow(l->ladder[x], l->numCols))
        {
            return x;
        }
    }
    return -1;
}

bool emptyBar(Bar b)
{
    if (b == NULL)
        return false;
    if (b->set)
        return false;
    return true;
}

bool canBeMovedUp(Ladder l, Bar b)
{
    int barRow = b->rowIndex;
    int barCol = b->colIndex;

    int upRow = barRow - 1;

    if (barRow == 0)
        return false;

    bool left;
    bool mid;
    bool right;

    if (barCol > 0)
    {
        Bar temp = l->ladder[upRow][barCol - 1];
        if (temp->set)
        {
            left = true;
        }
        else
        {
            left = false;
        }
    }
    else
    {
        left = false;
    }
    if (barCol < l->numCols - 1)
    {
        Bar temp = l->ladder[upRow][barCol + 1];
        if (temp->set)
        {
            right = true;
        }
        else
        {
            right = false;
        }
    }
    else
    {
        right = false;
    }
    Bar temp = l->ladder[upRow][barCol];
    if (temp->set)
    {
        mid = true;
    }
    else
    {
        mid = false;
    }

    if (left == false && mid == false && right == false)
    {
        return true;
    }
    return false;
}

/****TEST FUNCTIONS FOR NON-CANONICAL FORM****/

void add_empty_row(Ladder l, int n)
{
    if (l->numRows == 0)
    {
        l->ladder = calloc(1, sizeof(Bar *));
        l->ladder[0] = calloc(n, sizeof(Bar));
        forall(n)
        {
            l->ladder[0][x] = dummy_bar();
            Bar b = l->ladder[0][x];
            setRowIndex(b, 0);
            setColIndex(b, x);
        }
        l->numRows++;
    }
    else
    {
        int memSize = l->numRows + 1;
        int index = l->numRows;
        l->ladder = realloc(l->ladder, memSize * sizeof(Bar *));
        l->ladder[index] = calloc(n, sizeof(Bar));
        forall(n)
        {
            l->ladder[index][x] = dummy_bar();
            Bar b = l->ladder[index][x];
            setRowIndex(b, index);
            setColIndex(b, x);
        }
        l->numRows++;
    }
}

void generate_test_root(Ladder root, int *perm, int size)
{
    forall(root->numCols * root->numCols)
    {
        add_empty_row(root, root->numCols);
    }
    int count = root->numRows;

    if (size == 1)
        return;

    if (size == 1)
    {
        return;
    }

    else
    {
        int largestIndex = getLargestIndex(perm, size);

        /*add all the bars to the ladder based on inversions in the permutation*/
        foreach (largestIndex, size)
        {
            if (perm[largestIndex] > perm[x])
            {

                Bar b = new_bar(perm[largestIndex], perm[x]);
                int colIndex = getColIndex(x);
                int rowIndex = count;
                b->colIndex = colIndex;
                b->rowIndex = rowIndex;
                printf("%d\n", root->numRows);
                root->add(root, b, rowIndex, colIndex);
                count++;
            }
        }

        int *arr = calloc(size - 1, sizeof(int));
        copyArray(&arr, perm, largestIndex, size);
        generate_test_root(root, arr, size - 1);
        free(arr);
    }
}

/**Check if bar b is visible from the level which represents the path of element with a value = to level**/
bool isDownWardVisible(Ladder l, Bar b, int level)
{
    int left = 0;
    int right = 0;
    int mid = 0;

    int colIndex = b->colIndex;

    /**Case 1: b is as right as possible**/
    if (colIndex == l->numCols - 1)
        return false;

    int rowCount = b->rowIndex - 1;

    Bar upperBar = NULL;

    /**Find the bar directly above b that contains the clean level**
     * This will be the upper limit for checking if b is downward visible from level**/
    while (rowCount >= 0)
    {
        Bar temp = l->ladder[rowCount][colIndex];

        /**Case in which there is a bar, b`, between bar b and the level k which is not part of the path of k**/
        if (temp->set && temp->vals[0] != level)
        {
            return false;
        }

        if (temp->vals[0] == level)
        {
            upperBar = temp;
            break;
        }
        rowCount--;
    }

    /***Case in which there was not a bar between 0 and b's row -1**/
    if (upperBar == NULL)
        return false;

    rowCount = b->rowIndex - 1;
    if (colIndex == 0)
    {
        left = -1;
    }
    else
    {
        left = colIndex - 1;
    }
    right = colIndex + 1;
    mid = colIndex;

    int rightCount = 0;
    for (int i = rowCount; i > upperBar->rowIndex; i--)
    {
        Bar leftBar = NULL;
        if (left >= 0)
        {
            leftBar = l->ladder[i][left];
        }

        Bar midBar = l->ladder[i][mid];
        Bar rightBar = l->ladder[i][right];

        /**If there is a bar to the left of the column of the bar b, then b is not downward visible from level*/
        if (leftBar != NULL && leftBar->set)
        {
            return false;
        }

        /**If there is a bar to the right of b that is not in the path = to the level then b is not downard visble from
         * the level*/
        if (rightBar->set && rightBar->vals[0] != level)
        {
            return false;
        }

        if (rightBar->set && rightBar->vals[0] == level)
        {
            rightCount++;
        }

        /**If ther is a bar above b that is not part of the path of the level then b cannot be right swapped**/
        if (midBar->set)
        {
            return false;
        }
    }

    if (rightCount != 1)
    {
        return false;
    }

    return true;
    /*for (int i = 0; i < b->rowIndex; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar cleanBar = l->ladder[i][j];
            if (cleanBar->vals[0] == level && cleanBar->set == true)
            {
                mid = b->colIndex;
                if (b->colIndex > 0)
                {
                    left = b->colIndex - 1;
                }
                if (b->colIndex < l->numCols - 1)
                {
                    right = b->colIndex + 1;
                }
                for (int i = b->rowIndex - 1; i > cleanBar->rowIndex; i--)
                {
                    Bar leftBar = l->ladder[i][left];
                    Bar rightBar = l->ladder[i][right];
                    Bar midBar = l->ladder[i][mid];
                    if (leftBar->set == true && sameBar(leftBar, cleanBar)==false)
                        return false;
                    if (midBar->set == true && sameBar(midBar, cleanBar)==false)
                        return false;
                    if (rightBar->set == true && sameBar(rightBar, cleanBar)==false)
                        return false;
                }
                return true;
            }
        }
    }
    return false;*/
}

void setActiveBar(Ladder l, int level, int *index)
{
    for (int i = l->numRows - 1; i >= 0; i--)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->set && b->vals[0] < level && b->beenSwapped == false)
            {
                if (isDownWardVisible(l, b, level))
                {
                    index[0] = b->rowIndex;
                    index[1] = b->colIndex;
                }
            }
        }
    }
}

void setActiveBars(Ladder l, int level, Bar *bars, int *numBars)
{

    int n = *numBars;
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar currBar = l->ladder[i][j];
            if (currBar->vals[0] == level)
            {
                for (int k = currBar->rowIndex + 1; k < l->numRows; k++)
                {
                    Bar downBar = l->ladder[k][j];
                    if (downBar->set && isDownWardVisible(l, downBar, level))
                    {
                        bars[n] = downBar;
                        n++;
                        break;
                    }
                }
            }
        }
    }

    *numBars = n;
}

int getCleanLevel(int *perm, Ladder l)
{
    qsort(perm, l->numCols + 1, sizeof(int), compInts);

    /*start at the end of the array and go backwards**/
    for (int i = l->numCols; i >= 0; i--)
    {
        int val = perm[i];
        int rowIndex = findMaxRowOfVal(l, val);

        for (int j = 0; j < l->numRows; j++)
            for (int k = 0; k < l->numCols; k++)
            {
                Bar b = l->ladder[j][k];
                if (b->vals[0] < val && b->vals[1] < val && b->set && b->rowIndex < rowIndex)
                {
                    char *s = print_bar(b);
                    print(s);
                    clear(s);
                    return val + 1;
                }
            }
    }
    return perm[0];
}

int findMaxRowOfVal(Ladder l, int val)
{
    int row = -1;
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->vals[0] == val)
            {
                row = b->rowIndex;
                continue;
            }
        }
    }
    return row;
}

int findMinRowOfVal(Ladder l, int val)
{
    int row = -1;
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->vals[0] == val)
            {
                row = b->rowIndex;
                return row;
            }
        }
    }
    return row;
}

void setActiveRegion(Ladder l, Bar activeBar, int cleanLevel, int min, int max, int *arr)
{
    if (cleanLevel > max || cleanLevel < min)
        return;

    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = getBar(l, i, j);
            if (b->vals[0] == cleanLevel)
            {
                arr[0] = b->rowIndex;
                setUpperRegion(l, activeBar, arr[0] - 1, arr);
                return;
            }
        }
    }
}

void setUpperRegion(Ladder l, Bar activeBar, int level, int *arr)
{
    bool flag = false;

    int barLevel = activeBar->vals[0];
    for (int i = level; i >= 0; i--)
    {
        if (emptyRow(l->ladder[i], l->numCols) == false)
        {
            forall(l->numCols)
            {
                Bar b = getBar(l, i, x);
                if (b->set)
                {
                    int lvl = b->vals[0];
                    if (barLevel == lvl)
                    {
                        arr[0] = i + 1;
                        flag = true;
                        goto exitCode;
                    }
                    if (barLevel < lvl)
                    {
                        arr[0] = i + 3;
                        flag = true;
                        goto exitCode;
                    }
                }
            }
        }
    }

exitCode:
    if (flag == false)
    {
        arr[0] = 0;
    }
    else
    {
        return;
    }
}

void setLowerRegion(Ladder l, int level, int *arr)
{
    return;
}
void findRowAndCol(Ladder l, Bar b, int *ar)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            if (sameBar(b, l->ladder[i][j]))
            {
                ar[0] = l->ladder[i][j]->rowIndex;
                ar[0] = l->ladder[i][j]->colIndex;
                return;
            }
        }
    }
}

void findAllChildren(Ladder l, int *perm, Bar currBar, int k, int size)
{
    recursionCount++;

    char *s = printLadderTwo(l);
    if (doubleLadder(s, ladders, globalCount))
    {
        printf("ERROR: DOUBLE LADDER\n");
        printf("%s\n", s);
    }
    addToLadders(ladders, s, globalCount);
    globalCount++;

    printLadder(s);
    clear(s);

    int rowIndex = -1;
    int colIndex = -1;


    //printf("RECURSION COUNT %d\n", recursionCount++);

    //Ladder clone = clone_ladder(l);

    for (int i = 0; i < l->numCols + 1; i++)
    {
        if (perm[i] >= k)
        {

            Bar bars[20];
            int numBars = 0;
            setActiveBars(l, perm[i], bars, &numBars);
            int newLevel = -1;

            if (recursionCount <= 1)
                newLevel = perm[i];
            else
            {
                newLevel = perm[i] + 1;
            }

            forall(numBars)
            {
                rowIndex = bars[x]->rowIndex;
                colIndex = bars[x]->colIndex;

                Bar b = getBar(l, rowIndex, colIndex);
                int region[1] = {-1};
                setActiveRegion(l, b, perm[i], perm[0], perm[size - 1], region);

                if (b->set == false)
                {
                    continue;
                }

                Bar upperBar = getUpperBar(l, b);
                Bar rightBar = getRightBar(l, b);
                swapVals(&(upperBar->vals[1]), &(rightBar->vals[1]));

                Bar cloneBar = clone_bar(b);
                rightSwap(l, b, region[0], b->colIndex + 1);

                findAllChildren(l, perm, b, newLevel, size);
                leftSwap(l, cloneBar, cloneBar->rowIndex, cloneBar->colIndex);
                swapVals(&(upperBar->vals[1]), &(rightBar->vals[1]));
                /* printf("AFTER LEFT SWAP:\n\n");
                s = printLadderTwo(l);
                printLadder(s);
                clear(s);*/
            }
        }
    }

    for (int i = 0; i < l->numCols + 1; i++)
    {
        if (perm[i] == k - 1)
        {

            Bar bars[20];
            int numBars = 0;
            setActiveBars(l, perm[i], bars, &numBars);

            //int newLevel = perm[i]+1;
            forall(numBars)
            {
                rowIndex = bars[x]->rowIndex;
                colIndex = bars[x]->colIndex;

                Bar b = l->ladder[rowIndex][colIndex];
                //Bar temp = clone_bar(b);
                if (b->set == false)
                {
                    continue;
                }
                int region[1] = {-1};
                setActiveRegion(l, b, perm[i], perm[0], perm[size - 1], region);

                Bar upperBar = getUpperBar(l, b);
                Bar rightBar = getRightBar(l, b);
                swapVals(&(upperBar->vals[1]), &(rightBar->vals[1]));

                Bar cloneBar = clone_bar(b);

                rightSwap(l, b, region[0], b->colIndex + 1);

                //b = findBar(clone, temp);
                //free(temp);

                findAllChildren(l, perm, b, k, size);
                leftSwap(l, cloneBar, cloneBar->rowIndex, cloneBar->colIndex);
                swapVals(&(upperBar->vals[1]), &(rightBar->vals[1]));

                /* printf("AFTER LEFT SWAP:\n\n");
                s = printLadderTwo(l);
                printLadder(s);
                clear(s);*/
            }

            /* int arr[2] = {-1, -1};
            setActiveBar(l, perm[i], arr);
            if (arr[0] == -1 || arr[1] == -1)
                return;

            rowIndex = arr[0];
            colIndex = arr[1];

            Bar b = getBar(l, rowIndex, colIndex);
            Bar cloneBar = clone_bar(b);

            int region[1] = {-1};
            setActiveRegion(l, b, perm[i], perm[0], perm[size - 1], region);

            rightSwap(l, b, region[0], b->colIndex + 1);
            findAllChildren(l, perm, b, k, size);
            leftSwap(l, cloneBar, cloneBar->rowIndex, cloneBar->colIndex);
            printf("AFTER LEFT SWAP:\n\n");
            s = printLadderTwo(l);
            printLadder(s);
            clear(s);*/
        }
    }
}

bool doubleLadder(char *l, char ladders[1000][1000], int count)
{
    forall(count)
    {
        if (strcmp(l, ladders[x]) == 0)
        {
            return true;
        }
    }
    return false;
}

void addToLadders(char ladders[1000][1000], char *l, int count)
{
    strcpy(ladders[count], l);
}