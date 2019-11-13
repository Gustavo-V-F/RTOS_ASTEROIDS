#include "_delay.h"

void _delay_us(uint32_t data)
{
	if(configCPU_CLOCK_HZ < MIN_CLOCK)
		return;

	uint32_t delay = (data*(configCPU_CLOCK_HZ/MIN_CLOCK)) << 1;

	_delay_loops(delay);
}

void _delay_ms(uint32_t data)
{
	_delay_us(data*1000);
}	

void _delay_loops(uint32_t data)
{
	uint32_t l = data/CYCLES_PER_LOOP;

	__asm__ __volatile__ ( "0:" "subs %[count], 1;" "bne 0b;" :[count]"+r"(l) );
}

