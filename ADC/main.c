#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcdConfig.c"

uint16_t output;

void checkZeros(char* arr)
{
	for(uint8_t i=0; i<4; i++)
	{
		if(arr[i]!=0)
			break;
		else
			arr[i] = 0x30;
	}
}

void out(uint16_t output, char* arr)
{
	uint16_t q = output;
	uint8_t rem;
	for(uint8_t i=0; i<4; i++)
	{
		if(q!=0)
		{
			rem = q%10;
			q /= 10;
			arr[3-i] = 0x30 + rem;
		}
		else
			break;
	}
	checkZeros(arr);
}

void adc(uint8_t admux, uint8_t adps)
{
	if(adps>7)
		return;
	else
	{
		ADCSRA = (1<<ADEN)|(1<<ADIE)|adps;		//initialize ADC , Enable ADC Interrupt and Select Frequency Prescalar
		ADMUX = admux;						//select input channel, channel gain, single or differential input and Reference Voltage
		ADCSRA |= (1<<ADSC);
	}
}

ISR(ADC_vect)
{
	output = ADCL;
	output |= ADCH<<8;
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	sei();
	lcd_init();
	lcd_gotoxy(1,1);
	lcd_print("Converted value is equal to :");
	adc(0x40,0x03);
    while (1)
	{
		char str[4] = {0};
		_delay_us(10);
		out(output, str);
		lcd_gotoxy(1,2);
		lcd_print(str);
		ADCSRA |= (1<<ADSC);
	}
	return 0;
}

