/*
 * UART.h
 *
 * Created: 9/2/2019 9:00:00 PM
 *  Author: Saif El-Deen
 */ 


#ifndef UART_H_
#define UART_H_

#include "UART_config.h"

/*---UART_Registers---*/
#define UDR    (*(volatile uint8*)0x2C)
#define UBRRH (*(volatile uint8*)0x40)
#define UBRRL (*(volatile uint8*)0x29)

#define UCSRA  (*(volatile uint8*)0x2B)
/****UCSRA Bits---*/
#define MPCM  (0u)
#define U2X   (1u)
#define PE    (2u)
#define DOR   (3u)
#define FE    (4u)
#define UDRE  (5u)
#define TXC   (6u)
#define RXC   (7u)


#define UCSRB  (*(volatile uint8*)0x2A)
/*---UCSRB Bits---*/
#define TXB8  (0u)
#define RXB8  (1u)
#define UCSZ2 (2u)
#define TXEN  (3u)
#define RXEN  (4u)
#define UDRIE (5u)
#define TXCIE (6u)
#define RXCIE (7u)

#define UCSRC  (*(volatile uint8*)0x40)
/*---UCSRC Bits---*/
#define UCPOL (0u)
#define UCSZ0 (1u)
#define UCSZ1 (2u)
#define USBS  (3u)
#define UPM0  (4u)
#define UPM1  (5u)
#define UMSEL (6u)
#define URSEL (7u)





#define N			100								//number of elments in transmit string array

extern Status UART_Init (UART_Cfg* a_UARtcfg_ptr);
/*void vUART_TransmitChar (unsigned char);
void vUART_TransmitString (unsigned char *);
unsigned char ucUART_Recive (void);*/



#endif /* UART_H_ */