#include "utilities.h"
#include "DynamicString.h"
#include "StringArray.h"
#include "Numbers.h"
#include "LL2.0.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    int perm[6] = {5, 6, 3, 4, 2, 1};

    run(perm, 6);

    return 0;
}