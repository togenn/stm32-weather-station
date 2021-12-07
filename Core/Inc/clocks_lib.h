/*
 * clocks_lib.h
 *
 *  Created on: Nov 30, 2021
 *      Author: toni
 */

#ifndef INC_CLOCKS_LIB_H_
#define INC_CLOCKS_LIB_H_

#include <stdint.h>

#define HSE 0u
#define HSI 1u
#define PLL 2u

#define PLLP_2 0u
#define PLLP_4 1u
#define PLLP_6 2u
#define PLLP_8 3u

#define AHB_PRESCALER_1 0u
#define AHB_PRESCALER_2 8u
#define AHB_PRESCALER_4 9u
#define AHB_PRESCALER_8 10u
#define AHB_PRESCALER_16 11u
#define AHB_PRESCALER_64 12u
#define AHB_PRESCALER_128 13u
#define AHB_PRESCALER_256 14u
#define AHB_PRESCALER_512 15u

#define APBx_PRESCALER_1 0u
#define APBx_PRESCALER_2 4u
#define APBx_PRESCALER_4 5u
#define APBx_PRESCALER_8 6u
#define APBx_PRESCALER_16 7u

#define PWR_VOS_SCALE_2 2u

void init_SYSCLK_HSE();
void init_SYSCLK_PLL(uint8_t clk_source, uint8_t PLLM, uint16_t PLLN,
		uint8_t PLLP);
void init_peripheral_prescalers(uint8_t AHB_prescaler, uint8_t APB1_prescaler,
		uint8_t APB2_prescaler);

uint32_t get_SYSCLK();
uint32_t get_AHB_clock();
uint32_t get_APB1_clock();
uint32_t get_APB2_clock();

uint8_t get_APB1_prescaler();
uint8_t get_APB2_prescaler();

#endif /* INC_CLOCKS_LIB_H_ */
