/*
 * clocks_lib.c
 *
 *  Created on: Dec 1, 2021
 *      Author: toni
 */
#include "clocks_lib.h"
#include "stm32f4xx.h"

#define HSE 0
#define HSI 1u
#define PLL 3u

#define PLLP_2 0
#define PLLP_4 1u
#define PLLP_6 2u
#define PLLP_8 3u

static void select_clk_source(uint8_t clk_source) {
	RCC->CFGR |= clk_source;
}

void init_SYSCLK_HSE() {
	//HSE 8MHz

	//enable HSE
	RCC->CR |= 1u << 17;
	select_clk_source(HSE);
}


void init_SYSCLK_PLL(uint8_t clk_source, uint16_t PLLN, uint8_t PLLM, uint8_t PLLP) {
	//enable PLL
	RCC->CR |= 1u << 24;

	switch (clk_source) {
	case HSE:
		RCC->CR |= 1u << 17;
		break;

	case HSI:
		RCC->CR |= 1u;
		break;
	}

	select_clk_source(clk_source);
}

void init_peripheral_prescalers();

uint32_t get_SYSCLK();
uint32_t get_AHB_clock();
uint32_t get_APB1_clock();
uint32_t get_APB2_clock();



