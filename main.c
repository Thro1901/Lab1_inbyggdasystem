#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "serial.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

int main (void) {
	//allocating space for Ledcommand array in memory
	char Ledcommand[15];
	//initialize uart
	uart_init();

	//setting PORTB as output
	DDRB |= (1 << PB0);	
	
	while (1) {
	
		// get line from UART
		uart_getstr(Ledcommand);


		// send line to led_exe
		led_executer(Ledcommand);
	}
	return 0;
}
