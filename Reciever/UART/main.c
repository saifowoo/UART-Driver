/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"
#include "DIO.h"
#include <avr/delay.h>

int main(void)
{
	uint8 data = 0;
	uint8 flag = 0;
	uint8 pbcounter = 0;
	uint8 i = 0;
	UART_Init();
	UART_Start();
	DIO_SetPinDirection(SEGA,OUTPUT);
	DIO_SetPinDirection(SEGB,OUTPUT);
	DIO_SetPinDirection(SEGC,OUTPUT);
	DIO_SetPinDirection(SEGD,OUTPUT);
	/* Replace with your application code */
	while (1)
	{
		if (flag == 1)
		{
			while (DIO_ReadPin(PushButton0) == LOW)
			{
				DIO_WritePin(SEGDP,HIGH);
				_delay_ms(200);
				DIO_WritePin(SEGDP,LOW);
				_delay_ms(7200);
			}
		}
		pbcounter = 0;
		PORTB = (pbcounter & 0x0F) | (PORTB & 0xF0);
		for (i=0;i<10;i++)
		{
			if(DIO_ReadPin(PushButton0) == HIGH)
			{
				while(DIO_ReadPin(PushButton0) == HIGH);
				flag = 1;
				_delay_ms(50);
				pbcounter++;
				i=0;
			}
			_delay_ms(100);
		}
		PORTB = (pbcounter & 0x0F) | (PORTB & 0xF0);
		while ((DIO_ReadPin(LINE1) == HIGH) && (DIO_ReadPin(PushButton0) == LOW));
		pbcounter = 10;
		PORTB = (pbcounter & 0x0F) | (PORTB & 0xF0);
	}
}

