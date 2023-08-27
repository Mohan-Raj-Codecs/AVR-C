#define F_CPU 160000000
#define FOSC 1843200
#define Baudrate 9600
#define UBRR ((FOSC/(16*Baudrate)) - 1)
#include <avr/io.h>
#include <util/delay.h>

void Uart_Init();

int main(void)
{
	int data;//decaring the varaible data
	Uart_Init();
	
	while (1)//infinite time it will be executing
	{
		data = uart_read();
		uart_write(data);
	}
	return 0;
}

void Uart_Init()
{
	//Set the baud rate
	UBRRH = UBRR >> 8;
	UBRRL = UBRR;
	//Enable transmission and Receive
	UCSRB = (1 << TXEN) | (1<<RXEN);
	//Setup the uart frame for 8 bit data
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

void uart_write(char a)
{
	UDR = a;
	_delay_ms(500);
	
}

void uart_read()
{
	return UDR;
}