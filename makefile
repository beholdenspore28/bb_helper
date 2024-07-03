SRC := test.c b_arr.c
CFLAGS := -Wall -Wextra -Werror -pedantic -O0 -g3 -std=c89
OUT := deleteme
CC := gcc

build:
	${CC} ${SRC} ${INC} ${CFLAGS} -o ${OUT}
	./${OUT}
