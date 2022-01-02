/*
 * I2C_lib.h
 *
 *  Created on: 28 Dec 2021
 *      Author: Toni
 */

#ifndef INC_I2C_LIB_H_
#define INC_I2C_LIB_H_

#include "stm32f4xx.h"

#define I2C_7_BIT_ADDRESSING 0
#define I2C_10_BIT_ADDRESSING 1

#define I2C_STATUS_IDLE 0
#define I2C_STATUS_TRANSMITTING 1
#define I2C_STATUS_RECEIVING 2

typedef struct {
	I2C_TypeDef* peripheral;
	uint8_t addressing_mode;
	uint16_t slave_address;
	uint8_t* data;
	uint32_t data_len;
	uint8_t status;
} I2C_handle_type;

void I2C_init(I2C_handle_type* handle);
void I2C_pins_init(); //user definable

/*
 * return 0 if peripheral is already busy, otherwise returns 1
 */
uint8_t I2C_transmit_data(I2C_handle_type* handle);
uint8_t I2C_transmit_data_and_wait(I2C_handle_type* handle);

uint8_t I2C_receive_data(I2C_handle_type* handle);
uint8_t I2C_receive_data_and_wait(I2C_handle_type* handle);

void I2C_handle_EV(I2C_handle_type* handle);

/*
 * Returns an error code:
 * 8 - bus error
 * 10 - ack failure
 * 11 - overrun error
 * 14 - timeout error
 */
uint8_t I2C_handle_ER(I2C_handle_type* handle);

#endif /* INC_I2C_LIB_H_ */
