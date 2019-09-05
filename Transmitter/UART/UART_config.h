/*
 * UART_config.h
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "typedefs.h"
#include "bitwise.h"
/*******************************************************************************/



/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define F_CPU		1000000UL
/*******************************************************************************/



/*******************************************************************************
 *                      Configuration Enums                                    *
 *******************************************************************************/

/******************** Check Status enum ********************/
typedef enum
{
	NotOk = 0U,
	OK = 1U
}Status;

/******************** Double Speed Mode enum ********************/
typedef enum
{
	DoubleSpeedDisable = 0U,
	DoubleSpeedEnable = 1U
}Speed;

/******************** Rx Complete Interrupt enum ********************/
typedef enum
{
	RxcInterruptDisable = 0U,
	RxcInterruptEnable = 1U
}RxcIntEn;

/******************** Tx Complete Interrupt enum ********************/
typedef enum
{
	TxcInterruptDisable = 0U,
	TxcInterruptEnable = 1U
}TxcIntEn;

/******************** UDR Empty Interrupt enum ********************/
typedef enum
{
	UDRInterruptDisable = 0U,
	UDRInterruptEnable = 1U
}UDRIntEn;

/******************** Data Bit Size enum ********************/
typedef enum
{
	DataSize5Bits = 5U,
	DataSize6Bits = 6U,
	DataSize7Bits = 7U,
	DataSize8Bits = 8U,
	DataSize9Bits = 9U
}Data;

/******************** Parity Bit enum ********************/
typedef enum
{
	ParityDisable = 0U,
	ParityOdd = 1U,
	ParityEven = 2U
}Parity;

/******************** Stop Bits enum ********************/
typedef enum
{
	StopBits1 = 1U,
	StopBits2 = 2U
}Stop;
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
typedef struct{
	uint16 baudrate;
	Speed   DoubleSpeed;
	RxcIntEn   RxcInterrupt;
	TxcIntEn   TxcInterrupt;
	UDRIntEn   UDRInterrupt;
	Data   DataSize;
	Parity   ParityBit;
	Stop   StopBits;
}UART_Cfg;

extern UART_Cfg UARTconfig;
/*******************************************************************************/


#endif /* UART_CONFIG_H_ */