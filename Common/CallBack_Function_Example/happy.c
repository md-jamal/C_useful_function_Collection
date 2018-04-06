#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include<stdio.h>
#include "happy.h"

static inline 
void *hello_buffer()
{
    printf("hello\n");
    return NULL;
}

/* API gateway */
const struct HappyClass Happy = {
    .hello = hello_buffer,
};

