/*
 * UART.c
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "UART.h"

Status UART_Init (UART_Cfg* a_UARtcfg_ptr)
{
	/*Check Double speed bits & Calculate UBRR value*/
	uint16 UBRRValue = 0;
	if (a_UARtcfg_ptr->DoubleSpeed == DoubleSpeedDisable)
	{
		ClrBit(UCSRA,U2X);
		UBRRValue = ((F_CPU)/((a_UARtcfg_ptr->baudrate)*(16U)))-1;
	}
	else if (a_UARtcfg_ptr->DoubleSpeed == DoubleSpeedEnable)
	{
		SetBit(UCSRA,U2X);
		UBRRValue = ((F_CPU)/((a_UARtcfg_ptr->baudrate)*(8U)))-1;
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
	
	/*Check TX compelet interrupt Enable bit*/
	if (a_UARtcfg_ptr->TxcInterrupt == TxcInterruptDisable)
	{
		ClrBit(UCSRB,TXCIE);
	}	
	else if (a_UARtcfg_ptr->TxcInterrupt == TxcInterruptEnable)
	{
		SetBit(UCSRB,TXCIE);
	}
	else
	{
		return NotOk;
	}
	
	/*Check RX comolete interrupt Enable bit*/
	if (a_UARtcfg_ptr->RxcInterrupt == RxcInterruptDisable)
	{
		ClrBit(UCSRB,RXCIE);
	}
	else if (a_UARtcfg_ptr->RxcInterrupt == RxcInterruptEnable)
	{
		SetBit(UCSRB,RXCIE);
	}
	else
	{
		return NotOk;
	}
	
	/*Check UDR Empty interrupt Enable bit*/
	if (a_UARtcfg_ptr->UDRInterrupt == UDRInterruptDisable)
	{
		ClrBit(UCSRB,UDRIE);
	}
	else if (a_UARtcfg_ptr->UDRInterrupt == UDRInterruptEnable)
	{
		SetBit(UCSRB,UDRIE);
	}
	else
	{
		return NotOk;
	}
	
	/*Clear URSEL bit into UCSRA to write in UCSRC*/
	SetBit(UCSRA,URSEL);
	
	/*Check data size bits*/
	if (a_UARtcfg_ptr->DataSize == DataSize5Bits)
	{
		ClrBit(UCSRC,UCSZ0);
		ClrBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (a_UARtcfg_ptr->DataSize == DataSize6Bits)
	{
		SetBit(UCSRC,UCSZ0);
		ClrBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (a_UARtcfg_ptr->DataSize == DataSize7Bits)
	{
		ClrBit(UCSRC,UCSZ0);
		SetBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (a_UARtcfg_ptr->DataSize == DataSize8Bits)
	{
		SetBit(UCSRC,UCSZ0);
		SetBit(UCSRC,UCSZ1);
		ClrBit(UCSRB,UCSZ2);
	}
	else if (a_UARtcfg_ptr->DataSize == DataSize9Bits)
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
	if (a_UARtcfg_ptr->ParityBit == ParityDisable)
	{
		ClrBit(UCSRC,UPM0);
		ClrBit(UCSRC,UPM1);
	}
	else if (a_UARtcfg_ptr->ParityBit == ParityOdd)
	{
		SetBit(UCSRC,UPM0);
		SetBit(UCSRC,UPM1);
	}
	else if (a_UARtcfg_ptr->ParityBit == ParityEven)
	{
		ClrBit(UCSRC,UPM0);
		SetBit(UCSRC,UPM1);
	}
	else
	{
		return NotOk;
	}
	
	/*Check stop bits*/
	if (a_UARtcfg_ptr->StopBits == StopBits1)
	{
		ClrBit(UCSRC,USBS);
	}
	else if (a_UARtcfg_ptr->StopBits == StopBits2)
	{
		SetBit(UCSRC,USBS);
	}
	else
	{
		return NotOk;
	}
	
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
