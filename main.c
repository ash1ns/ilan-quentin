#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "neural_network/xor.h"
#include "neural_network/neural_network.h"
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "img_operations/all_img_op.h"

int main(int argc, char *argv[])
{
    if (argc !=  2)
        err(1, "Need one argument");

    //char ask_img_op = "img_op";
    if (strcmp(argv[1],"xor") == 0) 
    {
        srand(time(NULL));
        xor();
    }
    else if(strcmp(argv[1], "nn") == 0)
    {
        srand(time(NULL));
        neural_network();
    }
    else if (strcmp(argv[1], "save") == 0)
    {
        //TODO
    }
    else
    {
        all_img_op(argv);
    }
    return EXIT_SUCCESS;
}
