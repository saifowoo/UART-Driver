/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"

int main(void)
{
	uint8 data = 0;
	UART_Init();
	UART_Start();
	UART_Send("saif");
	/* Replace with your application code */
    while (1) 
    {
		UART_ReceiveChar(&data);
		UART_SendChar(data);
    }
}

