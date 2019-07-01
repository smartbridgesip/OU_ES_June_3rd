/*
 * water_project.c
 *
 * Created: 6/20/2019 7:23:18 PM
 * Author : lenovo
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <avr/io.h>

#define enable 5
#define registerselection 7

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);

void LCD();
void dcmotor();

int main(void)
{
   PORTB = 0x00; //input port
   DDRB = 0x01; // Portb.0 = output
   DDRA = 0xFF;
   DDRC=0XFF;
   DDRD=0XFF;

   while (1)
   {
	   if((PINB & 0x02) != 0)    // read PINB.1
	   {
		   PORTB |= 0b00000001;   // set PORTB.0
		   LCD();
		   dcmotor();
	   }
	   else
	   {
		   PORTB &= 0b11111110;   // clear PORTB.0
		   send_a_command(0x01);//all clear command
		   send_a_command(0x38);//16*2 line LCD
		   send_a_command(0x0E);//screen and cursor on
		   send_a_string("CLEAR PATH");
       }
   }
}


void LCD()
{
	send_a_command(0x01);//all clear command
	send_a_command(0x38);//16*2 line LCD
	send_a_command(0x0E);//screen and cursor on
	send_a_string("OBJECT DETECTED");
}

void dcmotor()
{
	PORTA=0x01;
	_delay_ms(4000);
	
	PORTA=0x00;
	_delay_ms(4000);
	
	PORTA=0x02;
	_delay_ms(4000);
	
	PORTA=0x00;
	_delay_ms(4000);
}

void send_a_command(unsigned char command)
{
	PORTC=command;
	PORTD&=~(1<<registerselection);
	PORTD|=(1<<enable);
	_delay_ms(50);
	PORTD&=~(1<<enable);
	PORTC=0;
}

void send_a_character(unsigned char character)
{
	PORTC=character;
	PORTD|=(1<<registerselection);
	PORTD|=(1<<enable);
	_delay_ms(50);
	PORTD&=~(1<<enable);
	PORTC=0;
}

void send_a_string(char *string_of_characters)
{
	while(*string_of_characters>0)
	{
		send_a_character(*string_of_characters++);
	}
}



 