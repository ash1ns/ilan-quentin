# Makefile

CPPFLAGS = `pkg-config --cflags sdl` -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm

SRC = main.c neural_network/neural_network.c neural_network/matrix.c neural_network/file.c img_operations/all_img_op.c img_operations/display.c img_operations/grayscale_binarize.c img_operations/matrix_and_img.c img_operations/pixel_operations.c img_operations/segmentation.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} neural_network/save_weights_bias/xor/*.data
	${RM} neural_network/save_weights_bias/neural_network/*.data
	${RM} main     # remove main program
	${RM} characters


# END
