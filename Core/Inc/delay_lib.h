#ifndef __SYSTICK_LIB_H
#define __SYSTICK_LIB_H

#include <stdint.h>

#define MILLIS 42000u
#define MICROS 42u

#define POLLING 4u
#define IR 6u


void init_systick_IR();

void delay(uint32_t ms);
void delay_micros(uint32_t micros);

void delay_IR(uint32_t ms);
void delay_micros_IR(uint32_t micros);


#endif
