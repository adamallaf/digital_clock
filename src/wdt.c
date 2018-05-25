#include "wdt.h"


inline void WDT_disable(){
	MCUSR &= ~(1 << WDRF);
	WDTCSR |= ((1 << WDCE) | (1 << WDE));			// change enable
	WDTCSR = 0x00;
}

inline void WDT_enable(){
	WDTCSR |= ((1 << WDCE) | (1 << WDE));			// change enable
	WDTCSR = (1 << WDIE) | (1 << WDP1) | (1 << WDP2);	// int enabled & 1s timeout
}
