/*
 * street lights project.c
 *
 * Created: 12-06-2019 03:26:56 PM
 * Author : JAYASURYA
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include<avr/io.h>
#include<util/delay.h>
int main(void)
{
	DDRA|=(1<<PA0);
	DDRB&=~(1<<PB0);
	DDRA|=(1<<PA1);        
	DDRB&=~(1<<PB1);
	while(1)
	{
		if((PINB&(1<<PB0))==0)
		{
			PORTA|=(1<<PA0);
			_delay_ms(220);
			PORTA&=~(1<<PA0);
		}
		else if((PINB&(1<<PB1))==0)
		{
			PORTA|=(1<<PA1);
			_delay_ms(220);
			PORTA&=~(1<<PA1);
		}
		else
		{
			PORTA=0X00;
		}
	}
}