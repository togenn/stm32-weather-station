#include "systick_lib.h"
#include "systick_driver.h"

void delay(uint32_t ms) {
	systick_reg->LOAD |= 16000u - 1;
	systick_reg->CTRL |= 5u;

	for (int i = 0; i < ms; i++) {
		while (!(systick_reg->CTRL & (1u << 16u)));

	}

	systick_reg->CTRL = 0;
}

void delay_micros(uint32_t micros) {
	systick_reg->LOAD |= 16u - 1;
	systick_reg->CTRL |= 5u;

	for (int i = 0; i < micros; i++) {
			while (!(systick_reg->CTRL & (1u << 16u)));

		}

		systick_reg->CTRL = 0;
}
