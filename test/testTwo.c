#include "utilities.h"
#include "DynamicString.h"
#include "StringArray.h"
#include "Numbers.h"
#include "LL2.0.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool DEBUG1 = false;
bool DEBUG2 = true;
bool DEBUG3 = false;
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
    if(DEBUG2)
    {
        Ladder l = new_ladder(3);
        generate_test_root(l, perm, 4);
        Bar b  = l->ladder[10][1];
        bool vis = isDownWardVisible(l, b, 4);
        printf("is vis = %d\n", vis);

        int index[2] = {0, 0};
        setActiveBar(l, 4, index);
        int row = index[0];
        int col = index[1];
        char* s = print_bar(l->ladder[row][col]);
        print(s);
        clear(s);
    }
    //run(perm, 6);

    return 0;
}