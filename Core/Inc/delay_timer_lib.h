/*
 * timer_lib.h
 *
 *  Created on: Dec 5, 2021
 *      Author: toni
 */
#define OK 0
#define OF_ERROR 1

#ifndef INC_DELAY_TIMER_LIB_H_
#define INC_DELAY_TIMER_LIB_H_

#include "stm32f4xx.h"

void init_timer(TIM_TypeDef* timer, uint16_t prescaler);

uint8_t delay(uint32_t ms, TIM_TypeDef *timer);
uint8_t delay_micros(uint32_t micros);

#endif /* INC_DELAY_TIMER_LIB_H_ */
