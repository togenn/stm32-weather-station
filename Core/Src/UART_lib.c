/*
 * UART_lib.c
 *
 *  Created on: Nov 30, 2021
 *      Author: toni
 */
#include "UART_lib.h"

static void enable_uart_clock(USART_TypeDef* uart) {

	if (uart == USART2) {
		RCC->APB1ENR = 1u << 17;
	} else if (uart == USART1) {
		RCC->APB2ENR = 1u << 4;
	} else if (uart == USART6) {
		RCC->APB2ENR = 1u << 5;
	}

}

static void set_BRR(uint32_t baudrate) {


}


void init_uart(USART_TypeDef* uart, uint8_t word_length, uint8_t stop_bits, uint32_t baudrate) {
	enable_uart_clock(uart);

	//Enable the USART
	uart->CR1 |= 1u << 13;

	//Program the M bit in USART_CR1 to define the word length
	uart->CR1 |= word_length << 12;

	//Program the number of stop bits in USART_CR2.
	uart->CR2 |= stop_bits << 12;

	//Select the desired baud rate using the baud rate register USART_BRR
	set_BRR(baudrate);

	6. Set the RE bit USART_CR1. This enables the receiver which begins searching for a
	start bit.

}

