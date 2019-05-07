#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "LadderLottery.h"
#include "utilities.h"
#include "Numbers.h"

int main(int argc, char* argv[])
{

    Int perm = new_int();
    perm->add(perm, 4);
    perm->add(perm, 6);
    perm->add(perm, 5);
    perm->add(perm, 1);
    perm->add(perm, 3);
    perm->add(perm, 2);


    create_root_ladder(perm);
    return 0;
}
