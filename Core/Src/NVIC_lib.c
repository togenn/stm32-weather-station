#include "NVIC_lib.h"
#include "stm32f4xx.h"

static void calculate_ISER_values(uint8_t IRQn, uint8_t *buf) {

	uint8_t ISER_num = IRQn / 32;
	uint8_t ISER_pos = IRQn % 32;

	buf[0] = ISER_num;
	buf[1] = ISER_pos;

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
