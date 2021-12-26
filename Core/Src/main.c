#include "GPIO_Lib.h"
#include "dht22.h"
#include <stdio.h>
#include <systick_IR_timer_lib.h>
#include "UART_lib.h"
#include "delay_timer_lib.h"

pin_type internal_led_pin;
pin_type test_pin;

void SysTick_Handler() {

	SysTick->CTRL = 0;
	dht22_handle_delay_IT();

}

void EXTI15_10_IRQHandler() {

	dht22_handle_data_pin_IT();
	EXTI->PR |= 1u << 10;

}

void dht22_application_callback() {
	printf("%d\n", (int) dht22_data.temperature);
	printf("%d\n", (int) dht22_data.humidity);

}


void init_uart_pins() {
	//pins PA2 and PA3
	pin_type uartTX, uartRX;
	init_pin(&uartTX, GPIOA, 2, alternate_function);
	init_pin(&uartRX, GPIOA, 3, alternate_function);

	GPIOA->AFR[0] |= 7u << 8;
	GPIOA->AFR[0] |= 7u << 12;
}


int main(void) {

	init_systick();
	init_timer(TIM2, 1);
	init_dht22();

	init_pin(&test_pin, GPIOA, 0, OUTPUT_PP);


	init_uart_pins();
	init_uart(USART2, UART_8BIT, UART_1_STOP_BITS, 115200);
	uint8_t data[] = "moro\n\r";



	while (1) {

		uart_transmit_data(USART2, data, 6);
		dht22_get_data();
		//toggle_pin(&test_pin);
		delay(2000, TIM2);

	}

}
