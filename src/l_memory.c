#include "lite.h"

#ifdef L_ENABLE_DEBUG_MEMORY

/*
Memory TODO
-track all memory manipulations
 -store useful info in a structure 
 		-track calls to malloc
 		  -if successfully allocated, store 
 			 the size and address of the allocated memory
 		-track calls to free
 		-track calls to realloc
 		-track calls to calloc
 print a memory report at the end of the program
 */
/*
void *l_debug_malloc(size_t size){ 
  void *p = malloc(size);
  if (p == NULL) {
    printf("[L_MEM_DEBUG] malloc() failed to allocate %ld bytes. Out of memory\n",size);
    exit(1);
  } 
  printf("[MALLOC] allocating %ld bytes to address %p\n", size, p);
  return p;
}
*/

#endif
