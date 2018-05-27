#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>
#include "wdt.h"


int main()
{
    unsigned char data = 0xaa;
	cli();			// disable interrupts
	WDT_disable();

	clock_prescale_set(clock_div_1);

	TWCR = (1 << TWEN);// | (1 << TWIE);
    TWSR |= 0x00;
    TWBR = 0x20;
    TWAR = 0;

	DDRB |= (1 << PB5);
    PORTC |= (1 << PC5) | (1 << PC4);

	sei();			// enable interrupts
	for(;;)
	{
        PORTB |= (1 << PB5);
        data = ~data;
        PORTB &= ~(1 << PB5);
        TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);
        while(!(TWCR & (1 << TWINT)));
        TWDR = (0x20 << 1);
        TWCR = (1 << TWINT) | (1 << TWEN);
        while(!(TWCR & (1 << TWINT)));
        TWDR = data;
        TWCR = (1 << TWINT) | (1 << TWEN);
        while(!(TWCR & (1 << TWINT)));
        TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
        _delay_ms(1000);
    }
    return 0;
}
