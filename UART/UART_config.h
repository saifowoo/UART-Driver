/*
 * UART_config.h
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 

#include "typedefs.h"
#include "bitwise.h"


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define F_CPU		1000000UL

typedef enum
{
	NotOk = 0U,
	OK = 1U
}Status;

typedef enum
{
	DoubleSpeedDisable = 0U,
	DoubleSpeedEnable = 1U
}Speed;

typedef enum
{
	RxcInterruptDisable = 0U,
	RxcInterruptEnable = 1U
}RxcIntEn;

typedef enum
{
	TxcInterruptDisable = 0U,
	TxcInterruptEnable = 1U
}TxcIntEn;

typedef enum
{
	UDRInterruptDisable = 0U,
	UDRInterruptEnable = 1U
}UDRIntEn;

typedef enum
{
	DataSize5Bits = 5U,
	DataSize6Bits = 6U,
	DataSize7Bits = 7U,
	DataSize8Bits = 8U,
	DataSize9Bits = 9U
}Data;

typedef enum
{
	ParityDisable = 0U,
	ParityOdd = 1U,
	ParityEven = 2U
}Parity;

typedef enum
{
	StopBits1 = 1U,
	StopBits2 = 2U
}Stop;

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


#endif /* UART_CONFIG_H_ */