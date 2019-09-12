/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"
#include "DIO.h"



/*volatile*/ uint8 recivevalue = 0;

int main(void)
{
	DDRA = 0xFF;
	
	UART_Init();
	while (1)
	{
		UART_Start();
		PORTA = ((recivevalue - 48) & 0x0F) | ((recivevalue - 48) & 0xF0);
		//UART_Stop();
	}
}

extern void UART_ISRCallBackRx (void)
{
	DIO_SetPinDirection(LED0,OUTPUT);
	TglBit(PORTB,PIN4);
	UART_ReceiveChar(&recivevalue);
}