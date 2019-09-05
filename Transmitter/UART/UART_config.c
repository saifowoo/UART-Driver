/*
 * UART_config.c
 *
 * Created: 9/4/2019 1:38:33 PM
 *  Author: kingd
 */ 

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "UART_config.h"
/*******************************************************************************/



/*******************************************************************************
 * Configuration Structure = {	Baud Rate (2400 -> 250000),
 *								Double Speed Mode (Enable,Disable),
 *								RX Complete Interrupt (Enable,Disable),
 *								TX Complete Interrupt (Enable,Disable),
 *								UDR Empty Interrupt (Enable,Disable),
 *								Data Bits Size (5,6,7,8,9),
 *								Parity Bit (Enable,Disable),
 *								Stop Bits (1,2),
 *								};							
 *******************************************************************************/
	UART_Cfg UARTconfig = {	4800U,
							DoubleSpeedDisable,
							RxcInterruptDisable,
							TxcInterruptDisable,
							UDRInterruptDisable,
							DataSize8Bits,
							ParityDisable,
							StopBits1 };
/*******************************************************************************/

