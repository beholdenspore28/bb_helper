#include "b_arr.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void* array_init(size_t item_size, size_t capacity) {
	void* ptr = NULL;
	size_t size = item_size * capacity + sizeof(arrayHeader_t);
	arrayHeader_t* h = malloc(size);


	if (h) {
		h->capacity = capacity;
		h->length = 0;
		ptr = h + 1;
	}

	return ptr;
}

size_t arrcap(const void* arr) {
	arrayHeader_t* h = (arrayHeader_t*)arr - 1;
	return h->capacity;
}

size_t arrlen(const void* arr) {
	arrayHeader_t* h = (arrayHeader_t*)arr - 1;
	return h->length;
}
