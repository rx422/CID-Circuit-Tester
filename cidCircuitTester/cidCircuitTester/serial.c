#include "serial.h"

FILE mystdout = FDEV_SETUP_STREAM(uartTransmit, uartReceive, _FDEV_SETUP_RW);

void uartInit(uint16_t ubrrlValue)
{
	stdout = &mystdout;
	stdin = &mystdout;
	UBRRL = ubrrlValue;
	UBRRH = ubrrlValue >> 8;
	UCSRA |= (1 << U2X);
	UCSRB |= (1 << RXEN)|(1<<TXEN);
	UCSRC |= (1<< URSEL)|(1<< UCSZ0)|(1<< UCSZ1);
}

void uartTransmit(unsigned char data, FILE *file)
{
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

unsigned char uartReceive(FILE *file)
{
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}