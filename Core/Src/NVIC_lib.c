#include "NVIC_lib.h"
#include "stm32f4xx.h"

static void calculate_register_values(uint8_t IRQn, uint8_t *buf,
		uint8_t bits_in_field) {

	bits_in_field = 32 / bits_in_field;
	uint8_t num = IRQn / bits_in_field;
	uint8_t pos = IRQn % bits_in_field;

	buf[0] = num;
	buf[1] = pos;
}

static void calculate_ISER_values(uint8_t IRQn, uint8_t *buf) {

	calculate_register_values(IRQn, buf, 1);
}



//priority must be between 0 and 15
void set_priority(uint8_t IRQn, uint8_t priority) {

	NVIC->IP[IRQn] = 0;
	NVIC->IP[IRQn] |= priority << 4;

}

void enable_IR(uint8_t IRQn) {

	uint8_t ISER_values[2];
	calculate_ISER_values(IRQn, ISER_values);

	NVIC->ISER[ISER_values[0]] |= 1u << ISER_values[1];
}

void disable_IR(uint8_t IRQn) {
	uint8_t ISER_values[2];
	calculate_ISER_values(IRQn, ISER_values);

	NVIC->ISER[ISER_values[0]] &= ~(1u << ISER_values[1]);

}
