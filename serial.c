#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

#define FOSC 16000000
#define BAUD 38400
#define MYUBRR FOSC/(16*BAUD)+1
//260

void uart_init(void) {

	/*Set baud rate */
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	/*Enable receiverand transmitter*/
		UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);

}

void uart_putchar(char chr) {

	 /* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = chr;

	
	/* Send "\n" Character */
	while (!(UCSR0A & (1 << UDRE0)));   /* Wait for empty transmit buffer       */
	UDR0 = '\n';					    /* Put data into buffer, sends the data */

   /* Send "\r" Character */
	while (!(UCSR0A & (1 << UDRE0)));   /* Wait for empty transmit buffer       */
	UDR0 = '\r';

}
