#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include "wdt.h"


int main()
{
	cli();			// disable interrupts
	WDT_disable();

	clock_prescale_set(clock_div_1);

	sei();			// enable interrupts
	for(;;);
	return 0;
}
