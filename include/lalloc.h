/* This code is free ( free means free, Do whatever useful ;-) )
 *
 *      Author : Viki (a) Vignesh Natarajan
 *      Lab    : vikilabs.org   
 */

#ifndef ALLOC_WRAPPER_H
#define ALLOC_WRAPPER_H 
#include<stdio.h> 

#define LFREE(mem){\
    lfree(mem);\
    mem = NULL;\
}

extern void     lalloc_init();
extern void     lalloc_destroy();
extern void    *lalloc(size_t size);
extern void     lfree(void *mem);
extern size_t   GetDynMemoryUsage();


static size_t  lalloc_size(void *mem);
#endif
