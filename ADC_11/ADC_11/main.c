/*
 * ADC_11.c
 *
 * Created: 29-04-2023 09:23:45 AM
 * Author : raj28
 */ 

#include <avr/io.h>
#define F_CPU 16000000L 
#include <util/delay.h>

int main(void)
{
	DDRC |= 0X80;
	ADCSRA &= (1<<ADEN);
	ADMUX = 0X00;
	SFIOR &= (1<<ACME);
	ACSR = 0X00;
	
    /* Replace with your application code */
    while (1) 
    {
		if( ACSR&(1<<ACO) )
		PORTC = 0x80;
		else
		PORTC = 0x00;
    }
}

