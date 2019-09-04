/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"
#include "Interrupt.h"

static volatile uint8 UARTisr_g = 0;
static volatile uint8 index = 0;
static volatile uint8 flag = 0;

/* ISR for UDR vector */
ISR(UART_UDR_VECT)
{
	if (UARTisr_g != 0)
	{
		UDR = UARTisr_g;
		index++;
		UARTisr_g = 0;
	}
	
}

/* ISR for receive vector */
ISR(USART_RXC_vect)
{
	flag = 1;
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
	uint32 loopindex = 0;
	
	if (UARTconfig.UDRInterrupt == UDRInterruptDisable)
	{
		for (loopindex=0 ; a_data_ptr[loopindex] != '\0' ; loopindex++)
		{
			UART_SendChar(a_data_ptr[loopindex]);
		}
	}
	else if (UARTconfig.UDRInterrupt == UDRInterruptEnable)
	{
		index = 0;
		while (a_data_ptr[index] != '\0')
		{
			UART_SendChar(a_data_ptr[index]);
		}
	}
	else
	{
		return NotOk;
	}
	
	return OK;
}

/*******************************************************************************
 * Function Name:	UART_Receive_Byte
 * Description: 	*used to receive a byte
 * parameters:
 *		Inputs:			None
 *		Outputs:		received data
 * Return:			Status to check function execution
 *******************************************************************************/
Status UART_ReceiveChar(uint8* a_data)
{
	if (UARTconfig.RxcInterrupt == RxcInterruptDisable)
	{
		/* Wait for data to be received */
		while ( !(UCSRA & (1<<RXC)) );
		/* Receive data from receiver buffer */
		*a_data = UDR;
	}
	else if(UARTconfig.RxcInterrupt == RxcInterruptEnable)
	{
		/* ISR will be executed */	
		if (flag == 1)
		{
			*a_data = UDR;
			flag = 0;
		}
		else
		{
			/* To avoid garbage value */
			*a_data = 0;
		}
	}
	else
	{
		return NotOk;
	}	
	
	return OK;
}

/*******************************************************************************
 * Function Name:	UART_Receive_String
 * Description: 	*used to receive string of Bytes
 * parameters:
 *		Inputs:			None
 *		Outputs:		String of received data
 * Return:			Status to check function execution
 *******************************************************************************/
Status UART_Receive (uint8* a_data)
{
	static uint8 counter_looper = 0;

	if (UARTconfig.RxcInterrupt == RxcInterruptDisable)
	{
		while(UDR != '#')
		{
			UART_ReceiveChar(&a_data[counter_looper]);
			counter_looper++;
		}
		counter_looper=0;
		
	}
	else if(UARTconfig.RxcInterrupt == RxcInterruptEnable)
	{
		/* ISR will be executed */
		if(UDR != '#')
		{
			UART_ReceiveChar(&a_data[counter_looper]);
			/* Garbage value detection */
			if (a_data[counter_looper] != 0)
			{
				counter_looper++;
			}
		}
		else
		{
			counter_looper=0;
		}
	}
	else
	{
		return NotOk;
	}
	
	return OK;
}
/*******************************************************************************/


Status UART_Start (void)
{
	SetBit(UCSRA,TXEN);
	SetBit(UCSRA,RXEN);
	
	/*Check TX compelet interrupt Enable bit*/
	if (UARTconfig.TxcInterrupt == TxcInterruptDisable)
	{
		ClrBit(UCSRB,TXCIE);
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
	ClrBit(UCSRB,TXCIE);
	
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
