#include "dht22.h"
#include <systick_IR_timer_lib.h>
#include "EXTI_lib.h"
#include "NVIC_lib.h"


uint16_t temperature_temp;
uint16_t humidity_temp;

int bits_read;

static void read_bit(void) {
	pin_state value = read_pin(&dht22);

	if (bits_read == 32) {

		disable_EXTI(10);

		dht22_data.temperature = temperature_temp;
		dht22_data.humidity = humidity_temp;

		temperature_temp = 0;
		humidity_temp = 0;
		bits_read = -1;

		dht_status = SLEEPING;
		dht22_application_callback();

	} else if (bits_read < 16) {

		humidity_temp |= (value << (15 - bits_read));

	} else if (bits_read < 32) {

		temperature_temp |= (value << (31 - bits_read));

	}

	bits_read++;

}

void dht22_handle_data_pin_IT() {
	IR_timer_micros(35);

}


void dht22_handle_delay_IT(void) {

	if (dht_status == INITIALIZING) {

		dht_status = INITIALIZING_2;

		set_input(&dht22, INPUT_PU);

		IR_timer_micros(185);


	} else if (dht_status == INITIALIZING_2) {
		dht_status = SENDING_DATA;

		//enable interrupt for data pin on rising edge
		enable_EXTI(10, EXTI_GPIOA, EXTI_RE);

	} else if (dht_status == SENDING_DATA) {
		read_bit();
	}

}

void init_dht22() {

	dht_status = SLEEPING;

	init_pin(&dht22, GPIOA, 10, INPUT_PU);
	enable_IR(EXTI15_10_IRQn);

}

uint8_t dht22_get_data() {
	if (dht_status == SLEEPING) {
		dht_status = INITIALIZING;

		set_output(&dht22, OUTPUT_PP);
		write_pin(&dht22, LOW);
		IR_timer_micros(1000);

	}

	return dht_status;

}

void dht22_get_data_and_wait() {
	dht22_get_data();
	while(dht_status != SLEEPING);
}

