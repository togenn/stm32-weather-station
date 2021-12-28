/*
 * I2c_lib.c
 *
 *  Created on: 28 Dec 2021
 *      Author: Toni
 */
#include "I2C_lib.h"
#include "clocks_lib.h"
#include "NVIC_lib.h"

static void I2C_enable_clock(I2C_handle_type *handle) {

	if (handle->peripheral == I2C1) {
		RCC->APB1ENR |= 1u << 21;
	} else if (handle->peripheral == I2C2) {
		RCC->APB1ENR |= 1u << 22;
	} else if (handle->peripheral == I2C3) {
		RCC->APB1ENR |= 1u << 23;
	}
}

static void I2C_enable_IR(I2C_handle_type *handle) {

	if (handle->peripheral == I2C1) {
		enable_IR(I2C1_EV_IRQn);
		enable_IR(I2C1_ER_IRQn);
	} else if (handle->peripheral == I2C2) {
		enable_IR(I2C2_EV_IRQn);
		enable_IR(I2C2_ER_IRQn);
	} else if (handle->peripheral == I2C3) {
		enable_IR(I2C3_EV_IRQn);
		enable_IR(I2C3_ER_IRQn);
	}
}

void I2C_init(I2C_handle_type *handle) {
	I2C_pins_init();
	I2C_enable_clock(handle);
	I2C_enable_IR(handle);

	//Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	uint8_t APB1_clk_MHz = get_APB1_clock() / 1000000;
	handle->peripheral->CR2 |= 0x1Fu & APB1_clk_MHz;

	//Configure the clock control registers
	uint16_t ccr = 5000 / (APB1_clk_MHz / 1000);
	handle->peripheral->CCR = ccr;

	//Configure the rise time register
	handle->peripheral->TRISE = ccr + 1;

	//enable interrupts
	handle->peripheral->CR2 |= 7u << 8;
}

uint8_t I2C_transmit_data(I2C_handle_type *handle) {

	if (handle->status != I2C_STATUS_IDLE) {
		return 1;
	}

	handle->status = I2C_STATUS_TRANSMITTING;

	//enable the peripheral
	handle->peripheral->CR1 |= 1u;

	//generate a Start condition
	handle->peripheral->CR1 |= 1u << 8;

	return 0;
}

uint8_t I2C_transmit_data_and_wait(I2C_handle_type *handle) {

	if (handle->status != I2C_STATUS_IDLE) {
		return 1;
	}

	I2C_transmit_data(handle);

	while (handle->status != I2C_STATUS_IDLE)
		;

	return 0;

}

static void handle_start_condition(I2C_handle_type *handle) {

	if (handle->addressing_mode == I2C_7_BIT_ADDRESSING) {

		handle->peripheral->DR = handle->slave_address;
	} else {
		uint8_t header = 0xF0;
		uint8_t bits_9_8 = handle->slave_address >> 8;

		header |= (0b11 << 1) & bits_9_8;
	}
}

void I2C_handle_EV(I2C_handle_type *handle) {

	if (handle->peripheral->SR1 & 1u) {
		//start condition
		handle_start_condition(handle);

	} else if (handle->peripheral->SR1 & (1u << 3)) {
		//header sent, send rest of the address
		handle->peripheral->DR = handle->slave_address;

	} else if (handle->peripheral->SR1 & 2u) {
		//address sent, send first frame
		handle->peripheral->DR = *(handle->data++);
		(void) handle->peripheral->SR2;

	} else if (handle->peripheral->SR1 & (1u << 7)) {
		//data register empty, write next frame to DR
		handle->peripheral->DR = *(handle->data++);

		if (--handle->data_len == 0) {
			//generate stop condition
			handle->peripheral->CR1 |= 1u << 9;

			handle->peripheral->CR1 &= ~1u;
			handle->status = I2C_STATUS_IDLE;

		}
	}
}

uint8_t I2C_handle_ER(I2C_handle_type *handle) {
	uint8_t error_code;

	if (handle->peripheral->SR1 & (1u << 8)) {
		error_code = 8;
	} else if (handle->peripheral->SR1 & (1u << 10)) {
		error_code = 10;
	} else if (handle->peripheral->SR1 & (1u << 11)) {
		error_code = 11;
	} else if (handle->peripheral->SR1 & (1u << 14)) {
		error_code = 14;
	}

	handle->peripheral->CR1 &= ~1u;
	handle->status = I2C_STATUS_IDLE;

	return error_code;

}

