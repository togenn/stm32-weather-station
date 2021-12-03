#include <delay_lib.h>
#include "dht22.h"
#include <stdio.h>

uint16_t temperature_temp;
uint16_t humidity_temp;

static void enable_data_pin_IT(void) {
	EXTI->FTSR |= 1u << 10;
	EXTI->IMR |= 1u << 10;

	uint8_t ISER_num = EXTI15_10_IRQn / 32;
	uint8_t ISER_pos = EXTI15_10_IRQn % 32;

	NVIC->ISER[ISER_num] |= 1u << ISER_pos;
}

static void disable_data_pin_IT(void) {
	EXTI->FTSR &= ~(1u << 10);
	EXTI->IMR &= ~(1u << 10);

	uint8_t ISER_num = EXTI15_10_IRQn / 32;
	uint8_t ISER_pos = EXTI15_10_IRQn % 32;

	NVIC->ISER[ISER_num] &= ~(1u << ISER_pos);
}

static void read_bit(void) {
	pin_state value = read_pin(&dht22);

	if (bits_read == 32) {

		disable_data_pin_IT();

		dht22_data.temperature = temperature_temp;
		dht22_data.humidity = humidity_temp;

		temperature_temp = 0;
		humidity_temp = 0;
		bits_read = -1;

		dht_status = COOLDOWN;
		application_callback();
		delay_IR(1000);



	} else if (bits_read < 16) {

		humidity_temp |= (value << (15 - bits_read));

	} else if (bits_read < 32) {

		temperature_temp |= (value << (31 - bits_read));

	}

	bits_read++;


}

void handle_data_pin_IT() {
	delay_micros_IR(35);

}

void handle_delay_IT(void) {

	if (dht_status == INITIALIZING_1) {

		dht_status = INITIALIZING_2;

		write_pin(&dht22, HIGH);
		delay_micros_IR(20);

	} else if (dht_status == INITIALIZING_2) {

		dht_status = SENDING_DATA_INIT;
		set_input(&dht22, INPUT_PU);
		delay_micros_IR(160);

	} else if (dht_status == SENDING_DATA_INIT) {

		dht_status = SENDING_DATA;

		//enable interrupt for data pin on rising edge
		enable_data_pin_IT();

	} else if (dht_status == COOLDOWN) {

		dht_status = SLEEPING;

	} else if (dht_status == SENDING_DATA) {
		read_bit();
	}

}

void init_dht22() {

	dht_status = SLEEPING;

	init_pin(&dht22, GPIOA, 10, INPUT_PU);

}

uint8_t get_data(pin_type *pin) {
	if (dht_status == SLEEPING) {
		dht_status = INITIALIZING_1;

		set_output(pin, OUTPUT_PP);
		write_pin(pin, LOW);
		delay_micros_IR(1200);

	}

	return dht_status;

}

