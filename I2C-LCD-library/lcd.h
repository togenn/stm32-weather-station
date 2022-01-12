#ifndef __LCD_LIB_H
#define __LCD_LIB_H

#include "I2C_lib.h"

#define LCD_CONTROL_INSTRUCTION 12u
#define LCD_CONTROL_DATA 13u

typedef enum {
	instruction,
	data
} LCD_data_type;

void LCD_init(I2C_handle_type* I2C_handle);

void LCD_set_cursor(I2C_handle_type* I2C_handle, uint8_t row, uint8_t column);

void LCD_write(I2C_handle_type *I2C_handle, char *text, uint8_t len,  uint8_t row, uint8_t column);

#endif
