#ifndef LCDCONFIG_H_INCLUDED
#define LCDCONFIG_H_INCLUDED

void lcdCommand(unsigned char cmnd);
void lcdData(unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char* str);

#endif // LCDCONFIG_H_INCLUDED
