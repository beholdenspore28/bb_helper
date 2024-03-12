#include "b_file.h"

void
FileBuffer_close (FileBuffer file)
{
  free (file.text);
}

FileBuffer
FileBuffer_read (const char *filename)
{
  FILE *file = fopen (filename, "r");
  if (file == NULL)
    {
      FileBuffer ret;
      ret.error = true;
      return ret;
    }
  size_t alloc = B_FILE_BUFFER_CHUNK_SIZE * B_FILE_BUFFER_GROWTH;
  char *buf = (char *)malloc (alloc);
  size_t len = 0;
  while (!feof (file))
    {
      if (alloc - len <= B_FILE_BUFFER_CHUNK_SIZE + 1)
        {
          alloc += B_FILE_BUFFER_CHUNK_SIZE;
          alloc *= B_FILE_BUFFER_GROWTH;
          buf = (char *)realloc ((void *)buf, alloc);
        }
      int got = fread ((void *)&buf[len], 1, B_FILE_BUFFER_CHUNK_SIZE, file);
      len += got;
      if (got != B_FILE_BUFFER_CHUNK_SIZE)
        {
          break;
        }
    }
  buf[len] = '\0';
  fclose (file);
  FileBuffer ret;
  ret.text = buf;
  ret.len = len;
  ret.error = false;
  return ret;
}
