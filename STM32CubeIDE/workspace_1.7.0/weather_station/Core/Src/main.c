#include "GPIO_Lib.h"
#include "systick_lib.h"
#include "weather_sensor.h"
#include <stdio.h>

int main(void) {

	printf("hello\n");
	GPIOA_enable_clock();

	pin_type internal_led_pin;
	init_pin(&internal_led_pin, GPIOA, 5, output, no_PUPD);

	pin_type weather_sensor;
	init_pin(&weather_sensor, GPIOA, 10, input, PU);

	send_start_signal(&weather_sensor);
	read_response_signal(&weather_sensor);

	char* data = read_data(&weather_sensor);

	for (uint32_t i = 0; i < 5; i++) {
		printf("%d\n", (int) *data);
		data++;
	}


	while (1) {

		delay(1000);
		toggle_pin(&internal_led_pin);




	}



}
