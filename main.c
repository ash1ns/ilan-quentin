#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "xor.h"
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "img_operations/all_img_op.h"

int main(int argc, char *argv[])
{
    if (argc !=  2)
        err(1, "Need one argument");

    char ask_xor[] = "xor";
    //char ask_img_op = "img_op";
    if (strcmp(argv[1],ask_xor) == 0) 
    {
        srand(time(NULL));
        xor();
    }
    else
    {
        all_img_op(argv);
    }
    return EXIT_SUCCESS;
}
