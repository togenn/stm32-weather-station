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

#define UART_1_STOP_BITS 0
#define UART_0_5_STOP_BITS 1u
#define UART_2_STOP_BITS 2u

//User definable
void init_uart_pins(void);

void init_uart(USART_TypeDef* uart, uint8_t word_length, uint8_t stop_bits, uint32_t);

void uart_transmit_data(USART_TypeDef* uart, uint8_t* data_buffer, uint32_t len);


#endif /* INC_UART_LIB_H_ */
