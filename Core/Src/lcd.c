#include <systick_IR_timer_lib.h>
#include "lcd.h"

void init_lcd() {

	init_pin(&data0, GPIOA, 5, OUTPUT_PP);
	init_pin(&data1, GPIOA, 6, OUTPUT_PP);
	init_pin(&data2, GPIOA, 7, OUTPUT_PP);
	init_pin(&data3, GPIOB, 6, OUTPUT_PP);
	init_pin(&data4, GPIOB, 10, OUTPUT_PP);
	init_pin(&data5, GPIOB, 4, OUTPUT_PP);
	init_pin(&data6, GPIOB, 5, OUTPUT_PP);
	init_pin(&data7, GPIOB, 3, OUTPUT_PP);
	init_pin(&RS, GPIOB, 8, OUTPUT_PP);
	//init_pin(&RW, GPIOA, 6, output, no_PUPD);
	init_pin(&E, GPIOB, 9, OUTPUT_PP);

	data_pins[0] = data0;
	data_pins[1] = data1;
	data_pins[2] = data2;
	data_pins[3] = data3;
	data_pins[4] = data4;
	data_pins[5] = data5;
	data_pins[6] = data6;
	data_pins[7] = data7;

	/*
	 delay(20);

	 write_data_pins(60u);

	 delay(5);

	 write_data_pins(60u);

	 delay_micros(150);

	 write_data_pins(60u);

	 delay(50);

	 write_data_pins(1u);
	 */

}

void write_data_pins(uint8_t data) {
	write_pin(&RS, LOW);
	write_pin(&E, LOW);
	delay(10);

	for (int i = 0; i < 8; i++) {
		write_pin(&(data_pins[i]), (data >> i) & 0x01);
		delay(1);
	}

	write_pin(&E, HIGH);
	delay(500);
	write_pin(&E, LOW);
}

