# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS =
LDLIBS = -lm

SRC = xor.c matrix.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: xor

xor: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} xor     # remove main program


# END
