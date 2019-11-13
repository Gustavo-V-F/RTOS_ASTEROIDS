#include "_rand.h"

static uint32_t next = 1;

uint32_t ulRand(void)  /* RAND_MAX assumed to be 32767. */
{
    next = next * 1103515245 + 12345;
    return((uint32_t)(next/65536) % 32768);
}


void vSrand(unsigned int seed)
{
    next = seed;
}
