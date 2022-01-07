#define STM32F401xx
#include "stm32f4xx.h"
#include "UART_lib.h"
#include "dht22.h"
#include "systick_IR_timer_lib.h"
#include "delay_timer_lib.h"
#include "main.h"
#include "string.h"
#include "RTC.h"
#include "lcd.h"
#include "math.h"
#include <stdio.h>

void int2string(uint16_t num, char *buffer) {

	sprintf(buffer, "%d", num);

}

void format_dht22_values(char *buffer, uint16_t value) {
	uint8_t decimal = value % 10;
	uint8_t integer = value / 10;

	char integer_str[2];
	int2string(integer, integer_str);

	char decimal_str[1];
	int2string(decimal, decimal_str);

	buffer = strcat(strcat(integer_str, ","), decimal_str);
}

void dht22_application_callback() {

	char temp[4];
	char humidity[4];
	format_dht22_values(temp, dht22_data.temperature);
	format_dht22_values(humidity, dht22_data.humidity);

	LCD_write(&I2C_handle, temp, 4, 0, 0);
	LCD_write(&I2C_handle, humidity, 4, 0, 5);

}

void uart_pins_init() {
//pins PA2 and PA3
	pin_type uartTX, uartRX;
	uartTX.AF_num = 7;
	uartTX.PP_OD = PP;
	uartTX.gpio = GPIOA;
	uartTX.mode = ALTERNATE_FUNCTION;
	uartTX.pin_num = 2;
	uartTX.push_pull = NO_PULL;

	uartRX = uartTX;
	uartRX.pin_num = 3;

	init_pin(&uartTX);
	init_pin(&uartRX);

}

void I2C_pins_init() {
	pin_type SCL, SDA;
	SCL.AF_num = 4;
	SCL.PP_OD = 0;
	SCL.push_pull = PULL_UP;
	SCL.gpio = GPIOB;
	SCL.mode = ALTERNATE_FUNCTION;
	SCL.pin_num = 6;

	SDA = SCL;
	SDA.pin_num = 7;

	init_pin(&SCL);
	init_pin(&SDA);

}


void init_time() {

	memset(&date_time, 0, sizeof(date_time));
	date_time.date = 6;
	date_time.day = thursday;
	date_time.hours = 9;
	date_time.minutes = 8;
	date_time.month = 1;
	date_time.seconds = 0;
	date_time.time_format = format_24;
	date_time.year = 22;

	RTC_init(&date_time);

	date_time.seconds = 0;
	alarm_mask_type mask;
	memset(&mask, 0, sizeof(mask));
	mask.seconds = mask_enable;

	set_alarm(&date_time, &mask, alarm_A);
}

void debug_pins(I2C_handle_type *handle) {
	uint8_t data = 1;
	handle->data = &data;
	handle->data_len = 1;

	for (uint32_t i = 0; i < 8; i++) {

		I2C_transmit_data_and_wait(handle);
		data = pow(2, i + 1);
		handle->data = &data;
		handle->data_len = 1;

	}
}

int main(void) {
	uart_init(USART2, UART_8BIT, UART_1_STOP_BITS, 115200);

	I2C_handle.peripheral = I2C1;
	I2C_handle.addressing_mode = I2C_7_BIT_ADDRESSING;
	I2C_handle.slave_address = 0x27;
	I2C_init(&I2C_handle);

	init_timer(TIM2, 2);

	LCD_init(&I2C_handle);

	while (1) {

	}
}
