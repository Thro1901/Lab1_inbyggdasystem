#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

#define FOSC 16000000 // 16MHz system clock
#define BAUD 38400 // BAUD i want
#define MYUBRR ((FOSC / 16) / BAUD) -1 // Calculate my baud rate
//260
void blink_led(void){

	while (!(UCSR0A & (1 << RXC0))) {  /* Wait for empty transmit buffer       */

		PORTB |= (1 << PB0); //put bit PB0 to HIGH
		_delay_ms(500);   
		PORTB &= ~(1 << PB0); //put bit PB0 to LOW
		_delay_ms(500);
	}
}

void uart_init(void) {

	/*Set baud rate */
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	/*Enable receiverand transmitter*/
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (1 << UCSZ01) | (3 << UCSZ00);
}

void uart_putchar(char chr) {

	if (chr == '\r') { 
		/* Send "\r" Character */
		while (!(UCSR0A & (1 << UDRE0)));   /* Wait for empty transmit buffer       */
		UDR0 = '\r';					    /* Put data into buffer, sends the data */

	   /* Send "\n" Character */
		while (!(UCSR0A & (1 << UDRE0)));   /* Wait for empty transmit buffer       */
		UDR0 = '\n';
	}
	else {
		
		while (!(UCSR0A & (1 << UDRE0)));   /* Wait for empty transmit buffer       */
		UDR0 = chr;
	} 
}

void uart_putstr(const char* str) {

	int i = 0;
	while (str[i] != 0) /* while str is not at the end  */
	{    /* Wait for empty transmit buffer*/
		while (!(UCSR0A & (1 << UDRE0)))
			; 
		UDR0 = str[i];            /* Put data into buffer, sends the data */
		i++;                            
	}
}

char uart_getchar(void) {

	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)))
		;

	/* Get and return received data from buffer */
	return UDR0;
}

void uart_echo(void) {

	//receive char from uart and put it on uart
	uart_putchar(uart_getchar());
}

void uart_getstr(char* str) {

	uint8_t i = 0;
	char c;

	do
	{
		// receive char from uart
		c = uart_getchar();
		// store character in buffer
		str[i++] = c;
	} while ((i < 15) && (c != '\n')); //exit loop when c == '\n', saves the '/r' and '\n' before exit. 
	str[i] = 0; // null-terminate to make it work with strcmp	
}
void led_executer(char* command) {


	uart_putstr(command);
	uart_putchar('\n');
	//check if command contains "on\r\n"
	if (strncasecmp(command, "on\r\n") == 0) {
		PORTB |= (1 << PB0);    // led on
	}
	else if (strncasecmp(command, "off\r\n") == 0) {
		PORTB &= ~(1 << PB0); // led off
	}
	else if (strncasecmp(command, "blink\r\n") == 0) {
		blink_led();  // led blink
	}
	else {
		uart_putstr("Wrong command, try again...");
		uart_putchar('\r');
	}
}

