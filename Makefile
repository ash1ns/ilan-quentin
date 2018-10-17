main: xor.c matrix.c
	clear && gcc -Wall -Wextra -Werror -std=c99 -o main xor.c matrix.c -lm
