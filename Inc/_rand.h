#ifndef _RAND_H
#define _RAND_H

#include <stdint.h>

uint32_t ulRand(void);  /* RAND_MAX assumed to be 32767. */
void vSrand(unsigned int seed);

#endif