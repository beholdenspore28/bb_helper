SRC := test.c newtest.c
OPT_DEBUG := -g3
OPT_SMALL := -Oz -flto
OPT_RELEASE := -flto -O3 
OPT_ := ${OPT_DEBUG} 
OPT := ${OPT_${MODE}}
CFLAGS += ${OPT} -Wall -Wextra -Werror -pedantic -std=c89

OUT := deleteme
CC := gcc

build:
	${CC} ${SRC} ${INC} ${CFLAGS} -o ${OUT}
	./${OUT}
