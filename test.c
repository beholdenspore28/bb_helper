#include "b_arr.h"
#include <stdio.h>
#include <stdlib.h>

/*Test program for b_arr*/

int main () {
	size_t i;
	int* arr;
	arr = array(int);

	printf("cap:%6ld len:%6ld\n", array_cap(arr), array_len(arr));

	for(i = 0; i < array_len(arr); i++) {
		arr[i] = i;
		printf("idx:%6ld v:%6d\n", i, arr[i]);
	}

	free((arrayHeader_t*)arr-1);

	return 0;
}
