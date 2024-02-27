
#include "LCD16x2_4bit.h"

void lcdcommand(unsigned char cmnd)
{
	LCD_DPRT = (LCD_DPRT & 0x0f)|(cmnd & 0xf0);		
	LCD_DPRT &= ~ (1<<LCD_RS);						
	LCD_DPRT |= (1<<LCD_EN);						
	_delay_us(1);									
	LCD_DPRT &= ~(1<<LCD_EN);						
	_delay_us(100);									
	
	LCD_DPRT = (LCD_DPRT & 0x0f)|(cmnd << 4);		
	LCD_DPRT |= (1<<LCD_EN);						
	_delay_us(1);									
	LCD_DPRT &= ~(1<<LCD_EN);						
	_delay_ms(2);									
}

void lcddata(unsigned char data)
{
	LCD_DPRT = (LCD_DPRT & 0x0f)|(data & 0xf0);		
	LCD_DPRT |= (1<<LCD_RS);						
	LCD_DPRT |= (1<<LCD_EN);						
	_delay_us(1);									
	LCD_DPRT &= ~(1<<LCD_EN);						
	_delay_us(100);									
	
	LCD_DPRT = (LCD_DPRT & 0x0f)|(data << 4);		
	LCD_DPRT |= (1<<LCD_EN);						
	_delay_us(1);									
	LCD_DPRT &= ~(1<<LCD_EN);						
	_delay_ms(2);									
}

void lcdinit()
{
	LCD_DDDR = 0xFF;
	_delay_ms(200);									
	lcdcommand(0x33);
	lcdcommand(0x32);								
	lcdcommand(0x28);								
	lcdcommand(0x0C);								
	lcdcommand(0x01);								
	_delay_ms(2);
	lcdcommand(0x82);								
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char firstcharadd[]={0x80, 0xC0};
	lcdcommand(firstcharadd[y] + x);
}

void lcd_print(char *str)
{
	unsigned char i=0;
	while (str[i] |= 0)
	{
		lcddata(str[i]);
		i++;
	}
}

void lcd_clear()
{
	lcdcommand(0x01);
	_delay_ms(2);
}