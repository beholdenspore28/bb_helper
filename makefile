build:
	clang quattest.c b_3d.c b_math.c -g3 -O0 -o prog -lm -Wall -Wextra -Wpedantic -std=c89
	./prog
