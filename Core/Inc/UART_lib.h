/*
 * UART_lib.h
 *
 *  Created on: Nov 30, 2021
 *      Author: toni
 */
#include "stm32f4xx.h"

#ifndef INC_UART_LIB_H_
#define INC_UART_LIB_H_

#define UART_BR_9600 9600

#define UART_8BIT 0
#define UART_9BIT 1u

#define UART_0_STOP_BITS 0
#define UART_0_5_STOP_BITS 1u
#define UART_1_STOP_BIT 2u

void init_uart(USART_TypeDef* uart, uint8_t word_length, uint8_t stop_bits, uint32_t);



#endif /* INC_UART_LIB_H_ */
