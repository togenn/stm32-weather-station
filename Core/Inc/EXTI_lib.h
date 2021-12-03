/*
 * EXTI_lib.h
 *
 *  Created on: Nov 29, 2021
 *      Author: toni
 */

#ifndef INC_EXTI_LIB_H_
#define INC_EXTI_LIB_H_

#include "stm32f4xx.h"

#define EXTI_GPIOA 0
#define EXTI_GPIOB 1u
#define EXTI_GPIOC 2u
#define EXTI_GPIOD 3u
#define EXTI_GPIOE 4u
#define EXTI_GPIOH 7u

#define EXTI_RE 0 //rising edge
#define EXTI_FE 1 // falling edge
#define EXTI_REFE 2 // rising and falling edge


//SYSCFG clock must be enabled

//gpio: EXTI_GPIOx
void enable_EXTI(uint8_t pin_num, uint8_t gpio, uint8_t edge);
void disable_EXTI(uint8_t pin_num);


#endif /* INC_EXTI_LIB_H_ */
