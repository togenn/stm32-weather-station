#include "GPIO_Lib.h"

void GPIOA_enable_clock(void) {
    RCC->AHB1ENR |= 0x1u;
}

void GPIOB_enable_clock(void) {
    RCC->AHB1ENR |= 0x2u;
}

void GPIOC_enable_clock(void) {
    RCC->AHB1ENR |= 0x4u;
}

void GPIOD_enable_clock(void) {
    RCC->AHB1ENR |= 0x8u;
}

void GPIOE_enable_clock(void) {
    RCC->AHB1ENR |= 0x10u;
}

void GPIOH_enable_clock(void) {
    RCC->AHB1ENR |= 0x80u;
}

void init_pin(pin_type* pin, GPIO_TypeDef* _gpio, uint32_t _pin_num, uint32_t _mode, uint32_t _PUPD) {
    pin->gpio = _gpio;
    pin->mode = _mode;
    pin->pin_num = _pin_num;
    pin->PUPD = _PUPD;

    pin->gpio->MODER |= pin->mode << ((pin->pin_num * 2));
    pin->gpio->PUPDR |= pin->PUPD << ((pin->pin_num * 2));
}

void set_input(pin_type* pin) {
	pin->gpio->MODER &= ~(3u << ((pin->pin_num * 2)));
	//pin->gpio->PUPDR &= ~(3u << ((pin->pin_num * 2)));
}

void set_output(pin_type* pin) {
	pin->gpio->MODER |= output << ((pin->pin_num * 2));
	//pin->gpio->PUPDR |= pin->PUPD << ((pin->pin_num * 2));
}

pin_state write_pin(pin_type* pin, pin_state state) {
    if (state == HIGH) {
        pin->gpio->ODR |= (1u << pin->pin_num);
    } else {
        pin->gpio->ODR &= ~(1u << pin->pin_num);
    }

    return state;
}

pin_state read_pin(pin_type* pin) {
    uint32_t state = ( pin->gpio->IDR >> pin->pin_num) & 1u;

    if (state == 1) {
        return HIGH;
    }

    return LOW;
}
pin_state toggle_pin(pin_type* pin) {
    pin->gpio->ODR ^= (1u << pin->pin_num);

    return read_pin(pin);
}
