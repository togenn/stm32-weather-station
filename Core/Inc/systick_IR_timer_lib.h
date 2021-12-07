#ifndef __SYSTICK_LIB_H
#define __SYSTICK_LIB_H

#include <stdint.h>

#define OK 0
#define ERROR_OF 1

uint32_t MILLIS;
uint8_t MICROS;

/* Timer which causes interrupts
 * AHB1 clock needs to be divisible by 1MHz
 *
 */

void init_systick();


//ms < 16,777,216 / (AHB1_clock / 1000)
uint8_t IR_timer_millis(uint32_t ms);

//micros < 16,777,216 / (AHB1_clock / 1000000)
uint8_t IR_timer_micros(uint32_t micros);


#endif
