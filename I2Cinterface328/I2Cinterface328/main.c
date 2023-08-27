#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000
#define F_SCL 100000

void I2C_Start()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}

void I2C_Stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}


void I2C_Write(unsigned char data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 1);
}

void I2C_Init()
{
	TWSR = 0x02 ;
	TWBR = ((F_CPU/(F_SCL * 2)) - 8)/4;
}



int main(void)
{
	I2C_Init();
	I2C_Start();
	I2C_Write(0b10010111);
	_delay_ms(5);
	I2C_Write(0b10010100);
	_delay_ms(5);
	I2C_Write(0b10010101);
	_delay_ms(5);
	I2C_Stop;
	while(1);

	return 0;

}
