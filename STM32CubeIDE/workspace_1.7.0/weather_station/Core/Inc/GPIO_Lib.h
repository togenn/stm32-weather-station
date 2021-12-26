#ifndef __GPIO_LIB_H
#define __GPIO_LIB_H

#include "stm32f4xx.h"                  // Device header

#define pin0 0x1
#define pin1 0x2
#define pin2 0x4
#define pin3 0x8
#define pin4 0x10
#define pin5 0x20
#define pin6 0x40
#define pin7 0x80
#define pin8 0x100
#define pin9 0x200
#define pin10 0x400
#define pin11 0x800
#define pin12 0x1000
#define pin13 0x2000
#define pin14 0x4000
#define pin15 0x8000

#define input 0x0
#define output 0x1
#define alternate_function 0x2
#define analog 0x3

#define no_PUPD 0x0
#define PU 0x1
#define PD 0x2

typedef enum {
    LOW,
    HIGH
} pin_state;

typedef struct {
    GPIO_TypeDef* gpio;
    uint32_t pin_num;
    uint32_t mode;
    uint32_t PUPD;
} pin_type;

void GPIOA_enable_clock(void);
void GPIOB_enable_clock(void);
void GPIOC_enable_clock(void);
void GPIOD_enable_clock(void);
void GPIOE_enable_clock(void);
void GPIOH_enable_clock(void);

void init_pin(pin_type* pin, GPIO_TypeDef* _gpio, uint32_t _pin_num, uint32_t _mode, uint32_t PUPD);
void set_input(pin_type* pin);
void set_output(pin_type* pin);
pin_state write_pin(pin_type* pin, pin_state state);
pin_state read_pin(pin_type* pin);
pin_state toggle_pin(pin_type* pin);

#endif





