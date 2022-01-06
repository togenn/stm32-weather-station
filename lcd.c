#include "lcd.h"
#include "delay_timer_lib.h"

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
	I2C_receive_data_and_wait(I2C_handle);

	busy_flag = (busy_flag >> 7) & 1u;

	return busy_flag;
}

static void send_command(I2C_handle_type *I2C_handle, uint8_t data) {
	uint8_t dataH = data >> 4;
	uint8_t dataL = data & 0xFu;

	uint8_t I2C_data[2] = { data, data & ~(1u << 3) };
	I2C_handle->data = I2C_data;
	I2C_handle->data_len = 2;
	I2C_transmit_data_and_wait(I2C_handle);
}


static void send_init_command(I2C_handle_type *I2C_handle) {
	uint8_t instruction = 0;
	instruction |= 1u << 2;
	instruction |= 3u << 3;

	uint8_t I2C_data[2] = { instruction, instruction & ~(1u << 3) };
	I2C_handle->data = I2C_data;
	I2C_handle->data_len = 2;
	I2C_transmit_data_and_wait(I2C_handle);
}

void LCD_init(I2C_handle_type *I2C_handle) {

	delay(15, TIM2);

	I2C_handle->addressing_mode = I2C_7_BIT_ADDRESSING;
	I2C_handle->slave_address = 0x27;
	I2C_init(I2C_handle);

	send_init_command(I2C_handle);

	delay(5, TIM2);

	send_init_command(I2C_handle);

	delay(1, TIM2);

	send_init_command(I2C_handle);
	while (!get_busy_flag(I2C_handle))
		;

	send_command(I2C_handle, 2u);

}

void LCD_write(I2C_handle_type *I2C_handle, char *text);
