#include "b_arr.h"
#include <stdio.h>
#include <stdlib.h>

/*Test program for b_arr*/

int main () {
	size_t i;
	int* arr;
	arr = array_alloc(int);
	
	printf(" PRE ADD CAP:%6ld LEN:%6ld\n", array_cap(arr), array_len(arr));
	
	for(i = 0; i < 16; i++) {
		array_add(arr);
	}

	printf("POST ADD CAP:%6ld LEN:%6ld\n", array_cap(arr), array_len(arr));
	
	for(i = 0; i < array_len(arr); i++) {
		arr[i] = i;
		printf("idx:%6ld v:%6d\n", i, arr[i]);
	}

	array_free(arr);

	return 0;
}
