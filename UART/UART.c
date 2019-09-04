/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"
#include "Interrupt.h"

static volatile uint8 UARTisr_g = 0;

ISR(UART_TXC_VECT)
{
	UDR = UARTisr_g;
}

Status UART_Init (void)
{
	/*Check Double speed bits & Calculate UBRR value*/
	uint16 UBRRValue = 0;
	if (UARTconfig.DoubleSpeed == DoubleSpeedDisable)
	{
		ClrBit(UCSRA,U2X);
		UBRRValue = ((F_CPU)/((UARTconfig.baudrate)*(16U)))-1;
	}
	else if (UARTconfig.DoubleSpeed == DoubleSpeedEnable)
	{
		SetBit(UCSRA,U2X);
		UBRRValue = ((F_CPU)/((UARTconfig.baudrate)*(8U)))-1;
	}
	else
	{
		return NotOk;
	}
	
	/*Clear URSEL bit into UCSRA to write in UBRRH*/
	ClrBit(UCSRA,URSEL);
	
	/*Set UBRR value into UBRRH & UBRRL*/
	UBRRH = (uint8)(UBRRValue>>8);
	UBRRL = (uint8)UBRRValue;
		
	/*Clear URSEL bit into UCSRA to write in UCSRC*/
	SetBit(UCSRA,URSEL);
	
	/*Check data size bits*/
	if (UARTconfig.DataSize == DataSize5Bits)
	{
		ClrBit(UCSRC,UCSZ0);
		ClrBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (UARTconfig.DataSize == DataSize6Bits)
	{
		SetBit(UCSRC,UCSZ0);
		ClrBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (UARTconfig.DataSize == DataSize7Bits)
	{
		ClrBit(UCSRC,UCSZ0);
		SetBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (UARTconfig.DataSize == DataSize8Bits)
	{
		SetBit(UCSRC,UCSZ0);
		SetBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (UARTconfig.DataSize == DataSize9Bits)
	{
		SetBit(UCSRC,UCSZ0);
		SetBit(UCSRC,UCSZ1);
		SetBit(UCSRB,UCSZ2);
	}
	else
	{
		return NotOk;
	}
	
	/*Check parity bits*/
	if (UARTconfig.ParityBit == ParityDisable)
	{
		ClrBit(UCSRC,UPM0);
		ClrBit(UCSRC,UPM1);
	}
	else if (UARTconfig.ParityBit == ParityOdd)
	{
		SetBit(UCSRC,UPM0);
		SetBit(UCSRC,UPM1);
	}
	else if (UARTconfig.ParityBit == ParityEven)
	{
		ClrBit(UCSRC,UPM0);
		SetBit(UCSRC,UPM1);
	}
	else
	{
		return NotOk;
	}
	
	/*Check stop bits*/
	if (UARTconfig.StopBits == StopBits1)
	{
		ClrBit(UCSRC,USBS);
	}
	else if (UARTconfig.StopBits == StopBits2)
	{
		SetBit(UCSRC,USBS);
	}
	else
	{
		return NotOk;
	}
	
	return OK;
}


Status UART_SendChar (uint8 a_data)
{
	if (UARTconfig.UDRInterrupt == UDRInterruptDisable)
	{
		while((UCSRA & (1<<UDRE)) == 0);					//wait until UART Data Reg is Empty (UDRE) (0 wait , 1 Empty you can transmit now)
		UDR = a_data;
	}
	else if (UARTconfig.UDRInterrupt == UDRInterruptEnable)
	{
		UARTisr_g = a_data;
	}
	else
	{
		return NotOk;
	}
	return OK;
}

Status UART_Send (const uint8* a_data_ptr)
{
	uint32 index = 0;
	for (index=0 ; a_data_ptr[index] != '\0' ; index++)
	{
		UART_SendChar(a_data_ptr[index]);
	}
	return OK;
}

Status UART_Start (void)
{
	SetBit(UCSRA,TXEN);
	SetBit(UCSRA,RXEN);
	
	/*Check TX compelet interrupt Enable bit*/
	if (UARTconfig.TxcInterrupt == TxcInterruptDisable)
	{
		ClrBit(UCSRB,TXCIE);
		ClrBit(SREG,I);
	}
	else if (UARTconfig.TxcInterrupt == TxcInterruptEnable)
	{
		SetBit(UCSRB,TXCIE);
		SetBit(SREG,I);
	}
	else
	{
		return NotOk;
	}
	
	/*Check RX comolete interrupt Enable bit*/
	if (UARTconfig.RxcInterrupt == RxcInterruptDisable)
	{
		ClrBit(UCSRB,RXCIE);
		ClrBit(SREG,I);
	}
	else if (UARTconfig.RxcInterrupt == RxcInterruptEnable)
	{
		SetBit(UCSRB,RXCIE);
		SetBit(SREG,I);
	}
	else
	{
		return NotOk;
	}
	
	/*Check UDR Empty interrupt Enable bit*/
	if (UARTconfig.UDRInterrupt == UDRInterruptDisable)
	{
		ClrBit(UCSRB,UDRIE);
		ClrBit(SREG,I);
	}
	else if (UARTconfig.UDRInterrupt == UDRInterruptEnable)
	{
		SetBit(UCSRB,UDRIE);
		SetBit(SREG,I);
	}
	else
	{
		return NotOk;
	}
	
	return OK;
}

Status UART_Stop (void)
{
	ClrBit(UCSRA,TXEN);
	ClrBit(UCSRA,RXEN);
	
	ClrBit(UCSRB,UDRIE);
	ClrBit(UCSRB,RXCIE);
	ClrBit(SREG,I);
	return OK;
}














/*void vUART_TransmitChar (unsigned char data)
{
	while((UCSRA & (1<<UDRE)) == 0);					//wait until UART Data Reg is Empty (UDRE) (0 wait , 1 Empty you can transmit now)
	UDR = data;											//write in UART Data Reg and then transmit it
}

unsigned char ucUART_Recive (void)
{
	while((UCSRA & (1<<RXC)) == 0);						//wait until RX Complete (UDRE) (0 Receive Reg is empty , 1 there is new data in Receive Reg)
	return UDR;											//return UART Data Reg
	
}

void vUART_TransmitString (unsigned char *string)
{
	uint8_t i=0;
	while(string[i] != '\0')
	{
		vUART_TransmitChar(string[i]);
		i++;
	}
	
	//unsigned char i;
	//for(i=0;i<N;i++)
	//{
		//while((UCSRA & (1<<UDRE)) == 0);
		//UDR = string[i];
	//}
}*/
