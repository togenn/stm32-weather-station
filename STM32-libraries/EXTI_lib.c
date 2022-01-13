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

static uint8_t get_gpio_number(GPIO_TypeDef *gpio) {

	uint8_t gpio_num;

	if (gpio == GPIOA) {

		gpio_num = EXTI_GPIOA;

	} else if (gpio == GPIOB) {

		gpio_num = EXTI_GPIOB;

	} else if (gpio == GPIOC) {

		gpio_num = EXTI_GPIOC;

	} else if (gpio == GPIOD) {

		gpio_num = EXTI_GPIOD;

	} else if (gpio == GPIOE) {

		gpio_num = EXTI_GPIOE;

	} else if (gpio == GPIOH) {

		gpio_num = EXTI_GPIOH;
	}

	return gpio_num;
}

void enable_EXTI_GPIO(uint8_t pin_num, GPIO_TypeDef* gpio, uint8_t edge) {

	RCC->APB2ENR |= 1u << 14;

	uint8_t gpio_num = get_gpio_number(gpio);

	//enable correct port from SYSCFG register for EXTI
	uint8_t SYSCFG_values[2];
	calculate_SYSCFG_values(pin_num, SYSCFG_values);

	SYSCFG->EXTICR[SYSCFG_values[0]] |= (gpio_num << SYSCFG_values[1]);

	enable_EXTI(pin_num, edge);

}

void disable_EXTI_GPIO(uint8_t pin_num) {
	uint8_t SYSCFG_values[2];
	calculate_SYSCFG_values(pin_num, SYSCFG_values);

	SYSCFG->EXTICR[SYSCFG_values[0]] &= ~(0xFu << SYSCFG_values[1]);

	disable_EXTI(pin_num);

}

void enable_EXTI(uint8_t EXTI_num, uint8_t edge) {
	switch (edge) {
	case EXTI_REFE:
		EXTI->FTSR |= 1u << EXTI_num;
		EXTI->RTSR |= 1u << EXTI_num;
		break;

	case EXTI_RE:
		EXTI->RTSR |= 1u << EXTI_num;
		break;

	case EXTI_FE:
		EXTI->FTSR |= 1u << EXTI_num;
		break;
	}

	EXTI->IMR |= 1u << EXTI_num;
}

void disable_EXTI(uint8_t EXTI_num) {
	EXTI->FTSR &= ~(1u << EXTI_num);
	EXTI->RTSR &= ~(1u << EXTI_num);

	EXTI->IMR &= ~(1u << EXTI_num);
}
