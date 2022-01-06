#define STM32F401xx
#include "stm32f4xx.h"
#include "UART_lib.h"
#include "dht22.h"
#include <stdio.h>
#include <systick_IR_timer_lib.h>
#include "delay_timer_lib.h"
#include "main.h"
#include "string.h"
#include "RTC.h"

pin_type test_pin;

void dht22_application_callback() {
	printf("%d\n", (int) dht22_data.temperature);
	printf("%d\n", (int) dht22_data.humidity);

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

void format_date_time(char *buffer, date_time_type *date_time) {
	char format[] = "%02d:%02d:%02d  %02d/%02d/20%02d\n\r";
	sprintf(buffer, format, (int) date_time->hours, (int) date_time->minutes,
			(int) date_time->seconds, (int) date_time->date,
			(int) date_time->month, (int) date_time->year);
}

int main(void) {

	init_systick();
	init_timer(TIM2, 1);
	init_dht22();


	uart_init(USART2, UART_8BIT, UART_1_STOP_BITS, 115200);
	uint8_t data[2] = {0x1, 0xFF};


	memset(&I2C_handle, 0, sizeof(I2C_handle));
	I2C_handle.addressing_mode = I2C_7_BIT_ADDRESSING;
	I2C_handle.peripheral = I2C1;
	I2C_handle.slave_address = 0x27;
	I2C_handle.data = data;
	I2C_handle.data_len = 2;

	date_time_type date_time;
	date_time.date = 29;
	date_time.day = wednesday;
	date_time.hours = 0;
	date_time.minutes = 0;
	date_time.month = 12;
	date_time.seconds = 0;
	date_time.time_format = format_24;
	date_time.year = 21;

	RTC_init(&date_time);

	date_time.seconds = 5;
	alarm_mask_type mask;
	memset(&mask, 0, sizeof(mask));
	mask.seconds = mask_enable;

	set_alarm(&date_time, &mask, alarm_A);

	I2C_init(&I2C_handle);
	char time[22];

	//I2C_transmit_data_and_wait(&I2C_handle);

	uint8_t data2 = 0x1u;
	I2C_handle.data = &data2;
	I2C_handle.data_len = 1;

	//I2C_transmit_data(&I2C_handle);

	while (1) {
		date_time = get_date_time();
		format_date_time(time, &date_time);
		uart_transmit_data(USART2, (uint8_t*) time, sizeof(time) / sizeof(time[0]));
		//dht22_get_data();
		//toggle_pin(&test_pin);
		delay(2000, TIM2);

	}

}
