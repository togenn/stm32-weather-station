#include "weather_sensor.h"
#include <stdio.h>

void send_start_signal(pin_type *sensor_pin) {
	set_output(sensor_pin);

	write_pin(sensor_pin, LOW);
	delay_micros(1200);

	write_pin(sensor_pin, HIGH);
	delay_micros(20);

	set_input(sensor_pin);
}

void read_response_signal(pin_type *sensor_pin) {

	while (!read_pin(sensor_pin));
	while (read_pin(sensor_pin));
}

char* read_data(pin_type *sensor_pin) {

	static char data[5];

	for (uint32_t i = 0; i < 5; i++) {

		char bits = 0;
		for (uint32_t j = 0; j < 8; j++) {
			while (!read_pin(sensor_pin));

			uint32_t counter = 0;
			while (read_pin(sensor_pin)) {
				delay_micros(10);
				counter++;
			}

			int bit = counter < 4 ? 0 : 1;
			//printf("%d\n", bit);
			bits |= (bit << j);
		}

		data[i] = bits;

	}

	return data;
}
