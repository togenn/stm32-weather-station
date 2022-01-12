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
#include "string_formatting.h"

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



void RTC_Alarm_IRQHandler() {

	date_time_type date_time = get_date_time();
	char date_time_str[16];
	format_date_time(date_time_str, &date_time);
	LCD_write(&I2C_handle, date_time_str, 16, 0, 0);


	dht22_get_data_and_wait();


	//TODO: fix format_dht22_values()
	char temp[5];
	char humidity[5];
	format_dht22_values(temp, dht22_data.temperature);
	format_dht22_values(humidity, dht22_data.humidity);

	LCD_write(&I2C_handle, temp, 4, 1, 0);
	LCD_write(&I2C_handle, humidity, 4, 1, 5);

}


