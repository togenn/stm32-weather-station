#include <systick_IR_timer_lib.h>
#include "clocks_lib.h"
#include "stm32f4xx.h"

static void timer(uint32_t s, uint32_t unit) {

	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	SysTick->LOAD |= s * unit - 1;
	SysTick->CTRL |= 7u;

}

void init_systick() {

	uint32_t processor_clock = get_AHB_clock();
	MILLIS = processor_clock / 1000;
	MICROS = processor_clock / 1000000;
}

void IR_timer_millis(uint32_t ms) {

	timer(ms, MILLIS);

}

void IR_timer_micros(uint32_t micros) {

	timer(micros, MICROS);

}

