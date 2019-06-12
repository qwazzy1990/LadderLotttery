#include "utilities.h"
#include "DynamicString.h"
#include "StringArray.h"
#include "Numbers.h"
#include "LL2.0.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/***GLOBAL VARIABLES**/

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
        l->ladder = realloc(l->ladder, memSize * sizeof(Bar **));
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
    printf("Permutation\n");
    forall(size)
    {
        printf("%d ", perm[x]);
    }
    printf("\n");
    Ladder l = new_ladder(size - 1);

    driver(l, perm, size);

    printf("Root Ladder:");
    char *s = l->print(l);
    print(s);
    clear(s);

    mainAlgorithm(l, perm);
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
    removeMultiple(ll);
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

        if (emptyBar(leftBar) && emptyBar(midBar) && emptyBar(rightBar))
        {
            Ladder clone = clone_ladder(l);
            removeMultiple(clone);
            removeEmptyRows(clone);
            char *s = clone->print(clone);
            print(s);
            clear(s);
            clone->del(clone);
        }
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
        //Bar curr = l->ladder[currentRow][currentCol];
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

void resetLadder(Ladder l)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->set == false)
            {
                continue;
            }
            if (canBeMovedUp(l, b))
            {
                rightSwap(l, b, b->rowIndex - 1, b->colIndex);
                removeMultiple(l);
                removeEmptyRows(l);
            }
        }
    }
}

void removeMultiple(Ladder l)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->set == true)
            {
                //sameBar(b, b);
                int row = 0;
                int col = 0;
                if ((j % (l->numCols - 1)) == 0)
                {
                    row = i + 1;
                    col = 0;
                }
                else
                {
                    row = i;
                    col = j + 1;
                }
                removeMultipleTwo(l, b, row, col);
            }
        }
    }
}

void removeMultipleTwo(Ladder l, Bar b, int row, int col)
{

    int tempCol = col;
    //printf("Here\n%d %d %d %d\n", b->vals[0], b->vals[1], row, col);
    for (int i = row; i < l->numRows; i++)
    {
        //printf("Here\n%d %d %d %d\n", b->vals[0], b->vals[1], i, col);
        if (i == row)
        {
            tempCol = col;
        }
        else
        {
            tempCol = 0;
        }
        for (int j = tempCol; j < l->numCols; j++)
        {
            Bar temp = l->ladder[i][j];
            if (b->vals[0] == 4 && b->vals[1] == 1)
            {
            }
            if (sameBar(b, temp))
            {
                l->ladder[i][j] = dummy_bar();
                temp = l->ladder[i][j];
                setRowIndex(temp, i);
                setColIndex(temp, j);
            }
        }
    }
}

void removeEmptyRows(Ladder l)
{
    Bar **ladder = NULL;
    int count = 0;
    int memSize = 0;
    forall(l->numRows)
    {
        if (emptyRow(l->ladder[x], l->numCols) == false)
        {
            if (count == 0)
            {
                memSize++;
                ladder = calloc(memSize, sizeof(Bar *));
                ladder[count] = l->ladder[x];
                count++;
            }
            else
            {
                memSize++;

                ladder = realloc(ladder, memSize * sizeof(Bar *));
                ladder[count] = l->ladder[x];
                count++;
            }
        }
    }

    free(l->ladder);
    l->numRows = count;
    l->ladder = ladder;
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

    int row = arr[0];
    int col = arr[1];

    //printf("HERE:%d %d\n", arr[0], arr[1]);
    swapVals(&(root->ladder[row - 2][col]->vals[1]), &(root->ladder[row - 1][col + 1]->vals[1]));

    rightSwap(root, root->ladder[arr[0]][arr[1]], arr[0] - 3, arr[1] + 1);

    fixCleanLevel(root, 6);
    removeMultiple(root);
    removeEmptyRows(root);
    resetAllRows(root);
    char *s = root->print(root);
    print(s);
    clear(s);
    //rightSwap(root, root->ladder[6][1], 5, 1);
    //removeMultiple(root);
    //removeEmptyRows(root);
    //rightSwap(root, root->ladder[7][0], 6, 0);
    resetLadder(root);
    swapVals(&(root->ladder[1][3]->vals[1]), &(root->ladder[2][4]->vals[1]));

    rightSwap(root, root->ladder[3][3], 0, 4);
    removeMultiple(root);
    removeEmptyRows(root);
    resetAllRows(root);
    resetLadder(root);
    s = root->print(root);
    print(s);
    clear(s);
}

bool sameBar(Bar b1, Bar b2)
{
    if (b1->vals[0] == b2->vals[0] && (b1->vals[1] == b2->vals[1]))
    {
        return true;
    }
    return false;
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
    forall(root->numCols)
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

    for (int i = 0; i < b->rowIndex; i++)
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

                    if (leftBar->set == true && leftBar->vals[0] != level && leftBar->vals[1] != level)
                        return false;
                    if (midBar->set == true && midBar->vals[0] != level && midBar->vals[1] != level)
                        return false;

                    if (rightBar->set == true && rightBar->vals[0] != level && rightBar->vals[1] != level)
                        return false;
                }
                return true;
            }
        }
    }
    return false;
}

void setActiveBar(Ladder l, int level, int *index)
{
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->set)
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
            /*if(b->vals[1] == val)
            {
                row = b->rowIndex;
                continue;
            }*/
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
            /*if(b->vals[1] == val)
            {
                row = b->rowIndex;
                return row;
            }*/
        }
    }
    return row;
}

void setActiveRegion(Ladder l, int cleanLevel, int min, int max, int *arr)
{
    if (cleanLevel <= min)
    {
        /**Set the arr[0] to the next row > clean level's lowest Row which is the ladder at the max index of that value**/
        arr[0] = findMaxRowOfVal(l, cleanLevel);
        arr[0] = arr[0] + 1;

        arr[1] = l->numRows - 1;
        return;
    }
    else if (cleanLevel > max)
    {
        cleanLevel = max;
        arr[0] = 0;
        arr[1] = findMinRowOfVal(l, cleanLevel);
        arr[1] = arr[1] - 1;
        return;
    }
    else
    {
        /**Set the arr[0] to the next row > clean level's lowest Row which is the ladder at the max index of that value**/
        arr[0] = findMaxRowOfVal(l, cleanLevel);
        arr[0] = arr[0] + 1;

        /**Set the arr[1] to the next row < clean level - 1's highest row which is the ladder at the min index of that value**/
        arr[1] = findMinRowOfVal(l, cleanLevel - 1);
        arr[1] = arr[1] - 1;
    }
}

/**Ladder l is data structure, Bar b is the active bar, active region needs to be calculated before hand.
 * indecies of where to swap will be set in this function*/
void setSwapIndeciesOfActiveBar(Ladder l, Bar b, int *activeRegion, int *indecies)
{
    if (b->colIndex >= l->numCols - 1)
        return;
    rightSwap(l, b, activeRegion[1], b->colIndex + 1);

    /*for(int i = 0; i < l->numRows; i++)
    {
        for(int j = 0; j < l->numCols; j++)
        {
            Bar temp = l->ladder[i][j];
            if(sameBar(b, temp))
            {
                indecies[0] = temp->rowIndex;
                indecies[1] = temp->colIndex;
                break;
            }
        }
    }*/
    removeMultiple(l);
}

void findAllChildren(Ladder l, int *perm, int k, Bar b)
{
    //begin
    //output l
    char *s = l->print(l);
    print(s);
    clear(s);
    for (int i = 0; i < l->numCols + 1; i++)
    {
        if (perm[i] >= k - 1)
        {
            int index[2] = {-1, -1};
            int region[2] = {-1, -1};
            setActiveRegion(l, k, perm[0], perm[3], region);

            findActiveBars(l, perm[i], region[1]);
            int newLevel = perm[i] + 2;
            //findAllChildren(l, perm, newLevel, bars[0]);
        }
    }
    //iterate through bars downward visible from k-2
}

void findActiveBars(Ladder l, int level, int region)
{
    
    int endOfPath = 0;
    char* s = l->print(l);
    print(s);
    clear(s);
    for (int i = 0; i < l->numRows; i++)
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->set == true && b->vals[0] == level)
            {
                endOfPath = b->rowIndex;
            }
        }
    
    
    for (int i = 0; i < l->numRows; i++)
    {
        for (int j = 0; j < l->numCols; j++)
        {
            Bar b = l->ladder[i][j];
            if (b->set && b->rowIndex > endOfPath && b->beenSwapped == false)
            {
                if (isDownWardVisible(l, b, level))
                {
                    printf("Right Swapping bar\n");
                    char* s = print_bar(b);
                    print(s);
                    clear(s);
                    //swapV
                    rightSwap(l, b, region, b->colIndex + 1);
                    b->beenSwapped = true;
                    removeMultiple(l);
                    findActiveBars(l, level, region);
                }
            }
        }
    }
}
