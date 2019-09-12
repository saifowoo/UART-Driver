/*******************************************************************************
 * File Name	: UART_config.c                                                *
 * Description	: configuration source file for user interface                 *
 * Created on	: 9/2/2019 9:00 PM                                             *
 * Author		: Saif El-Deen Moustafa                                        *
 *******************************************************************************/  



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
 *								call back fun for TX interrupt,
 *								call back fun for RX interrupt
 *								};							
 *******************************************************************************/
	UART_Cfg UARTconfig = {	4800U,
							DoubleSpeedDisable,
							RxcInterruptEnable,
							TxcInterruptDisable,
							UDRInterruptDisable,
							DataSize8Bits,
							ParityDisable,
							StopBits1,
							NULL,
							UART_ISRCallBackRx };
/*******************************************************************************/

