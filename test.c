#ifndef B_LIST_H
#define B_LIST_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define ui8 uint8_t
#define ui16 uint16_t
#define ui32 uint32_t
#define ui64 uint64_t

#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

#define DECLARE_LIST(type) \
typedef struct { \
	size_t capacity; \
	size_t length; \
  type * data; \
} list_##type; \
\
list_##type list_##type##_alloc(void) { \
	list_##type list; \
	memset(&list, 0, sizeof(list_##type)); \
	return list; \
} \
\
void list_##type##_free(list_##type * list) { \
	free(list->data); \
	memset(list, 0, sizeof(list_##type)); \
} \
\
void list_##type##_add(list_##type* l, type value) { \
	l->length++; \
	if (l->length >= l->capacity) { \
		l->capacity = l->length * 2 + 1; \
		l->data = realloc(l->data, sizeof(type) * l->capacity); \
	} \
	l->data[l->length] = value; \
} \
\
void list_##type##_remove(list_##type* l) { \
	l->length--; \
}

#define DECLARE_LIST_TYPES 1
#if DECLARE_LIST_TYPES

typedef void* void_ptr;
typedef const void* const_void_ptr;
typedef const void* long_double;

DECLARE_LIST(void_ptr)
DECLARE_LIST(const_void_ptr)
DECLARE_LIST(float)
DECLARE_LIST(double)
DECLARE_LIST(long_double)

DECLARE_LIST(ui8)
DECLARE_LIST(ui16)
DECLARE_LIST(ui32)
DECLARE_LIST(ui64)
DECLARE_LIST(size_t)

#define DECLARE_LIST_ALIAS(baseType, targetType) \
typedef list_##baseType list_##targetType; \
list_##targetType list_##targetType##_alloc(void) { \
	return list_##baseType##_alloc(); \
} \
void list_##targetType##_free(list_##targetType* list) { \
	list_##baseType##_free(list); \
} \
void list_##targetType##_add(list_##targetType* list, targetType value) { \
	list_##baseType##_add(list,*(targetType*)&value); \
} \
void list_##targetType##_remove(list_##targetType* list) { \
	list_##baseType##_remove(list); \
}

DECLARE_LIST_ALIAS(ui8, i8)
DECLARE_LIST_ALIAS(ui16, i16)
DECLARE_LIST_ALIAS(ui32, i32)
DECLARE_LIST_ALIAS(ui64, i64)

#endif /*DECLARE_LIST_TYPES*/
#endif /*B_LIST_H*/

#include <stdio.h>

int main (void) {
	size_t i;
	list_i32 ints;
	ints = list_i32_alloc();
	
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
