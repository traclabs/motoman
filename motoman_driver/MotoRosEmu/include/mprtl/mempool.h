#ifndef FAKE_MOTOPLUS_MEMPOOL_H__
#define FAKE_MOTOPLUS_MEMPOOL_H__


#include <stdlib.h> // size_t


// Memory Pool Control API /////////////////////////////////////////////////////

void* mpMalloc(size_t size);
void  mpFree(void *ptr);


#endif // FAKE_MOTOPLUS_MEMPOOL_H__
