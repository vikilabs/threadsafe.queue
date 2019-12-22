/* This code is free ( free means free, Do whatever useful  ;-) )
 *
 *      Author : Viki (a) Vignesh Natarajan
 *      Lab    : vikilabs.org   
 */

#include <stdlib.h>
#include <pthread.h>
static pthread_mutex_t alloc_lock;
#include "lalloc.h"
static size_t dynamic_memory_usage;

void lalloc_init()
{
    pthread_mutex_init(&alloc_lock, NULL);
}

void lalloc_destroy()
{
    pthread_mutex_destroy(&alloc_lock);
}

void lfree(void *mem)
{

    /*
    <- This memory stores its size ->     <-- This memory area stores the data --->
     (mem - 1)                              mem (points to [1])
        |                                     |
        v                                     v
       [0]                                   [1] [2] [3] .............  [ size ] 
    */

    if(!mem)
        return;

    pthread_mutex_lock(&alloc_lock);
    dynamic_memory_usage -= lalloc_size(mem);
    free((size_t *) mem - 1);
    pthread_mutex_unlock(&alloc_lock);
}

void *lalloc(size_t size)
{
    pthread_mutex_lock(&alloc_lock);
    size_t *mem = calloc(1, sizeof(size_t) + size);

    if(!mem){
        pthread_mutex_unlock(&alloc_lock);
        return NULL;
    }

    /*

       <- This memory stores its size ->     <-- This memory area stores the data --->
       [0]                                   [1] [2] [3] .............  [ size ] 

     */

    mem[0] = size;  /* store the size in the first address*/

    dynamic_memory_usage += mem[0];
    pthread_mutex_unlock(&alloc_lock);
    return &mem[1]; /* return the second address to store data*/
}

static size_t lalloc_size(void *mem)
{
    /*
    <- This memory stores its size ->     <-- This memory area stores the data --->
     ((size_t *)mem)[-1]                    mem (points to [1])
        |                                     |
        v                                     v
       [0]                                   [1] [2] [3] .............  [ size ] 
    */

    return ((size_t *)mem)[-1];
}

size_t GetDynMemoryUsage()
{
    size_t mem;
    pthread_mutex_lock(&alloc_lock);
    mem = dynamic_memory_usage;
    pthread_mutex_unlock(&alloc_lock);
    return mem;
}
