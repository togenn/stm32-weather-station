/*
 * timer_lib.c
 *
 *  Created on: Dec 5, 2021
 *      Author: toni
 */
#include "delay_timer_lib.h"

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
		prescaler = get_APB1_prescaler();
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

void init_timer(TIM_TypeDef *timer, uint16_t prescaler) {
	//disable events
	timer->CR1 |= 2u;

	timer->PSC = prescaler - 1;

	enable_timer_clock(timer);
}

uint8_t delay(uint32_t ms, TIM_TypeDef *timer) {
	uint32_t max = 0;

	if (timer == TIM2 || timer == TIM5) {
		max--;
	} else {
		max = 65535;
	}

	uint8_t status = ms < (max / (get_timer_clock(timer) / 1000)) ? OK : OF_ERROR;

	if (status == OK) {
		timer->ARR = ms - 1;
		timer->CR1 |= 1u;
		while (timer->CNT != ms - 1);
	}


	return status;

}

