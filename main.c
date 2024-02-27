
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "LCD16x2_4bit.h"
#define DHT11_PIN 6
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Request()						
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);		
	_delay_ms(20);					
	PORTD |= (1<<DHT11_PIN);		
}

void Response()						
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data()							
{	
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);	
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN))				
		c = (c<<1)|(0x01);						
		else								
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

int main(void)
{	
	char data[5];
	lcdinit();					
	lcd_clear();			
	lcd_gotoxy(0,0);			
	lcd_print("Humidity =");
	lcd_gotoxy(0,1);
	lcd_print("Temp = ");
	
    while(1)
	{	
		Request();				
		Response();				
		I_RH=Receive_data();	
		D_RH=Receive_data();	
		I_Temp=Receive_data();	
		D_Temp=Receive_data();	
		CheckSum=Receive_data();
		
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			lcd_gotoxy(0,0);
			lcd_print("Error");
		}
		
		else
		{	
			itoa(I_RH,data,10);
			lcd_gotoxy(11,0);
			lcd_print(data);
			lcd_print(".");
			
			itoa(D_RH,data,10);
			lcd_print(data);
			lcd_print("%");

			itoa(I_Temp,data,10);
			lcd_gotoxy(6,1);
			lcd_print(data);
			lcd_print(".");
			
			itoa(D_Temp,data,10);
			lcd_print(data);
			lcddata(0xDF);
			lcd_print("C ");
			
			itoa(CheckSum,data,10);
			lcd_print(data);
			lcd_print(" ");
		}
				
	_delay_ms(500);
	}	
}