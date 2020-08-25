/*
 * LCD.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Kamal
 */
#include<avr/io.h>
#include<util/delay.h>

#define LCD_DATA PORTB
#define ctrl   PORTA
#define  rs PA3
#define rw PA4
#define en PA5
#define t 1

void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_arabic(unsigned char *pattern,const char location);

int main()
{

	DDRB=0b11111111;
	DDRA=0b00111000;
	init_LCD();
	_delay_ms(t);

	unsigned char Pattern1 [ ] = {0xf, 0xf, 0xc, 0xc, 0x1c, 0x1c, 0x0, 0x0} ;
	unsigned char Pattern2 [ ] = { 0x0, 0x0, 0x0, 0xe, 0x1b, 0x1f, 0x0, 0x0} ;
	unsigned char Pattern3 [ ] = { 0xc, 0xc, 0xc, 0xc, 0xf, 0xf, 0x0, 0x0} ;
	unsigned char Pattern4 [ ] = { 0x3, 0x3, 0x3, 0x3, 0x13, 0x1f, 0x1f, 0x0 } ;
    unsigned char Pattern5 [ ]= {0xe, 0xe, 0x5, 0x1f, 0x14, 0xe, 0xa, 0x0};
    unsigned char Pattern6 [ ]= {0xe, 0xe, 0x14, 0x1f, 0x5, 0xe, 0xa, 0x0};



LCD_arabic(Pattern1,1);
LCD_cmd(0x89);
LCD_write(1);
_delay_ms(100);
LCD_arabic(Pattern2,2);
LCD_cmd(0x88);
LCD_write(2);
_delay_ms(100);
LCD_arabic(Pattern3,3);
LCD_cmd(0x87);
LCD_write(3);
_delay_ms(100);
LCD_arabic(Pattern4,4);
LCD_cmd(0x86);
LCD_write(4);
_delay_ms(100);

LCD_arabic(Pattern5,5);
LCD_cmd(0xC0);
LCD_write(5);
_delay_ms(100);
LCD_arabic(Pattern6,6);
	LCD_cmd(0xC0);
	LCD_write(6);
	_delay_ms(100);

while(1)
{

	 for(int i=0;i<16;i++)
	 {
		 LCD_cmd(0x1);

		 LCD_cmd(0x89);
		 LCD_write(1);

		 LCD_cmd(0x88);
		 LCD_write(2);

		 LCD_cmd(0x87);
		 LCD_write(3);

		 LCD_cmd(0x86);
		 LCD_write(4);

		 LCD_cmd((0xC1+i));
	 LCD_write(5);
	 LCD_cmd((0xC1+i));

		 LCD_write(6);
		 _delay_ms(100);
}



/*0
	 for(int i=0;i<40;i++)
	 {
		 LCD_cmd((0xC0+i));
	 _delay_ms(100);
}
*/
}



	return 0;

}

void LCD_arabic(unsigned char *pattern,const char location)
{
	int i=0;
	LCD_cmd(0x40 + (location*8));
	for(i=0;i<7;i++)
	{
		LCD_write(pattern[i]);
	}
}


void init_LCD(void)
{
	LCD_cmd(0x38);
	_delay_ms(t);
	LCD_cmd(0x01);
	_delay_ms(t);
	LCD_cmd(0x02);
	_delay_ms(t);
	LCD_cmd(0x06);
	_delay_ms(t);
	LCD_cmd(0x80);
	_delay_ms(t);
	LCD_cmd(0x0C);
}


void LCD_cmd(unsigned char cmd)
{
	LCD_DATA=cmd;
	PORTA &=~(1<<rs);
	PORTA &=~(1<<rw);
	PORTA|=(1<<en);
	_delay_ms(t);
	PORTA &=~(1<<en);

}

void LCD_write(unsigned char data)
{
	LCD_DATA=data;
	PORTA|=(1<<rs);
	PORTA &=~(1<<rw);
	PORTA |=(1<<en);
		_delay_ms(t);
		PORTA &=~(1<<en);

}






