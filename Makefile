# Makefile

CPPFLAGS = `pkg-config --cflags sdl` -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm

SRC = main.c xor/xor.c xor/matrix.c xor/file.c img_operations/all_img_op.c img_operations/display.c img_operations/grayscale_binarize.c img_operations/matrix_and_img.c img_operations/pixel_operations.c img_operations/segmentation.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} xor/save_weights_bias/*.data
	${RM} main     # remove main program
	${RM} characters


# END
