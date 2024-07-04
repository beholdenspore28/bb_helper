#ifndef B_LIST_H
#define B_LIST_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define ui8		uint8_t
#define ui16	uint16_t
#define ui32	uint32_t
#define ui64	uint64_t

#define i8		int8_t
#define i16		int16_t
#define i32		int32_t
#define i64		int64_t

#define DECLARE_LIST(type) \
typedef struct { \
	size_t capacity; \
	size_t length; \
  type * data; \
} list_##type; \
list_##type list_##type##_alloc(void); \
void list_##type##_free(list_##type * list); \
void list_##type##_add(list_##type* l, type value); \
void list_##type##_remove(list_##type* l);

#define DEFINE_LIST(type) \
list_##type list_##type##_alloc(void) { \
	list_##type list; \
	memset(&list, 0, sizeof(list_##type)); \
	list.data = malloc(sizeof(type)); \
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

#define DEFINE_LIST_TYPES 1
#if DEFINE_LIST_TYPES

#define DECLARE_LIST_ALIAS(baseType, targetType) \
typedef list_##baseType list_##targetType; \
list_##targetType list_##targetType##_alloc(void); \
void list_##targetType##_free(list_##targetType* list); \
void list_##targetType##_add(list_##targetType* list, targetType value); \
void list_##targetType##_remove(list_##targetType* list);

#define DEFINE_LIST_ALIAS(baseType, targetType) \
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

DECLARE_LIST_ALIAS(ui8, i8)
DECLARE_LIST_ALIAS(ui16, i16)
DECLARE_LIST_ALIAS(ui32, i32)
DECLARE_LIST_ALIAS(ui64, i64)

#define B_LIST_IMPLEMENTATION \
DEFINE_LIST(void_ptr) \
DEFINE_LIST(const_void_ptr) \
DEFINE_LIST(float) \
DEFINE_LIST(double) \
DEFINE_LIST(long_double) \
 \
DEFINE_LIST(ui8) \
DEFINE_LIST(ui16) \
DEFINE_LIST(ui32) \
DEFINE_LIST(ui64) \
DEFINE_LIST(size_t) \
 \
DEFINE_LIST_ALIAS(ui8, i8) \
DEFINE_LIST_ALIAS(ui16, i16) \
DEFINE_LIST_ALIAS(ui32, i32) \
DEFINE_LIST_ALIAS(ui64, i64) \

#endif /*DEFINE_LIST_TYPES*/

#endif /*B_LIST_H*/
