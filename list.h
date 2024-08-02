/*----------------------------------LEGAL--------------------------------------

MIT License

Copyright (c) 2023 Benjamin Joseph Brooks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-----------------------------------------------------------------------------*/

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "blib.h"

#define DECLARE_LIST(type)                                                     \
  typedef struct {                                                             \
    size_t capacity;                                                           \
    size_t length;                                                             \
    type *data;                                                                \
  } list_##type;                                                               \
  list_##type list_##type##_alloc(void);                                       \
  void list_##type##_free(list_##type *list);                                  \
  void list_##type##_add(list_##type *l, type value);                          \
  void list_##type##_remove(list_##type *l);

#define DEFINE_LIST(type)                                                      \
  list_##type list_##type##_alloc(void) {                                      \
    list_##type list;                                                          \
    memset(&list, 0, sizeof(list_##type));                                     \
    list.data = malloc(sizeof(type));                                          \
    return list;                                                               \
  }                                                                            \
                                                                               \
  void list_##type##_free(list_##type *list) {                                 \
    free(list->data);                                                          \
    memset(list, 0, sizeof(list_##type));                                      \
  }                                                                            \
                                                                               \
  void list_##type##_add(list_##type *l, type value) {                         \
    if (l->length >= l->capacity) {                                            \
      l->capacity = l->length * 2 + 1;                                         \
      l->data = realloc(l->data, sizeof(type) * l->capacity);                  \
    }                                                                          \
    l->data[l->length] = value;                                                \
    l->length++;                                                               \
  }                                                                            \
                                                                               \
  void list_##type##_remove(list_##type *l) { l->length--; }

#define DEFINE_LIST_TYPES 1
#if DEFINE_LIST_TYPES

#define DECLARE_LIST_ALIAS(baseType, targetType)                               \
  typedef list_##baseType list_##targetType;                                   \
  list_##targetType list_##targetType##_Alloc(void);                           \
  void list_##targetType##_free(list_##targetType *list);                      \
  void list_##targetType##_add(list_##targetType *list, targetType value);     \
  void list_##targetType##_remove(list_##targetType *list);

#define DEFINE_LIST_ALIAS(baseType, targetType)                                \
  list_##targetType list_##targetType##_alloc(void) {                          \
    return list_##baseType##_alloc();                                          \
  }                                                                            \
  void list_##targetType##_free(list_##targetType *list) {                     \
    list_##baseType##_free(list);                                              \
  }                                                                            \
  void list_##targetType##_add(list_##targetType *list, targetType value) {    \
    list_##baseType##_add(list, *(targetType *)&value);                        \
  }                                                                            \
  void list_##targetType##_remove(list_##targetType *list) {                   \
    list_##baseType##_remove(list);                                            \
  }

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

#define B_LIST_IMPLEMENTATION                                                  \
  DEFINE_LIST(void_ptr)                                                        \
  DEFINE_LIST(const_void_ptr)                                                  \
  DEFINE_LIST(float)                                                           \
  DEFINE_LIST(double)                                                          \
  DEFINE_LIST(long_double)                                                     \
                                                                               \
  DEFINE_LIST(ui8)                                                             \
  DEFINE_LIST(ui16)                                                            \
  DEFINE_LIST(ui32)                                                            \
  DEFINE_LIST(ui64)                                                            \
  DEFINE_LIST(size_t)                                                          \
                                                                               \
  DEFINE_LIST_ALIAS(ui8, i8)                                                   \
  DEFINE_LIST_ALIAS(ui16, i16)                                                 \
  DEFINE_LIST_ALIAS(ui32, i32)                                                 \
  DEFINE_LIST_ALIAS(ui64, i64)
#endif /*DEFINE_LIST_TYPES*/
