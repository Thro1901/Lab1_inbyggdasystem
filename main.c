#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

int main (void) {
	
	unsigned char data[] = "Hello from Thomas  ";
	uart_init();
	char sign = 'T';

	DDRB |= (1 << PB0);

	while (true) {
		PORTB |= (1 << PB0);
		_delay_ms(500);
		PORTB &= ~(1 << PB0);
		_delay_ms(500);
		uart_putchar(sign);
		uart_putstr(data);
	}
	return 0;
}
