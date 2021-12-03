#include <delay_lib.h>
#include "GPIO_Lib.h"
#include "weather_sensor.h"
#include "lcd.h"
#include "dht22.h"
#include <stdio.h>
#include "EXTI_lib.h"
#include "NVIC_lib.h"

extern void initialise_monitor_handles(void);
void system_clock_config(void);

pin_type internal_led_pin;
pin_type external_led;

void SysTick_Handler() {

	SysTick->CTRL = 0;
	handle_delay_IT();

}

void EXTI15_10_IRQHandler() {

	toggle_pin(&external_led);
	//handle_data_pin_IT();
	EXTI->PR |= 1u << 10;

}

void application_callback() {
	printf("%d\n", (int) dht22_data.temperature);
	printf("%d\n", (int) dht22_data.humidity);

}

void system_clock_config(void) {

	PWR->CR |= (2u << 14);

	RCC->PLLCFGR |= (1u << 22);
	RCC->PLLCFGR |= (1u << 3);
	RCC->PLLCFGR |= (0x54u << 6);

	RCC->CFGR |= (4u << 10);
	RCC->CFGR |= 2u;

	RCC->CR |= (1u << 18);
	RCC->CR |= (1u << 16);
	RCC->CR |= (1u << 24);
}

int main(void) {

	initialise_monitor_handles();

	printf("hello\n");

	system_clock_config();


	init_pin(&internal_led_pin, GPIOA, 5, OUTPUT_PP);
	init_pin(&external_led, GPIOA, 0, OUTPUT_PP);


	init_dht22();


	enable_IR(EXTI15_10_IRQn);
	enable_EXTI(10, EXTI_GPIOA, EXTI_RE);

	write_pin(&external_led, HIGH);

	while (1) {
		//get_data(&dht22);

	}

}
