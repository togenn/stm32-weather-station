/*
 * clocks_lib.h
 *
 *  Created on: Nov 30, 2021
 *      Author: toni
 */

#ifndef INC_CLOCKS_LIB_H_
#define INC_CLOCKS_LIB_H_

void init_SYSCLK();
void init_SYSCLK_PLL();
void init_peripheral_prescalers();

uint32_t get_SYSCLK();
uint32_t get_AHB_clock();
uint32_t get_APB1_clock();
uint32_t get_APB2_clock();


#endif /* INC_CLOCKS_LIB_H_ */
