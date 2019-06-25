#include "utilities.h"
#include "DynamicString.h"
#include "StringArray.h"
#include "Numbers.h"
#include "LL2.0.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
bool DEBUG1 = false;
bool DEBUG2 = false;
bool DEBUG3 = false;
bool DEBUG4 = false;
bool DEBUG5 = false;
bool DEBUG6 = false;
bool DEBUG7 = true;

int main(int argc, char *argv[])
{
    int perm[6] = {5, 6, 3, 4, 2, 1};
    Ladder l = new_ladder(5);
    generate_test_root(l, perm, 6);
    char *s = NULL;
    if (DEBUG1)
    {
        int perm[4] = {4, 3, 2, 1};

        Ladder l = new_ladder(3);

        generate_test_root(l, perm, 4);
        char *s = l->print(l);

        print(s);
        clear(s);
    }
    if (DEBUG2)
    {
        Ladder l = new_ladder(3);
        generate_test_root(l, perm, 4);
        Bar b = l->ladder[10][1];
        bool vis = isDownWardVisible(l, b, 4);
        printf("is vis = %d\n", vis);

        int index[2] = {0, 0};
        setActiveBar(l, 4, index);
        int row = index[0];
        int col = index[1];
        char *s = print_bar(l->ladder[row][col]);
        print(s);
        clear(s);
    }
    //run(perm, 6);
    if (DEBUG4)
    {
        int arr[2] = {-1, -1};

        s = printLadderTwo(l);
        print(s);
        clear(s);
        getFirstTurnBarIndex(l, perm, arr);

        int size = sizeof(perm) / sizeof(perm[0]);
        printf("SIZE IS %d\n", size);
        Bar turnBar = getBar(l, arr[0], arr[1]);
        s = print_bar(turnBar);
        printf("Before: %s\n", s);
        setActiveRegion(l, turnBar, 5, 1, 6, arr);
        rightSwap(l, turnBar, arr[0], turnBar->colIndex + 1);
        s = print_bar(turnBar);
        printf("After: %s\n", s);

        findAllChildren(l, perm, turnBar, turnBar->vals[0] + 1, size);
    }

    if (DEBUG5)
    {
        Ladder l = new_ladder(3);
        generate_test_root(l, perm, 4);
        int arr[2] = {-1, -1};

        getFirstTurnBarIndex(l, perm, arr);
        Bar turnBar = l->ladder[arr[0]][arr[1]];
        int ar[1] = {-1};
        char *s = l->print(l);
        print(s);
        clear(s);

        //setActiveRegion(l, 4, 1, 4, ar);

        int rowIndex = turnBar->rowIndex;
        int colIndex = turnBar->colIndex;
        rightSwap(l, turnBar, ar[0], turnBar->colIndex + 1);
        printf("Active region is %d\n", ar[0]);
        s = l->print(l);
        print(s);
        clear(s);
        Bar leftBar = l->ladder[ar[0]][colIndex + 1];
        leftSwap(l, leftBar, rowIndex, colIndex);
        s = l->print(l);
        print(s);
        clear(s);
    }

    if (DEBUG6)
    {
        int arr[2] = {-1, -1};

        getFirstTurnBarIndex(l, perm, arr);

        char *s = l->print(l);
        print(s);
        clear(s);

        //setActiveRegion(l, 4, 1, 4, ar);

        l->ladder[0][1]->vals[0] = 2;
        l->ladder[0][1]->vals[1] = 7;
        l->ladder[0][1]->set = true;

        Bar testBar = l->ladder[0][1];

        rightSwap(l, testBar, -1, testBar->colIndex + 1);
        s = l->print(l);
        print(s);
        clear(s);
    }

    if (DEBUG7)
    {
       runProg(perm, 6);
    }

    return 0;
}