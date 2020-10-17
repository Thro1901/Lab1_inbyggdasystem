#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

int main (void) {
	//int i = 0;
	//unsigned char data[] = "Hello from ATmega328p  ";
	uart_init();
	char sign = 'T';

	DDRB |= (1 << PB0);

	while (true) {
		PORTB |= (1 << PB0);
		_delay_ms(500);
		PORTB &= ~(1 << PB0);
		_delay_ms(500);
		uart_putchar(sign);
	}
	return 0;
}
