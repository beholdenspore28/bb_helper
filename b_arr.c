#include "b_arr.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

void* bhide_array_alloc(size_t item_size, size_t capacity) {
	void* ptr = NULL;
	size_t size = item_size * capacity + sizeof(bhide_arrayHeader_t);
	bhide_arrayHeader_t* h = malloc(size);

	if (h) {
		h->capacity = capacity;
		h->length = 0;
		ptr = h + 1;
	}

	return ptr;
}

void array_free(void* arr) {
	free((bhide_arrayHeader_t*)arr-1);
}

void array_add(void* arr) {
	bhide_arrayHeader_t* h = (bhide_arrayHeader_t*)arr - 1;

	h->length++;
	if (h->length > h->capacity) {
		assert(0);
	}
}

size_t bhide_array_capacity(const void* arr) {
	bhide_arrayHeader_t* h = (bhide_arrayHeader_t*)arr - 1;
	return h->capacity;
}

size_t bhide_array_length(const void* arr) {
	bhide_arrayHeader_t* h = (bhide_arrayHeader_t*)arr - 1;
	return h->length;
}
