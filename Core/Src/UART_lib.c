/*
 * UART_lib.c
 *
 *  Created on: Nov 30, 2021
 *      Author: toni
 */
#include "UART_lib.h"
#include "clocks_lib.h"

static void enable_uart_clock(USART_TypeDef* uart) {

	if (uart == USART2) {
		RCC->APB1ENR |= 1u << 17;
	} else if (uart == USART1) {
		RCC->APB2ENR |= 1u << 4;
	} else if (uart == USART6) {
		RCC->APB2ENR |= 1u << 5;
	}

}

static void set_BRR(uint32_t baudrate, USART_TypeDef* uart) {
	uint32_t clk_speed;
	if (uart == USART2) {
		clk_speed = get_APB1_clock();
	} else {
		clk_speed = get_APB2_clock();
	}

	uart->BRR = clk_speed / baudrate;
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
	set_BRR(baudrate, uart);

	//Set the RE bit USART_CR1. This enables the receiver which begins searching for a start bit.
	uart->CR1 |= 1u << 2;

}

void uart_transmit_data(USART_TypeDef* uart, uint8_t* data_buffer, uint32_t len) {

	//Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	uart->CR1 |= 1u << 3;

	//Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
	//for each data to be transmitted in case of single buffer.
	for (int i = 0; i < len; i++) {
		uart->DR = data_buffer[i];

		while (!(uart->SR & (1u << 7)));
	}

	//After writing the last data into the USART_DR register, wait until TC=1. This indicates
	//that the transmission of the last frame is complete. This is required for instance when
	//the USART is disabled or enters the Halt mode to avoid corrupting the last
	//transmission.

	while(!(uart->SR & (1u << 6)));

	//disable transmission and clear TC bit
	uint32_t temp = uart->SR;
	uart->DR = 0;
	(void) temp;
	uart->CR1 &= ~(1u << 3);


}



