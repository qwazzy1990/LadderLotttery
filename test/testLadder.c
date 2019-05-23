#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "LadderLottery.h"
#include "utilities.h"
#include "Numbers.h"

bool DEBUG1 = true;
bool DEBUG2 = false;
bool DEBUG3 = false;
int main(int argc, char *argv[])
{

    Int perm = new_int();
    perm->add(perm, 4);
    perm->add(perm, 6);
    perm->add(perm, 5);
    perm->add(perm, 1);
    perm->add(perm, 3);
    perm->add(perm, 2);
    char *s = perm->print(perm);
    print(s);
    clear(s);
    int p[6] = {4, 6, 5, 1, 3, 2};

    if (DEBUG1)
    {

        Table *t = new_table(5);
        Bar *b1 = new_bar(p[1], p[2], 2, res_row(t, 0, t->numRows));
        t->add(t, b1, b1->height-1, b1->column-1);
        s = t->print(t);
        print(s);
        clear(s);
        Bar *b2 = new_bar(p[1], p[3], 3, res_row(t, 1, t->numRows));
        
        t->add(t, b2, b2->height-1, b2->column-1);
        s = t->print(t);
        print(s);
        clear(s);
        Bar *b3 = new_bar(p[1], p[4], 4, res_row(t, 2, t->numRows));
        
        t->add(t, b3, b3->height-1, b3->column-1);
        s = t->print(t);
        print(s);
        clear(s);
        Bar *b4 = new_bar(p[1], p[5], 5, res_row(t, 3, t->numRows));
        t->add(t, b4, b4->height-1, b4->column-1);
        s = t->print(t);
        print(s);
        clear(s);
        Bar *b5 = new_bar(p[2], p[3], 3, res_row(t, 4, t->numRows));
        t->add(t, b5, b5->height-1, b5->column-1);
        s = t->print(t);
        print(s);
        clear(s);

       
    }
    if (DEBUG2)
    {
        minHeightLadder(p, 6);
    }
    return 0;
}
