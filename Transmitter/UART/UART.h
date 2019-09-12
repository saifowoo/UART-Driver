/*******************************************************************************
 * File Name	: UART.h                                                       *
 * Description	: header file for UART module                                  *
 * Created on	: 9/2/2019 9:00 PM                                             *
 * Author		: Saif El-Deen Moustafa                                        *
 *******************************************************************************/  



#ifndef UART_H_
#define UART_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "UART_config.h"
#include "typedefs.h"
#include "bitwise.h"
/*******************************************************************************/



/*******************************************************************************
*                          Mapped Registers                                   *
*******************************************************************************/

/******************** UART I/O Data Register ********************/
#define UDR    (*(volatile uint8*)0x2C)

/******************** UART Baud Rate Registers High ********************/
#define UBRRH (*(volatile uint8*)0x40)

/******************** UART Baud Rate Registers Low ********************/
#define UBRRL (*(volatile uint8*)0x29)

/******************** Control and StatusRegister A ********************/
#define UCSRA  (*(volatile uint8*)0x2B)
/********** Pin Description **********/
#define MPCM  (0U)
#define U2X   (1U)
#define PE    (2U)
#define DOR   (3U)
#define FE    (4U)
#define UDRE  (5U)
#define TXC   (6U)
#define RXC   (7U)

/******************** Control and StatusRegister B ********************/
#define UCSRB  (*(volatile uint8*)0x2A)
/********** Pin Description **********/
#define TXB8  (0U)
#define RXB8  (1U)
#define UCSZ2 (2U)
#define TXEN  (3U)
#define RXEN  (4U)
#define UDRIE (5U)
#define TXCIE (6U)
#define RXCIE (7U)

/******************** Control and StatusRegister C ********************/
#define UCSRC  (*(volatile uint8*)0x40)
/********** Pin Description **********/
#define UCPOL (0U)
#define UCSZ0 (1U)
#define UCSZ1 (2U)
#define USBS  (3U)
#define UPM0  (4U)
#define UPM1  (5U)
#define UMSEL (6U)
#define URSEL (7U)
/*******************************************************************************/


/*******************************************************************************
 *                       	TyPe Defines                                       *
 *******************************************************************************/
typedef void(* CallBackPtr)(void);
/*******************************************************************************/



/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define NULL		((void *)0)
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
	CallBackPtr		TxCallBack;
	CallBackPtr		RxCallBack;
}UART_Cfg;

extern UART_Cfg UARTconfig;
/*******************************************************************************/



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	UART_Init
 * Description: 	*used to intialize UART module
 * parameters:
 *		Inputs:			None
 *		Outputs:		None
 * Return:			Status to check function execution
 *******************************************************************************/
extern Status UART_Init (void);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	UART_SendChar
 * Description: 	*used to Send a byte
 * parameters:
 *		Inputs:			data to send
 *		Outputs:		None
 * Return:			Status to check function execution
 *******************************************************************************/
extern Status UART_SendChar (uint8 a_data);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	UART_Send
 * Description: 	*used to send a string of bytes
 * parameters:
 *		Inputs:			String to send
 *		Outputs:		None
 * Return:			Status to check function execution
 *******************************************************************************/
extern Status UART_Send (const uint8* a_data_ptr);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	UART_ReceiveChar
 * Description: 	*used to receive a byte
 * parameters:
 *		Inputs:			None
 *		Outputs:		received data
 * Return:			Status to check function execution
 *******************************************************************************/
extern Status UART_ReceiveChar(uint8* a_data);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	UART_Receive
 * Description: 	*used to receive string of Bytes
 * parameters:
 *		Inputs:			None
 *		Outputs:		String of received data
 * Return:			Status to check function execution
 *******************************************************************************/
extern Status UART_Receive (uint8* a_data);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	UART_Start
 * Description: 	*used to Start the communication
 * parameters:
 *		Inputs:			None
 *		Outputs:		None
 * Return:			Status to check function execution
 *******************************************************************************/
extern Status UART_Start (void);
/*******************************************************************************/

/*******************************************************************************
 * Function Name:	UART_Stop
 * Description: 	*used to Stop the communication
 * parameters:
 *		Inputs:			None
 *		Outputs:		None
 * Return:			Status to check function execution
 *******************************************************************************/
extern Status UART_Stop (void);
/*******************************************************************************/

#endif /* UART_H_ */