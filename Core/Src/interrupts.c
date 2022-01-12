/*
 * interrupts.c
 *
 *  Created on: 28 Dec 2021
 *      Author: Toni
 */
#include "stm32f4xx.h"
#include "dht22.h"
#include "main.h"
#include "UART_lib.h"
#include "stdio.h"
#include "lcd.h"
#include "RTC.h"

void SysTick_Handler() {

	SysTick->CTRL = 0;
	dht22_handle_delay_IT();

}

void EXTI15_10_IRQHandler() {

	dht22_handle_data_pin_IT();
	EXTI->PR |= 1u << 10;

}

void I2C1_EV_IRQHandler() {
	I2C_handle_EV(&I2C_handle);
}

void I2C1_ER_IRQHandler() {
	uint8_t error_code = I2C_handle_ER(&I2C_handle);
	char number[2];
	sprintf(number, "%d", error_code);

	uart_transmit_data(USART2, (uint8_t*) number, 2);

	while(1);
}


void format_date_time(char *buffer, date_time_type *date_time) {
	char format[] = "%02d:%02d %02d/%02d/20%d";
	sprintf(buffer, format, (int) date_time->hours, (int) date_time->minutes,
			(int) date_time->date,
			(int) date_time->month, (int) date_time->year);
}

void RTC_Alarm_IRQHandler() {

	date_time_type date_time = get_date_time();
	char date_time_str[16];
	format_date_time(date_time_str, &date_time);
	LCD_write(&I2C_handle, date_time_str, 16, 0, 0);

	dht22_get_data_and_wait();

}


