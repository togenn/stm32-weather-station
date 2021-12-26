#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#include "GPIO_Lib.h"

#define SENDING_DATA 0u
#define INITIALIZING 1u
#define INITIALIZING_2 2u
#define SLEEPING 3u


struct dht22_data {
	uint16_t temperature;
	uint16_t humidity;
};

struct dht22_data dht22_data;

uint8_t dht_status;

//sensor is connected to PA10
pin_type dht22;

void dht22_handle_delay_IT(void);
void dht22_handle_data_pin_IT(void);
void init_dht22();

uint8_t dht22_get_data();
void dht22_get_data_and_wait();

//user definable
void dht22_application_callback(void);


#endif
