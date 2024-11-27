/*
* cidCircuitTester.c
*
* Created: 3/29/2021 7:54:39 PM
*  Author: Adrian
*/

#define F_CPU	1000000UL

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "serial.h"

#define BYTE_TO_BINARY_PATTERN	"%d%d%d%d"
#define BYTE_TO_BINARY(uint8_t)	\
(uint8_t & 0x01 ? 1 : 0), \
(uint8_t & 0x02 ? 1 : 0), \
(uint8_t & 0x04 ? 1 : 0), \
(uint8_t & 0x08 ? 1 : 0)

#define READ_FUNCTION_PATTERN	" %d \n\r"
#define READ_FUNCTION(uint8_t)	\
(uint8_t & 0x80 ? 1 : 0)

#define BAUD_RATE			9600L
#define UBRRL_VALUE			(uint16_t)(F_CPU/(BAUD_RATE * 16)) * 2

const uint8_t converter[] = {8, 4, 2, 1};

void ports_init(void);
void print_truth_table(void);
void print_one_combination(const uint8_t);
void check_command(const uint8_t);

int main(void)
{
	uartInit(UBRRL_VALUE);
	
	ports_init();
	
	char symbol = false;

	printf("ABCD f\n\r");
	print_truth_table();
	
	while(1)
	{
		symbol = getchar();
		
		if (symbol)
		{
			printf("\n\rABCD f\n\r");
			check_command(symbol);
			symbol = false;
		}
		_delay_ms(100);
	}
}

void ports_init(void)
{	
	DDRC |= (1 << DDRC0) | (1 << DDRC1) | (1 << DDRC2) | (1 << DDRC3);
	PORTC &= ~(1 << PORTC0) | ~(1 << PORTC1) | ~(1 << PORTC2) | ~(1 << PORTC3);
	
	DDRD &= ~(1 << DDRC7);
	PORTD |= (1 << PORTC7);
}

void print_truth_table(void)
{		
	for (uint8_t count = 0; count < 16; count++)
	{
		print_one_combination(count);
	}
}

void print_one_combination(const uint8_t count)
{
	for (int j = 3; j >= 0; j--)
	{
		if (count & converter[j] ? true : false)
		{
			PORTC |= (1 << j);
		}
		else
		{
			PORTC &= ~(1 << j);
		}
	}
	printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PINC));
	printf(READ_FUNCTION_PATTERN, READ_FUNCTION(PIND));
}

void check_command(const uint8_t symbol)
{
	switch(symbol)
	{
		case '0':
			print_one_combination(0x00);
			break;
		case '1':
			print_one_combination(0x01);
			break;
		case '2':
			print_one_combination(0x02);
			break;
		case '3':
			print_one_combination(0x03);
			break;
		case '4':
			print_one_combination(0x04);
			break;
		case '5':
			print_one_combination(0x05);
			break;
		case '6':
			print_one_combination(0x06);
			break;
		case '7':
			print_one_combination(0x07);
			break;
		case '8':
			print_one_combination(0x08);
			break;
		case '9':
			print_one_combination(0x09);
			break;
		case 'A':
			print_one_combination(0x0A);
			break;
		case 'a':
			print_one_combination(0x0A);
			break;
		case 'B':
			print_one_combination(0x0B);
			break;
		case 'b':
			print_one_combination(0x0B);
			break;
		case 'C':
			print_one_combination(0x0C);
			break;
		case 'c':
			print_one_combination(0x0C);
			break;
		case 'D':
			print_one_combination(0x0D);
			break;
		case 'd':
			print_one_combination(0x0D);
			break;
		case 'E':
			print_one_combination(0x0E);
			break;
		case 'e':
			print_one_combination(0x0E);
			break;
		case 'F':
			print_one_combination(0x0F);
			break;
		case 'f':
			print_one_combination(0x0F);
			break;
		default:
			print_truth_table();
	}
}