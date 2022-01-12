#ifndef __GPIO_LIB_H
#define __GPIO_LIB_H

#include "stm32f4xx.h"

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

typedef enum {
    INPUT,
    OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
} pin_mode;

typedef enum {
    PP,
    OD
} PP_OD_type;

typedef enum {
	NO_PULL,
    PULL_UP,
    PULL_DOWN
} PUSH_PULL_type;

typedef struct {
    GPIO_TypeDef* gpio;
    uint8_t pin_num;
    pin_mode mode;
    PP_OD_type PP_OD;
    PUSH_PULL_type push_pull;
    uint8_t AF_num;
} pin_type;


void init_pin(pin_type* pin);
void change_mode(pin_type* pin);

pin_state write_pin(pin_type* pin, pin_state state);
pin_state read_pin(pin_type* pin);
pin_state toggle_pin(pin_type* pin);

#endif





