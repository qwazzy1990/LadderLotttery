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
bool DEBUG3 = true;
bool DEBUG4 = false;
bool DEBUG5 = false;

int main(int argc, char *argv[])
{
    int perm[4] = {4, 3, 2, 1};

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
    if (DEBUG3)
    {
        Ladder l = new_ladder(3);
        generate_test_root(l, perm, 4);
        //Bar b = new_bar(2, 1);
        //l->add(l, b, 6, 0);

        //printf("%d\n", getCleanLevel(perm, l));

        int ar[2] = {0, 0};
        setActiveRegion(l, getCleanLevel(perm, l), 1, 4, ar);
        getFirstTurnBarIndex(l, perm, ar);
        Bar b = l->ladder[ar[0]][ar[1]];
        setActiveRegion(l, 5, 1, 4, ar);
        //printf("Active region is %d %d\n", ar[0], ar[1]);
        int indecies[2] = {-1, -1};
        setSwapIndeciesOfActiveBar(l, b, ar, indecies);
        b = l->ladder[10][1];
        setSwapIndeciesOfActiveBar(l, b, ar, indecies);
        b = l->ladder[14][0];
        setSwapIndeciesOfActiveBar(l, b, ar, indecies);
        b = l->ladder[2][1];
        setSwapIndeciesOfActiveBar(l, b, ar, indecies);

    }
    //run(perm, 6);
    if(DEBUG4)
    {
        Ladder l = new_ladder(3);
        generate_test_root(l, perm, 4);
        Ladder clone  = clone_ladder(l);
        char* s = clone->print(clone);
        print(s);
        clear(s);
    }

    return 0;
}