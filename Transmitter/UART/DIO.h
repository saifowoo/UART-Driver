/*
 * IncFile1.h
 *
 * Created: 8/17/2019 11:42:54 AM
 *  Author: kingd
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "typedefs.h"
#include "bitwise.h"

#define DDRA		(*((volatile uint8 *)0x3A))
#define DDRB		(*((volatile uint8 *)0x37))
#define DDRC		(*((volatile uint8 *)0x34))
#define DDRD		(*((volatile uint8 *)0x31))

#define PORTA		(*((volatile uint8 *)0x3B))
#define PORTB		(*((volatile uint8 *)0x38))
#define PORTC		(*((volatile uint8 *)0x35))
#define PORTD		(*((volatile uint8 *)0x32))

#define PINA		(*((volatile uint8 *)0x39))
#define PINB		(*((volatile uint8 *)0x36))
#define PINC		(*((volatile uint8 *)0x33))
#define PIND		(*((volatile uint8 *)0x30))

#define PINA0		0
#define PINA1		1
#define PINA2		2
#define PINA3		3
#define PINA4		4
#define PINA5		5
#define PINA6		6
#define PINA7		7

#define PINB0		8
#define PINB1		9
#define PINB2		10
#define PINB3		11
#define PINB4		12
#define PINB5		13
#define PINB6		14
#define PINB7		15

#define PINC0		16
#define PINC1		17
#define PINC2		18
#define PINC3		19
#define PINC4		20
#define PINC5		21
#define PINC6		22
#define PINC7		23

#define PIND0		24
#define PIND1		25
#define PIND2		26
#define PIND3		27
#define PIND4		28
#define PIND5		29
#define PIND6		30
#define PIND7		31

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7
#define PIN8		8
#define PIN9		9
#define PIN10		10
#define PIN11		11
#define PIN12		12
#define PIN13		13
#define PIN14		14
#define PIN15		15
#define PIN16		16
#define PIN17		17
#define PIN18		18
#define PIN19		19
#define PIN20		20
#define PIN21		21
#define PIN22		22
#define PIN23		23
#define PIN24		24
#define PIN25		25
#define PIN26		26
#define PIN27		27
#define PIN28		28
#define PIN29		29
#define PIN30		30
#define PIN31		31

#define LED0		12
#define LED1		13
#define LED2		14
#define LED3		15

#define PushButton1	10
#define PushButton0	20

#define INPUT		0
#define OUTPUT		1

#define LOW			0
#define HIGH		1

#define ROW1		18	
#define ROW2		19
#define ROW3		20
#define LINE1		21
#define LINE2		22
#define LINE3		23

#define SEGA		8
#define SEGB		9
#define SEGC		10
#define SEGD		11
#define SEGEN1		26
#define SEGEN2		27
#define SEGDP		28

void DIO_WritePin (uint8 PinNum,uint8 PinValue);
uint8 DIO_ReadPin (uint8 PinNum);
void DIO_SetPinDirection (uint8 PinNum,uint8 PinDirection);

#endif /* INCFILE1_H_ */