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
#include "NVIC_lib.h"



void dht22_application_callback() {


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
	date_time.date = 11;
	date_time.day = tuesday;
	date_time.hours = 17;
	date_time.minutes = 23;
	date_time.month = 1;
	date_time.seconds = 0;
	date_time.time_format = format_24;
	date_time.year = 22;

	RTC_init(&date_time);
	set_priority(RTC_Alarm_IRQn, 3);

	date_time.seconds = 0;
	alarm_mask_type mask;
	memset(&mask, 0, sizeof(mask));


	set_alarm(&date_time, &mask, alarm_A);
}



int main(void) {
	//uart is used for debugging
	uart_init(USART2, UART_8BIT, UART_1_STOP_BITS, 115200);

	init_systick();

	dht22.gpio = GPIOA;
	dht22.pin_num = 10;
	init_dht22();
	set_priority(SysTick_IRQn, 2);

	I2C_handle.peripheral = I2C1;
	I2C_handle.addressing_mode = I2C_7_BIT_ADDRESSING;
	I2C_handle.slave_address = 0x27;
	I2C_init(&I2C_handle);
	set_priority(I2C1_EV_IRQn, 1);
	set_priority(I2C1_ER_IRQn, 0);

	init_timer(TIM2, 2);

	LCD_init(&I2C_handle);

	init_time();

	//TODO: enter sleep mode after initializing and make microcontroller to wake up only for interrupts (RTC alarm)

	while (1) {


	}
}
