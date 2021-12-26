#ifndef __WEATHER_SENSOR_H
#define __WEATHER_SENSOR_H

#include "systick_lib.h"
#include "GPIO_Lib.h"

void send_start_signal(pin_type* sensor_pin);
void read_response_signal(pin_type* sensor_pin);
char* read_data(pin_type* sensor_pin);


#endif
