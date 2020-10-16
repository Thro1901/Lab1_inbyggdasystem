#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

void main (void) {

	DDRB |= (1 << PB0);

	while (true) {
		PORTB |= (1 << PB0);
		_delay_ms(500);
		PORTB &= ~(1 << PB0);
		_delay_ms(500);

	}
}