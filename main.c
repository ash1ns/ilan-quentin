#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "xor.h"
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc !=  2)
        err(1, "Need one argument");

    char ask_xor[] = "xor";
    if (strcmp(argv[1],ask_xor) == 0) 
    {
        srand(time(NULL));
        xor();
    }
    return EXIT_SUCCESS;
}
