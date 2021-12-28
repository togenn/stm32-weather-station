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

void init_pin(pin_type *pin, GPIO_TypeDef *_gpio, uint8_t _pin_num,
		uint8_t _mode) {
	pin->gpio = _gpio;
	pin->pin_num = _pin_num;

	enable_GPIOx_clock(_gpio);

	if (_mode < 3) {
		set_input(pin, _mode);
	} else if (_mode != alternate_function) {
		set_output(pin, _mode);
	} else {
		pin->gpio->MODER |= 2u << ((pin->pin_num * 2));
	}

}

void set_AF_num(pin_type* pin, uint8_t num) {
	uint8_t reg_H_L = pin->pin_num < 8 ? 0 : 1;

	pin->gpio->AFR[reg_H_L] |= (15u & num) << (pin->pin_num * 4);
}

void set_input(pin_type *pin, uint8_t mode) {
	pin->gpio->MODER &= ~(3u << ((pin->pin_num * 2)));
	pin->gpio->PUPDR &= ~(3u << ((pin->pin_num * 2)));

	switch (mode) {
	case INPUT_NO_PUPD:
		break;

	case INPUT_PU:
		pin->gpio->PUPDR |= (PU << ((pin->pin_num * 2)));
		break;

	case INPUT_PD:
		pin->gpio->PUPDR |= (PD << ((pin->pin_num * 2)));

	default:
		break;

	}

}

void set_output(pin_type *pin, uint8_t mode) {
	pin->gpio->MODER &= ~(3u << ((pin->pin_num * 2)));
	pin->gpio->MODER |= 1u << ((pin->pin_num * 2));

	switch (mode) {
	case OUTPUT_PP:
		break;

	case OUTPUT_OD:
		pin->gpio->OTYPER |= (OD << (pin->pin_num));
		break;

	default:
		break;
	}

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
