#include <avr/io.h>//Preprocessor for AVR
#define F_CPU 1600000L//Clock frequency
#include <util/delay.h>//Delay function
 
 
#define rs_high PORTA |=(1<<0);//PORT D pin 0 making as high
#define rs_low PORTA &= ~(1<<0);//PORT D pin 0 making as low
 
#define en_high PORTA |= (1<<1);//PORT D pin 1 making as high
#define en_low PORTA &= ~(1<<1);//PORT D pin 0 making as low
 
#define lcdport PORTB//PORTB as LCDport

void lcd_cmd(unsigned char cmd)
{
	lcdport =cmd;
	rs_low;
	en_high;
	_delay_ms(1);
	en_low;
}
 
void lcd_data(unsigned char data)
{
	lcdport =data;
	rs_high;
	en_high;
	_delay_ms(1);
	en_low;
}
 
void lcd_int()
{
	lcd_cmd(0x38);//2 lines 5x7 matrix
	_delay_ms(5);
	//lcd_cmd(0x02);//Return home
	//_delay_ms(5);
	lcd_cmd(0x01);//Clearing screen
	_delay_ms(5);
	lcd_cmd(0x0c);//Display on ,cursor off
	_delay_ms(5);
	lcd_cmd(0x06);//Incrementing cursor
	_delay_ms(5);
	lcd_cmd(0x80);//Force cursor begin 1st line
	_delay_ms(5);
}
 
void cursorpos(char x, char y)
{
	if((x<1 || x>2) || (y<1 || y>16))
	{
		x=1;
		y=1;
	}
	if(x==1)
	{
		lcd_cmd(0x80+y);//Cursor force to start from 1st row
	}
	else
	{
		lcd_cmd(0xc0+y);//Cursor force to start from 2nd row
	}
}
 
void lcd_out(char a, char b, char *str)
{
 
	cursorpos(a,b);
	while(*str)
	{
 
		lcd_data(*str);
		str++;
	}
}
 
 
int main(void)
{
   DDRB = 0xff;//Set the data direction register DDRB as output
   DDRA |=(1<<0);//Set the Data direction Register port d pin 0as output
   DDRA |=(1<<1);//Set the Data direction Register port d pin 1as output
   lcd_int();//Initialize the LCD
   lcd_out(1,1,"skill-lync");
   lcd_out(2,2,"Hellooooooo");
}