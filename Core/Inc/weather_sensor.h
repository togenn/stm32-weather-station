#ifndef __WEATHER_SENSOR_H
#define __WEATHER_SENSOR_H

#include <systick_IR_timer_lib.h>
#include "GPIO_Lib.h"

struct sensor_data {
	uint16_t temperature;
	uint16_t humidity;
};

void send_start_signal(pin_type* sensor_pin);
void read_response_signal(pin_type* sensor_pin);
struct sensor_data read_data(pin_type* sensor_pin);


#endif
