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

#include <stdio.h>
#include <stdlib.h>
#include "blib.h"

#define B_FILE_BUFFER_CHUNK_SIZE (64 /* chars */)
#define B_FILE_BUFFER_GROWTH (4 /* times */)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
  size_t len;
  char *text;
  bool error : 1;
} filebuffer_t;

static inline filebuffer_t filebuffer_read(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    filebuffer_t ret;
    ret.error = true;
    return ret;
  }
  size_t alloc = B_FILE_BUFFER_CHUNK_SIZE * B_FILE_BUFFER_GROWTH;
  char *buf = (char *)malloc(alloc);
  size_t len = 0;
  while (!feof(file)) {
    if (alloc - len <= B_FILE_BUFFER_CHUNK_SIZE + 1) {
      alloc += B_FILE_BUFFER_CHUNK_SIZE;
      alloc *= B_FILE_BUFFER_GROWTH;
      buf = (char *)realloc((void *)buf, alloc);
    }
    int got = fread((void *)&buf[len], 1, B_FILE_BUFFER_CHUNK_SIZE, file);
    len += got;
    if (got != B_FILE_BUFFER_CHUNK_SIZE) {
      break;
    }
  }
  buf[len] = '\0';
  fclose(file);
  filebuffer_t ret;
  ret.text = buf;
  ret.len = len;
  ret.error = false;
  return ret;
}

static inline void filebuffer_close(const filebuffer_t file) { free(file.text); }

#ifdef __cplusplus
} //extern "C" {
#endif // __cplusplus
