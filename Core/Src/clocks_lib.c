/*
 * clocks_lib.c
 *
 *  Created on: Dec 1, 2021
 *      Author: toni
 */
#include "clocks_lib.h"
#include "stm32f4xx.h"
#include <stdio.h>

static void select_clk_source(uint8_t clk_source) {
	RCC->CFGR |= clk_source;
}

static uint16_t get_AHB_prescaler() {
	uint8_t bits = (15u << 4) & RCC->CFGR;
	uint16_t AHB_prescaler;

	if (!(bits & 8u)) {
		return 1;
	}

	switch (bits) {
	case AHB_PRESCALER_2:
		AHB_prescaler = 2;
		break;
	case AHB_PRESCALER_4:
		AHB_prescaler = 4;
		break;
	case AHB_PRESCALER_8:
		AHB_prescaler = 8;
		break;
	case AHB_PRESCALER_16:
		AHB_prescaler = 16;
		break;
	case AHB_PRESCALER_64:
		AHB_prescaler = 64;
		break;
	case AHB_PRESCALER_128:
		AHB_prescaler = 128;
		break;
	case AHB_PRESCALER_256:
		AHB_prescaler = 256;
		break;
	case AHB_PRESCALER_512:
		AHB_prescaler = 512;
		break;
	}

	return AHB_prescaler;
}

uint8_t get_APB1_prescaler() {
	uint8_t bits = (7u << 10) & RCC->CFGR;
	uint16_t APB1_prescaler;

	if (!(bits & 4u)) {
		return 1;
	}

	switch (bits) {
	case APBx_PRESCALER_2:
		APB1_prescaler = 2;
		break;
	case APBx_PRESCALER_4:
		APB1_prescaler = 4;
		break;
	case APBx_PRESCALER_8:
		APB1_prescaler = 8;
		break;
	case APBx_PRESCALER_16:
		APB1_prescaler = 16;
		break;
	}

	return APB1_prescaler;
}

uint8_t get_APB2_prescaler() {
	uint8_t bits = (7u << 13) & RCC->CFGR;
	uint16_t APB2_prescaler;

	if (!(bits & 4u)) {
		return 1;
	}

	switch (bits) {
	case APBx_PRESCALER_2:
		APB2_prescaler = 2;
		break;
	case APBx_PRESCALER_4:
		APB2_prescaler = 4;
		break;
	case APBx_PRESCALER_8:
		APB2_prescaler = 8;
		break;
	case APBx_PRESCALER_16:
		APB2_prescaler = 16;
		break;
	}

	return APB2_prescaler;
}

static uint8_t get_PLLM() {

	return RCC->PLLCFGR & 63u;
}

static uint16_t get_PLLN() {

	return RCC->PLLCFGR & (511u << 6);
}

static uint8_t get_PLLP() {
	uint8_t PLLP;

	switch (RCC->PLLCFGR & (3u << 16)) {
	case PLLP_2:
		PLLP = 2;
		break;
	case PLLP_4:
		PLLP = 4;
		break;
	case PLLP_6:
		PLLP = 6;
		break;
	case PLLP_8:
		PLLP = 8;
		break;
	}

	return PLLP;
}

static uint32_t calculate_PLL_clk(uint32_t source_clk, uint8_t PLLM,
		uint16_t PLLN, uint8_t PLLP) {

	return source_clk / PLLM * PLLN / PLLP;
}


void init_SYSCLK_HSE() {
	//HSE 8MHz
	//enable HSE
	RCC->CR |= 1u << 16;
	RCC->CR |= 1u << 18;
	select_clk_source(HSE);
}

void init_SYSCLK_PLL(uint8_t clk_source, uint8_t PLLM, uint16_t PLLN,
		uint8_t PLLP) {
	RCC->PLLCFGR = 0;

	RCC->PLLCFGR |= PLLM;
	RCC->PLLCFGR |= PLLN << 6;
	RCC->PLLCFGR |= PLLP << 16;

	uint32_t clock_value = calculate_PLL_clk(clk_source, PLLM, PLLN,
			get_PLLP(PLLP));
	printf("%d\n", (int) clock_value);

	if (clock_value > 60000000) {
		RCC->APB1ENR |= 1u << 28;
		PWR->CR |= PWR_VOS_SCALE_2 << 14;
		FLASH->ACR |= 2u;
	} else if (clock_value > 30000000) {
		FLASH->ACR |= 2u;
	}


	switch (clk_source) {
	case HSE:
		RCC->CR |= 1u << 18;
		RCC->CR |= 1u << 16;
		RCC->PLLCFGR |= 1u << 22;
		break;

	case HSI:
		RCC->CR |= 1u;
		break;
	}

	RCC->CR |= 1u << 24;

	select_clk_source(PLL);

	if (clk_source == HSE) {
		RCC->CR &= ~1u;
	}



}

void init_peripheral_prescalers(uint8_t AHB_prescaler, uint8_t APB1_prescaler,
		uint8_t APB2_prescaler) {
	RCC->CFGR |= AHB_prescaler << 4;
	RCC->CFGR |= APB1_prescaler << 10;
	RCC->CFGR |= APB2_prescaler << 13;
}

uint32_t get_SYSCLK() {

	uint8_t clk_source = 3u & RCC->CFGR;
	uint32_t clk_speed;

	switch (clk_source) {
	case HSI:
		clk_speed = 16000000;
		break;
	case HSE:
		clk_speed = 8000000;
		break;
	case PLL:

		if ((1u << 22) & RCC->PLLCFGR) {
			clk_speed = 8000000;
		} else {
			clk_speed = 16000000;
		}

		return calculate_PLL_clk(clk_speed, get_PLLM(), get_PLLN(), get_PLLP());

	}

	return clk_speed;
}

uint32_t get_AHB_clock() {

	return get_SYSCLK() / get_AHB_prescaler();
}

uint32_t get_APB1_clock() {

	return get_AHB_clock() / get_APB1_prescaler();
}

uint32_t get_APB2_clock() {

	return get_AHB_clock() / get_APB2_prescaler();
}

