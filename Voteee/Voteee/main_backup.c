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
void lcd_cout(char a, char b, char *str)
{
	lcd_cmd(0x01);//clearingscren
	cursorpos(a,b);
	while(*str)
	{
		
		lcd_data(*str);
		str++;
	}
}


int main(void)
{
	
	//Sensors Setup
	uint8_t GPCSR = 0X00;
	// -X     -Warned Voted  -Voted -X   -Person In
	// 7654   3              2      1    0
	DDRD = 0b11111100;
	DDRC = 0x00;
	
	DDRB = 0xff;//Set the data direction register DDRB as output
	DDRA |=(1<<0);//Set the Data direction Register port d pin 0as output
	DDRA |=(1<<1);//Set the Data direction Register port d pin 1as output
	lcd_int();//Initialize the LCD
	lcd_cout(1,1,"EVM Ready!");
	
	while(1){
		
		if(PIND & 0X01){
			lcd_cout(1,1,"Press Button");
			lcd_out(2,2,"to Record Vote");
			_delay_ms(200);
			GPCSR|=0X01;
		}
		if(PIND & 0X02){
			lcd_cout(1,1,"Vote Recorded");
			_delay_ms(200);
			lcd_out(1,1,"Electronic Vote");
			lcd_out(2,2,"Machine");
			GPCSR=0X00;
		}
		if(GPCSR & 0x01 ){   //If entered take vote
			if( (GPCSR & 0X04) && !(GPCSR & 0X08) ){ //Already Voted
				lcd_cout(1,1,"Voted Recorded!!");
				lcd_out(2,2,"Please Quit!!");
				GPCSR|=0x08;
			}
			else if( (PINC &0x01) && !(GPCSR & (1<<2)) ){
				lcd_cout(1,1,"Voted : A Party");
				_delay_ms(400);
				GPCSR|= (1<<2);
			}
			else if( (PINC &0x02) && !(GPCSR & (1<<2)) ){
				lcd_cout(1,1,"Voted : B Party");
				_delay_ms(400);
				GPCSR|= (1<<2);
			}
			else if( (PINC &0x04) && !(GPCSR & (1<<2)) ){
				lcd_cout(1,1,"Voted : C Party");
				_delay_ms(400);
				GPCSR|= (1<<2);
			}
			else if( (PINC &0x08) && !(GPCSR & (1<<2)) ){
				lcd_cout(1,1,"Voted : D Party");
				_delay_ms(400);
				GPCSR|= (1<<2);
			}
		}
		
		
	}	
}
