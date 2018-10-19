#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "xor.h"

int main(int argc, char *argv[])
{
    if (argc !=  2)
        err(1, "Need one argument");
    for (size_t i = 0; i < (size_t)argc; i++)
    {
        printf("Argument %li : %s \n", i+1, argv[i]);
    }

    char ask_xor[] = "xor";
    if (strcmp(argv[1],ask_xor) == 0)
        xor();
    return EXIT_SUCCESS;
}
