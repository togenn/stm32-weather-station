#include "lcd.h"
#include "delay_timer_lib.h"

//1st bit - RS
//2nd bit - RW
//3rd bit - E
//4th bit - background light
//5th-8th bit - data pins

static uint8_t get_busy_flag(I2C_handle_type *I2C_handle) {
	uint8_t command = LCD_CONTROL_INSTRUCTION | 2u;
	I2C_handle->data = &command;
	I2C_handle->data_len = 1;
	while (get_busy_flag(I2C_handle))
			;
	I2C_transmit_data_and_wait(I2C_handle);

	uint8_t busy_flag = 0;
	I2C_handle->data = &busy_flag;
	I2C_handle->data_len = 1;
	while (get_busy_flag(I2C_handle))
			;
	I2C_receive_data_and_wait(I2C_handle);

	busy_flag = (busy_flag >> 7) & 1u;

	return busy_flag;
}

static void send_data(I2C_handle_type *I2C_handle, uint8_t data,
		LCD_data_type data_type) {
	uint8_t control_bits =
			data_type ? LCD_CONTROL_DATA : LCD_CONTROL_INSTRUCTION;
	uint8_t dataH = (data & 0xF0u) | control_bits;
	uint8_t dataL = ((data & 0xFu) << 4) | control_bits;

	uint8_t I2C_dataH[2] = { dataH, dataH & ~(1u << 2) };
	I2C_handle->data = I2C_dataH;
	I2C_handle->data_len = 2;
	while (get_busy_flag(I2C_handle))
		;
	I2C_transmit_data_and_wait(I2C_handle);

	uint8_t I2C_dataL[2] = { dataL, dataL & ~(1u << 2) };
	I2C_handle->data = I2C_dataL;
	I2C_handle->data_len = 2;
	while (get_busy_flag(I2C_handle))
		;
	I2C_transmit_data_and_wait(I2C_handle);
}

static void send_command(I2C_handle_type *I2C_handle, uint8_t command) {
	send_data(I2C_handle, command, instruction);
}

static void send_char(I2C_handle_type *I2C_handle, char character) {
	send_data(I2C_handle, (uint8_t) character, data);
}

static void send_string(I2C_handle_type *I2C_handle, char* string, uint8_t len) {

	for (uint32_t i = 0;  i < len ; i++) {
		send_char(I2C_handle, *(string++));
	}
}

static void send_init_command(I2C_handle_type *I2C_handle, uint8_t command) {
	command <<= 4;
	command |= (1u << 2) | (1u << 3);

	uint8_t I2C_data[2] = { command, command & ~(1u << 2) };
	I2C_handle->data = I2C_data;
	I2C_handle->data_len = 2;
	while (get_busy_flag(I2C_handle))
		;
	I2C_transmit_data_and_wait(I2C_handle);
}

static void send_commands(I2C_handle_type *I2C_handle, uint8_t *commands,
		uint8_t len) {

	while (get_busy_flag(I2C_handle))
		;
	for (uint32_t i = 0; i < len; i++) {
		send_command(I2C_handle, *(commands++));
		while (get_busy_flag(I2C_handle))
			;
	}

}

static void set_cursor(I2C_handle_type *I2C_handle, uint8_t row, uint8_t column) {
	uint8_t row_change = row ? 64 : 0;

	send_command(I2C_handle, 0x80u + column + row_change);

}

void LCD_init(I2C_handle_type *I2C_handle) {

	delay(15, TIM2);

	send_init_command(I2C_handle, 3u);

	delay(5, TIM2);

	send_init_command(I2C_handle, 3u);

	delay(1, TIM2);

	send_init_command(I2C_handle, 3u);

	while (get_busy_flag(I2C_handle))
		;

	send_init_command(I2C_handle, 2u);

	uint8_t commands[4] = { 0x2Fu, 0x08u, 0x01u, 0x06u };
	send_commands(I2C_handle, commands, 4);

}

void LCD_write(I2C_handle_type *I2C_handle, char *text, uint8_t len,  uint8_t row, uint8_t column) {

	set_cursor(I2C_handle, row, column);

	send_string(I2C_handle, text, len);
}
