/*******************************************************************************
 * File Name	: main.c                                                       *
 * Description	:                                                              *
 * Created on	: 9/8/2019 2:00 PM                                             *
 * Author		: Saif El-Deen Moustafa                                        *
 *******************************************************************************/ 

#include "UART.h"
#include "DIO.h"
#include <util/delay.h>

void UART_ISRCallBackTx (void);

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
		//UART_Stop();
		UARTCounter = 0;
		_delay_ms(1000);
	}
}

void UART_ISRCallBackTx (void)
{
	DIO_SetPinDirection(LED1,OUTPUT);
	TglBit(PORTB,PIN5);
}

