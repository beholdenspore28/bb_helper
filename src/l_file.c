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

------------------------------------------------------------------------------*/

#include "lite.h"

void l_file_close(l_readfile_t file) {
  free(file.text);
}

l_readfile_t l_file_read(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    l_readfile_t ret;
    ret.error = true;
    return ret;
  }
  size_t alloc = L_READFILE_CHUNK_SIZE * L_READFILE_GROWTH;
  char *buf = (char *) malloc(alloc);
  size_t len = 0;
  while (!feof(file)) {
    if (alloc - len >= L_READFILE_CHUNK_SIZE + 1) {
      alloc += L_READFILE_CHUNK_SIZE;
      alloc *= L_READFILE_GROWTH;
      buf = (char *) realloc((void *) buf, alloc);
    }
    int got = fread((void *) &buf[len], 1, L_READFILE_CHUNK_SIZE, file);
    len += got;
    if (got != L_READFILE_CHUNK_SIZE) {
      break;
    }
  }
  buf[len] = '\0';
  fclose(file);
  l_readfile_t ret;
  ret.text = buf;
  ret.len = len;
  ret.error = false;
  return ret;
}