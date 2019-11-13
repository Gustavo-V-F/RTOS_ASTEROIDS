#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>
#include "FreeRTOSConfig.h"

#define MIN_CLOCK 3000000
#define CYCLES_PER_LOOP 2

void _delay_us(uint32_t data);	
void _delay_ms(uint32_t data);	
void _delay_loops(uint32_t data);

#endif /* _DELAY_H_ */
