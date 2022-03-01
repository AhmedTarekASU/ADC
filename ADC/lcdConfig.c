#include "lcdConfig.h"
#define LCD_PRT PORTC
#define LCD_DDR DDRC
#define LCD_PIN PINC
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

void lcdCommand(unsigned char cmnd)
{
	LCD_PRT = (LCD_PRT & 0x0F)|(cmnd & 0xF0);
	LCD_PRT &= ~(1<<LCD_RS);
	LCD_PRT &= ~(1<<LCD_RW);
	LCD_PRT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PRT &= ~(1<<LCD_EN);

	_delay_us(20);

	LCD_PRT = (LCD_PRT & 0x0F)|(cmnd<<4);
	LCD_PRT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PRT &= ~(1<<LCD_EN);

}

void lcdData(unsigned char data)
{
	LCD_PRT = (LCD_PRT & 0x0F)|(data & 0xF0);
	LCD_PRT |= (1<<LCD_RS);
	LCD_PRT &= ~(1<<LCD_RW);
	LCD_PRT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PRT &= ~(1<<LCD_EN);
	LCD_PRT = (LCD_PRT & 0x0F)|(data<<4);
	LCD_PRT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PRT &= ~(1<<LCD_EN);
}

void lcd_init()
{
	LCD_DDR = 0xFF;
	LCD_PRT &= ~(1<<LCD_EN);
	_delay_us(2000);
	lcdCommand(0x33);
	_delay_us(100);
	lcdCommand(0x32);
	_delay_us(100);
	lcdCommand(0x28);
	_delay_us(100);
	lcdCommand(0x0E);
	_delay_us(100);
	lcdCommand(0x01);
	_delay_us(2000);
	lcdCommand(0x06);
	_delay_us(100);
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
	lcdCommand(firstCharAdr[y-1] + x - 1);
	_delay_us(100);
}

void lcd_print(char* str)
{
	unsigned char i = 0;
	while(str[i]!=0)
	{
	    lcdData(str[i]);
		i++;
	}
}
