#define F_CPU 16000000
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "UART.h"

void UART_init(uint16_t ubrr)
{
	// set baudrate in UBRR
	UBRR0L = (uint8_t)(ubrr & 0xFF);
	UBRR0H = (uint8_t)(ubrr >> 8);

	// enable the transmitter and receiver
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void UART_puts(char* s)
{
	// transmit character until NULL is reached
	while(*s > 0) UART_putc(*s++);
}

void UART_putc(unsigned char data)
{
	// wait for transmit buffer to be empty
	while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer*/

	// load data into transmit register
	UDR0 = data;
}

unsigned char UART_getc(void)
{
	// wait for data
	while ( !(UCSR0A & (1<<RXC0)) );

	// return data
	return UDR0;
}

void UART_getLine(char* buf, uint8_t n)
{
	uint8_t bufIdx = 0;
	char c;

	// while received character is not carriage return
	// and end of buffer has not been reached
	do
	{
		// receive character
		c = UART_getc();

		// store character in buffer
		buf[bufIdx++] = c;
	}
	while((bufIdx < n) && (c != '\r'));

	// ensure buffer is null terminated
	buf[bufIdx] = 0;
}
