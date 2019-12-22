/* This code is free ( free means free, Do whatever useful )
 *
 *      Author : Viki (a) Vignesh Natarajan
 *      Lab    : vikilabs.org   
 */

#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <assert.h>

#define TEST_PASS(str){\
    printf("[ success ] (%s : %d ) | %s\n", __func__, __LINE__, str);\
}

#define TEST_FAIL(str){\
    printf("[ failure ] (%s : %d ) | %s\n", __func__, __LINE__, str);\
    assert(0);\
}

#endif

