/*
 * UART_config.c
 *
 * Created: 9/4/2019 1:38:33 PM
 *  Author: kingd
 */ 

#include "UART_config.h"

	UART_Cfg UARTconfig = {	9600U,
							DoubleSpeedDisable,
							RxcInterruptDisable,
							TxcInterruptDisable,
							UDRInterruptDisable,
							DataSize8Bits,
							ParityDisable,
							StopBits1 };
