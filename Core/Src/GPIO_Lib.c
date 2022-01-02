#include "GPIO_Lib.h"

static void enable_GPIOx_clock(GPIO_TypeDef *gpio) {

	if (gpio == GPIOA) {

		RCC->AHB1ENR |= GPIOA_CLOCK_EN;

	} else if (gpio == GPIOB) {

		RCC->AHB1ENR |= GPIOB_CLOCK_EN;

	} else if (gpio == GPIOC) {

		RCC->AHB1ENR |= GPIOC_CLOCK_EN;

	} else if (gpio == GPIOD) {

		RCC->AHB1ENR |= GPIOD_CLOCK_EN;

	} else if (gpio == GPIOE) {

		RCC->AHB1ENR |= GPIOE_CLOCK_EN;

	} else if (gpio == GPIOH) {

		RCC->AHB1ENR |= GPIOH_CLOCK_EN;
	}
}

void init_pin(pin_type *pin) {

	enable_GPIOx_clock(pin->gpio);

	change_mode(pin);

	uint8_t reg_H_L = pin->pin_num < 8 ? 0 : 1;
	pin->gpio->AFR[reg_H_L] |= pin->AF_num << (pin->pin_num * 4);
}

void change_mode(pin_type *pin) {
	pin->gpio->MODER &= ~(3u << ((pin->pin_num * 2)));
	pin->gpio->PUPDR &= ~(3u << ((pin->pin_num * 2)));
	pin->gpio->OTYPER &= ~(1u << pin->pin_num);

	pin->gpio->MODER |= pin->mode << (pin->pin_num * 2);
	pin->gpio->OTYPER |= pin->PP_OD << pin->pin_num;
	pin->gpio->PUPDR |= pin->push_pull << (pin->pin_num * 2);

}

pin_state write_pin(pin_type *pin, pin_state state) {
	if (state == HIGH) {
		pin->gpio->ODR |= (1u << pin->pin_num);
	} else {
		pin->gpio->ODR &= ~(1u << pin->pin_num);
	}

	return state;
}

pin_state read_pin(pin_type *pin) {
	uint32_t state = (pin->gpio->IDR >> pin->pin_num) & 1u;

	if (state == 1) {
		return HIGH;
	}

	return LOW;
}
pin_state toggle_pin(pin_type *pin) {
	pin->gpio->ODR ^= (1u << pin->pin_num);

	return 0;
}
