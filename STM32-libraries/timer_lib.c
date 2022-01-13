/*
 * timer_lib.c
 *
 *  Created on: Dec 5, 2021
 *      Author: toni
 */
#include <timer_lib.h>
#include "clocks_lib.h"

static void enable_timer_clock(TIM_TypeDef *timer) {
	if (timer == TIM1) {
		RCC->APB2ENR |= 1u;
	} else if (timer == TIM2) {
		RCC->APB1ENR |= 1u;
	} else if (timer == TIM3) {
		RCC->APB1ENR |= 2u;
	} else if (timer == TIM4) {
		RCC->APB1ENR |= 4u;
	} else if (timer == TIM5) {
		RCC->APB1ENR |= 8u;
	} else if (timer == TIM9) {
		RCC->APB2ENR |= 1u << 16;
	} else if (timer == TIM10) {
		RCC->APB2ENR |= 1u << 17;
	} else if (timer == TIM11) {
		RCC->APB2ENR |= 1u << 18;
	}
}

static uint32_t get_timer_base_clock(TIM_TypeDef *timer) {
	uint32_t clk_speed;
	uint8_t prescaler;

	if (timer == TIM2 || timer == TIM3 || timer == TIM4 || timer == TIM5) {
		clk_speed = get_APB1_clock();
		prescaler = get_APB1_prescaler();
	} else {
		clk_speed = get_APB2_clock();
		prescaler = get_APB2_prescaler();
	}

	if (prescaler != 1) {
		clk_speed *= 2;
	}

	return clk_speed;
}

static uint32_t get_timer_clock(TIM_TypeDef *timer) {

	uint16_t prescaler = timer->PSC;

	return get_timer_base_clock(timer) / (prescaler + 1);
}

static void start_timer(uint32_t value, TIM_TypeDef *timer) {
	timer->CNT = 0;
	timer->ARR = value - 1;
	timer->CR1 |= 1u;
}

static uint32_t get_ms_value(uint32_t ms) {
	return ms * (timer_clock / 1000) - 1;
}

static uint32_t get_micros_value(uint32_t micros) {
	return micros * (timer_clock / 1000000) - 1;
}

static uint8_t check_for_overflow(uint32_t ms, TIM_TypeDef* timer) {
	uint32_t max = 0;

	if (timer == TIM2 || timer == TIM5) {
		max--;
	} else {
		max = 65535;
	}

	return ms < (max / (timer_clock / 1000)) ? OK : OF_ERROR;


}

void init_timer(TIM_TypeDef *timer, uint16_t prescaler) {
	enable_timer_clock(timer);
	timer->PSC = prescaler - 1;
	timer_clock = get_timer_clock(timer);

}

uint8_t delay(uint32_t ms, TIM_TypeDef *timer) {


	uint8_t status = check_for_overflow(ms, timer);

	if (status == OK) {
		start_timer(get_ms_value(ms), timer);
		while (!(timer->SR & 1u))
			;
		timer->SR &= ~1u;
	}

	return status;

}

void delay_micros(uint32_t micros, TIM_TypeDef *timer) {

	start_timer(get_micros_value(micros), timer);

	while (!(timer->SR & 1u))
		;
	timer->SR &= ~1u;

}

uint8_t timer_IT(uint32_t ms, TIM_TypeDef *timer) {

	uint8_t status = check_for_overflow(ms, timer);

	if (status == OK) {
		timer->DIER |= 1u;
		start_timer(get_ms_value(ms), timer);
	}

	return status;

}

void timer_micros_IT(uint32_t micros, TIM_TypeDef *timer) {
	timer->DIER |= 1u;
	start_timer(get_micros_value(micros), timer);
}

