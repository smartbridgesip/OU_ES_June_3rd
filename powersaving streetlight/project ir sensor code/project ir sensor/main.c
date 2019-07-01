/*
 * project ir sensor.c
 *
 * Created: 20-06-2019 10:32:40
 * Author : Mohit
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define RS 7
#define E 5

#include <avr/io.h>
#include <util/delay.h>

void sco(unsigned char a);
void sch(unsigned char b);


int main(void)
{
	
	DDRC=0XFF;
	DDRD=0XFF;
	_delay_ms(50);
	DDRA|=(1<<PA0);
	DDRB&=~(1<<PB0);
	sco(0X01);
	sco(0X38);
	sco(0X0E);
	
	while(1)
	{
		
		if((PINB&(1<<PB0))==0)
		{
			
			PORTA=0XFF;
			sch(0X4F);
			sch(0X4E);
			_delay_ms(500);
		}
		else
		{
			PORTA=0X00;
			sco(0X01);
			sco(0X38);
			sco(0X0E);
			
			
			sch(0X4F);
			sch(0X46);
			sch(0X46);
			_delay_ms(500);
		}
	}
	
}

void sco(unsigned char a)
{
	PORTC=a;
	PORTD&=~(1<<RS);
	PORTD|=(1<<E);
	_delay_ms(500);
	PORTD&=~(1<<E);
	PORTC=0;
}
void sch(unsigned char b)
{
	PORTC=b;
	PORTD|=(1<<RS);
	PORTD|=(1<<E);
	_delay_ms(500);
	PORTD&=~(1<<E);
	PORTC=0;
}
