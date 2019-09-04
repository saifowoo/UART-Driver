/*
 * bitwise.h
 *
 * Created: 8/17/2019 11:25:25 AM
 *  Author: kingd
 */ 


#ifndef BITWISE_H_
#define BITWISE_H_

#define SetBit(REG,POS)		(REG |= (1U<<POS))
#define ClrBit(REG,POS)		(REG &=~(1U<<POS))
#define TglBit(REG,POS)		(REG ^= (1U<<POS))
#define GetBit(REG,POS)		(REG & (1U<<POS))



#endif /* BITWISE_H_ */