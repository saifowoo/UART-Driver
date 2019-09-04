/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"
#include "DIO.h"

int main(void)
{
	DDRA = 0xFF;
	uint8 recivevalue = 0;
	UART_Init();
	while (1)
	{
		UART_Start();
		UART_ReceiveChar(&recivevalue);
		PORTA = ((recivevalue - 48) & 0x0F) | ((recivevalue - 48) & 0xF0);
		UART_Stop();
	}
}

