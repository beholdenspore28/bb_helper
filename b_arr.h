#ifndef B_ARR_H
#define B_ARR_H

#include <stddef.h>

#define ARRAY_INITIAL_CAPACITY 16
#define array(T) (T*)array_init(sizeof(T),ARRAY_INITIAL_CAPACITY)
#define array_cap(arr) arrcap((void*)arr)
#define array_len(arr) arrlen((void*)arr)

typedef struct {
	size_t capacity;
	size_t length;
} arrayHeader_t;

void* array_init(size_t item_size, size_t capacity);
size_t arrcap(const void* arr);
size_t arrlen(const void* arr);

#endif
