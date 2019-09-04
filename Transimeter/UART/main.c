/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"
#include "DIO.h"
#include <util/delay.h>

int main(void)
{
	uint8 UARTCounter = 0;
	uint8 index = 0;
	UART_Init();
	DIO_SetPinDirection(PushButton0,INPUT);
	/* Replace with your application code */
	while (1)
	{
		UART_Start();
		for (index=0;index<10;index++)
		{
			if(DIO_ReadPin(PushButton0) == HIGH)
			{
				while(DIO_ReadPin(PushButton0) == HIGH);
				_delay_ms(50);
				UARTCounter++;
				index=0;
			}
			_delay_ms(100);
		}
		UART_SendChar(UARTCounter+48);
		UART_Stop();
		UARTCounter = 0;
		_delay_ms(1000);
	}
}

