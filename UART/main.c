/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"

int main(void)
{
    UART_Cfg config = {9600U,DoubleSpeedDisable,RxcInterruptDisable,TxcInterruptDisable,UDRInterruptDisable,DataSize8Bits,ParityDisable,StopBits1};
	UART_Init(&config);
	/* Replace with your application code */
    while (1) 
    {
		
    }
}

