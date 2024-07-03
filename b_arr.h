#ifndef B_ARR_H
#define B_ARR_H

#include <stddef.h>

#define ARRAY_INITIAL_CAPACITY 16
#define array_alloc(T) (T*)bhide_array_alloc(sizeof(T),ARRAY_INITIAL_CAPACITY)
#define array_cap(arr) bhide_array_capacity((void*)arr)
#define array_len(arr) bhide_array_length((void*)arr)

typedef struct {
	size_t capacity;
	size_t length;
} bhide_arrayHeader_t;

void array_free(void* arr);
void array_add(void* arr);

void* bhide_array_alloc(size_t item_size, size_t capacity);
size_t bhide_array_capacity(const void* arr);
size_t bhide_array_length(const void* arr);

#endif
