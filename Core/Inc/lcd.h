#ifndef __LCD_H
#define __LCD_H

#include "GPIO_Lib.h"

pin_type data0;
pin_type data1;
pin_type data2;
pin_type data3;
pin_type data4;
pin_type data5;
pin_type data6;
pin_type data7;
pin_type RS;
pin_type RW;
pin_type E;

typedef enum {
	instruction,
	data
} write_type;

pin_type data_pins[8];

void init_lcd(void);
void write_data_pins(uint8_t data);

#endif
