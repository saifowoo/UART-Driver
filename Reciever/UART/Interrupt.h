/*
 * Interrupt.h
 *
 * Created: 9/4/2019 2:51:44 PM
 *  Author: kingd
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define SREG		(*((volatile uint8 *)0x5F))
#define GICR		(*((volatile uint8 *)0x5B))
#define MCUCR		(*((volatile uint8 *)0x55))
#define MCUCSR		(*((volatile uint8 *)0x54))
#define GIFR		(*((volatile uint8 *)0x5A))

#define INT0_vect	(*((volatile uint8 *)0x5A))

#define INTF0		6
#define INTF1		7
#define INTF2		5

#define INT0		6
#define INT1		7
#define INT2		5

#define ISC2		6

#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3

#define I			7

#define INT2_vect				3
#define TIMER2_COMP_vect		4
#define TIMER2_OVF_vect			5
#define TIMER1_CAPT_vect		6
#define TIMER1_COMPA_vect		7
#define TIMER1_COMPB_vect		8
#define TIMER1_OVF_vect			9
#define TIMER0_COMP_vect		10
#define TIMER0_OVF_vect			11
#define UART_RXC_VECT			13
#define UART_UDR_VECT			14
#define UART_TXC_VECT			15

# define sei()  __asm__ __volatile__ ("sei" ::: "memory")

/*#define ISR(INTNUM) void __vector_##INTNUM (void) __attribute__ ((signal,used));\
void __vector_##INTNUM (void)*/

#define Timer_ISR	__vector_10
void Timer_ISR(void) __attribute__ ((signal, used));

#define RXC_ISR	__vector_13
void Timer_ISR(void) __attribute__ ((signal, used));

#define TXC_ISR	__vector_15
void Timer_ISR(void) __attribute__ ((signal, used));

#define UDR_ISR	__vector_14
void Timer_ISR(void) __attribute__ ((signal, used));

#endif /* INTERRUPT_H_ */