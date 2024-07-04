#include "b_list.h"
#include <stdio.h>

int main (void) {
	size_t i;
	list_i32 ints;
	ints = list_i32_alloc();
	ints.data[0] = 420;
	
	printf("-----------------------------------\n");
	for(i = 0; i < 32; i++) {
		list_i32_add(&ints, i);
		printf("ADD IDX: %6ld VAL: %6d\n", i, ints.data[i]);
	}

	printf("-----------------------------------\n");
	for(i = 0; i < 8; i++) {
		printf("REM IDX: %6ld VAL: %6d\n", ints.length, ints.data[ints.length]);
		list_i32_remove(&ints);
	}

	printf("----------------------------------\n");
	for(i = 0; i < ints.length; i++) {
		printf("RES IDX: %6ld VAL: %6d\n", i, ints.data[i]);
	}

	list_i32_free(&ints);
	return 0;
}
