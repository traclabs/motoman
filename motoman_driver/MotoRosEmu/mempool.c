
#include <mprtl/mempool.h>

#include <stdlib.h> // malloc, free


// Memory Pool Control API /////////////////////////////////////////////////////

void *mpMalloc(size_t size)
{
  return malloc(size);
}


void mpFree(void *ptr)
{
  free(ptr);
}

