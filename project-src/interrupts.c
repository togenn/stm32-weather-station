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
#include "EXTI_lib.h"
#include <string.h>


void SysTick_Handler() {

	SysTick->CTRL = 0;
	dht22_handle_delay_IT();

}

void EXTI15_10_IRQHandler() {

	dht22_handle_data_pin_IT();
	EXTI->PR |= 1u << 10;

}

void TIM5_IRQHandler() {
	//reading data from dht22 failed
	dht22_data.temperature = 0xFFFF;
	dht22_data.humidity = 0xFFFF;

	disable_EXTI_GPIO(dht22.pin_num);

	temperature_tmp = 0;
	humidity_tmp = 0;
	bits_read = 0;

	dht_status = SLEEPING;
	TIM5->DIER &= ~1u;
	TIM5->CR1 &= ~1u;
	TIM5->SR = 0;
}

void I2C1_EV_IRQHandler() {
	I2C_handle_EV(&I2C_handle);
}

void I2C1_ER_IRQHandler() {
	uint8_t error_code = I2C_handle_ER(&I2C_handle);
	char number[2];
	sprintf(number, "%d", error_code);

	uart_transmit_data(USART2, (uint8_t*) number, 2);

	while (1)
		;
}

void EXTI17_RTC_Alarm_IRQHandler() {

	date_time_type date_time = get_date_time();
	char date_time_str[16];
	format_date_time(date_time_str, &date_time);
	LCD_write(&I2C_handle, date_time_str, 16, 0, 0);

	dht22_get_data_and_wait();

	char temp[6];
	char humidity[5];
	temp[0] = '\0';
	humidity[0] = '\0';
	format_dht22_values(temp, dht22_data.temperature);
	format_dht22_values(humidity, dht22_data.humidity);
	strcat(temp, "C ");
	humidity[4] = '%';

	LCD_write(&I2C_handle, temp, 6, 1, 0);
	LCD_write(&I2C_handle, humidity, 5, 1, 6);

	set_alarm(&date_time, &mask, alarm_A);

}

