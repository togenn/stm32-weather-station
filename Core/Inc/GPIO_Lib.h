#ifndef __GPIO_LIB_H
#define __GPIO_LIB_H

#define STM32F401xx
#include "stm32f4xx.h"                  // Device header

#define no_PUPD 0x0
#define PU 0x1
#define PD 0x2

#define PP 0x0
#define OD 0x1

// pin modes
#define INPUT_NO_PUPD 0
#define INPUT_PU 1
#define INPUT_PD 2

#define OUTPUT_PP 3
#define OUTPUT_OD 4

#define alternate_function 5


#define GPIOA_CLOCK_EN 0x1u
#define GPIOB_CLOCK_EN 0x2u
#define GPIOC_CLOCK_EN 0x4u
#define GPIOD_CLOCK_EN 0x8u
#define GPIOE_CLOCK_EN 0x10u
#define GPIOH_CLOCK_EN 0x80u


typedef enum {
    LOW,
    HIGH
} pin_state;

typedef struct {
    GPIO_TypeDef* gpio;
    uint32_t pin_num;
} pin_type;


void init_pin(pin_type* pin, GPIO_TypeDef* _gpio, uint8_t pin_num, uint8_t _mode);
void set_input(pin_type* pin, uint8_t mode);
void set_output(pin_type* pin, uint8_t mode);
void set_AF_num(pin_type* pin, uint8_t num);
pin_state write_pin(pin_type* pin, pin_state state);
pin_state read_pin(pin_type* pin);
pin_state toggle_pin(pin_type* pin);

#endif





