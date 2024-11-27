#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdio.h>
#include <avr/io.h>

void uartInit(uint16_t ubrr);
void uartTransmit(unsigned char data, FILE *file);
unsigned char uartReceive(FILE *file);

#endif /*SERIAL_H_*/