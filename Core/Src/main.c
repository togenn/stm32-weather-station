#include "UART_lib.h"
#include "dht22.h"
#include <stdio.h>
#include <systick_IR_timer_lib.h>
#include "delay_timer_lib.h"
#include "main.h"
#include "string.h"

pin_type test_pin;

void dht22_application_callback() {
	printf("%d\n", (int) dht22_data.temperature);
	printf("%d\n", (int) dht22_data.humidity);

}

void uart_pins_init() {
	//pins PA2 and PA3
	pin_type uartTX, uartRX;
	init_pin(&uartTX, GPIOA, 2, alternate_function);
	init_pin(&uartRX, GPIOA, 3, alternate_function);

	set_AF_num(&uartTX, 7);
	set_AF_num(&uartRX, 7);
}

void I2C_pins_init() {
	pin_type SCL, SDA;
	init_pin(&SCL, GPIOB, 6, alternate_function);
	init_pin(&SDA, GPIOB, 7, alternate_function);

	set_AF_num(&SCL, 4);
	set_AF_num(&SDA, 4);
}

int main(void) {

	init_systick();
	init_timer(TIM2, 1);
	init_dht22();

	init_pin(&test_pin, GPIOA, 0, OUTPUT_PP);

	uart_init(USART2, UART_8BIT, UART_1_STOP_BITS, 115200);
	uint8_t data[] = "moro\n\r";

	memset(&I2C_handle, 0, sizeof(I2C_handle));
	I2C_handle.addressing_mode = I2C_7_BIT_ADDRESSING;
	I2C_handle.peripheral = I2C1;

	I2C_init(&I2C_handle);


	while (1) {

		uart_transmit_data(USART2, data, 6);
		dht22_get_data();
		//toggle_pin(&test_pin);
		delay(2000, TIM2);

	}

}
