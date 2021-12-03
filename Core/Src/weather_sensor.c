#include "weather_sensor.h"
#include <stdio.h>

void send_start_signal(pin_type *sensor_pin) {
	set_output(sensor_pin, OUTPUT_PP);

	write_pin(sensor_pin, LOW);
	delay_micros(1200);

	write_pin(sensor_pin, HIGH);
	delay_micros(20);

	set_input(sensor_pin, INPUT_PU);
}

void read_response_signal(pin_type *sensor_pin) {

	while (!read_pin(sensor_pin));
	while (read_pin(sensor_pin));
}

struct sensor_data read_data(pin_type *sensor_pin) {
	struct sensor_data data;

	send_start_signal(sensor_pin);
	read_response_signal(sensor_pin);


	for (uint32_t i = 0; i < 2; i++) {

		uint16_t bits = 0;
		for (uint32_t j = 0; j < 16; j++) {
			while (!read_pin(sensor_pin));

			delay_micros(40);

			if (read_pin(sensor_pin)) {
				bits |= (1u << (15u - j));
				while(read_pin(sensor_pin));
			}
		}

		if (i) {
			data.temperature = bits;
		} else {
			data.humidity = bits;
		}

	}

	return data;
}
