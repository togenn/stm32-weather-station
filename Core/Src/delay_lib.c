#include <delay_lib.h>
#include "GPIO_Lib.h"

static void _delay(uint32_t s, uint32_t unit, uint8_t IR_type) {

	SysTick->CTRL = 0;
	SysTick->LOAD = 0;

	SysTick->LOAD |= s * unit - 1;
	SysTick->CTRL |= IR_type;
	SysTick->CTRL |= 1u;

}

void delay(uint32_t ms) {
	_delay(ms, MILLIS, POLLING);
}

void delay_micros(uint32_t micros) {
	_delay(micros, MICROS, POLLING);
}

void delay_IR(uint32_t ms) {
	_delay(ms, MILLIS, IR);
}

void delay_micros_IR(uint32_t micros) {
	_delay(micros, MICROS, IR);
}

