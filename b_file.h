#if (!defined(B_FILE_H))
#define B_FILE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
  size_t len;
  char *text;
  bool error : 1;
} FileBuffer;

#if !defined(B_FILE_BUFFER_CHUNK_SIZE)
/*Number of chars before buffer must be expanded*/
#define B_FILE_BUFFER_CHUNK_SIZE (64 /* chars */)
#endif

#if !defined(B_FILE_BUFFER_GROWTH)
#define B_FILE_BUFFER_GROWTH                                                  \
  (4 /* times */) /*Scalar to multiply chunk size when expanding*/
#endif

void FileBuffer_close (FileBuffer file);
FileBuffer FileBuffer_read (const char *filename);

#endif /*B_FILE_H*/
