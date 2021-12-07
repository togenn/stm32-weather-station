#include "GPIO_Lib.h"
#include "weather_sensor.h"
#include "lcd.h"
#include "dht22.h"
#include <stdio.h>
#include <systick_IR_timer_lib.h>
#include "EXTI_lib.h"
#include "NVIC_lib.h"
#include "clocks_lib.h"


extern void initialise_monitor_handles(void);

pin_type internal_led_pin;
pin_type external_led;

int count = 0;

void SysTick_Handler() {

	SysTick->CTRL = 0;

	//handle_delay_IT();

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

void enable_FPU() {
	uint32_t* FPU_CPACR = 0xE000ED88;

	*FPU_CPACR |= 15u << 20;
}


int main(void) {

	initialise_monitor_handles();

	printf("hello\n");

	enable_FPU();

	init_SYSCLK_PLL(HSE, 4u, 84u, PLLP_2);
	init_peripheral_prescalers(AHB_PRESCALER_1, APBx_PRESCALER_2, APBx_PRESCALER_2);

	//printf("%d\n", (int) get_AHB_clock());

	init_pin(&internal_led_pin, GPIOA, 5, OUTPUT_PP);



	//delay_IR(100);

	while (1) {
		//get_data(&dht22);

	}

}
