#include "lcd.h"

//1st bit - RS
//2nd bit - RW
//3rd bit - E
//4th-7th - D4-D7
//8th - background light

static uint8_t get_busy_flag(I2C_handle_type *I2C_handle) {
	uint8_t command = 2u;
	I2C_handle->data = &command;
	I2C_handle->data_len = 1;
	I2C_transmit_data_and_wait(I2C_handle);

	uint8_t busy_flag = 0;
	I2C_handle->data = &busy_flag;
	I2C_handle->data_len = 1;
	busy_flag = I2C_receive_data_and_wait(I2C_handle);
}

void LCD_init(I2C_handle_type *I2C_handle) {
	I2C_handle->addressing_mode = I2C_7_BIT_ADDRESSING;
	I2C_handle->slave_address = 0x27;
	I2C_init(&I2C_handle);

}

void LCD_write(I2C_handle_type *I2C_handle, char *text);
