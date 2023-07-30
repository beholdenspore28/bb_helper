#include "lite.h"
#ifdef L_ENABLE_FILE

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

#endif
