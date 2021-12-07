/*
 * EXTI_lib.c
 *
 *  Created on: Nov 29, 2021
 *      Author: toni
 */
#include "EXTI_lib.h"

static void calculate_SYSCFG_values(uint8_t pin_num, uint8_t *buf) {

	uint8_t SYSCFG_num = pin_num / 4;
	uint8_t SYSCFG_pos = pin_num % 4 * 4;

	buf[0] = SYSCFG_num;
	buf[1] = SYSCFG_pos;

}

void enable_EXTI(uint8_t pin_num, uint8_t gpio, uint8_t edge) {

	RCC->APB2ENR |= 1u << 14;
	//enable correct port from SYSCFG register for EXTI
	uint8_t SYSCFG_values[2];
	calculate_SYSCFG_values(pin_num, SYSCFG_values);

	SYSCFG->EXTICR[SYSCFG_values[0]] |= (gpio << SYSCFG_values[1]);

	switch (gpio) {
	case EXTI_REFE:
		EXTI->FTSR |= 1u << pin_num;
		EXTI->RTSR |= 1u << pin_num;
		break;

	case EXTI_RE:
		EXTI->FTSR |= 1u << pin_num;
		break;

	case EXTI_FE:
		EXTI->RTSR |= 1u << pin_num;
		break;
	}

	EXTI->IMR |= 1u << pin_num;

}

void disable_EXTI(uint8_t pin_num) {
	uint8_t SYSCFG_values[2];
	calculate_SYSCFG_values(pin_num, SYSCFG_values);

	SYSCFG->EXTICR[SYSCFG_values[0]] &= ~(0xFu << SYSCFG_values[1]);

	EXTI->FTSR &= ~(1u << pin_num);
	EXTI->RTSR &= ~(1u << pin_num);

	EXTI->IMR &= ~(1u << pin_num);

	RCC->APB2ENR &= ~(1u << 14);

}

