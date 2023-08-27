#include <avr/io.h>//AVR preprocessor
#define F_CPU 16000000L//CPU frequency
#include <util/delay.h>//Delay preprocessor


void SPI_Master_Init()
{
	
	DDRB = (1<< DDB5) | (1 << DDB3) | (1<< DDB2);
	//SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	SPCR = (1<<6) | (1<<4) | (1<<0);
}

void SPI_Master_Write()
{
	
	PORTB |= (1<<DDB2);
	
	SPDR=0Xf0;//Transferring data
	
	//while((SPSR & (1<<SPIF)) == 0);
	while((SPSR &(1<<7)) == 0);
	
}

int main(void)//main fun
{
	while (1)//continuous operation
	{
		SPI_Master_Init();//caller function
		SPI_Master_Write();//caller function
	}
	return 0;//return value as 0
}