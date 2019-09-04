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

#define INT2_vect_num		3
#define UART_TXC_VECT		15

//# define sei()  __asm__ __volatile__ ("sei" ::: "memory")

#define ISR(INTNUM) void __vector_##INTNUM (void) __attribute__ ((signal,used, externally_visible));\
void __vector_##INTNUM (void)




#endif /* INTERRUPT_H_ */