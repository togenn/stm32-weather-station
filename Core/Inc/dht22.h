#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#include "GPIO_Lib.h"

#define SENDING_DATA 0u
#define SENDING_DATA_INIT 5u
#define SLEEPING 1u
#define INITIALIZING_1 2u
#define INITIALIZING_2 3u
#define COOLDOWN 4u

struct dht22_data {
	uint16_t temperature;
	uint16_t humidity;
};

struct dht22_data dht22_data;

uint8_t dht_status;
int bits_read;

//sensor is connected to PA10
pin_type dht22;

void handle_delay_IT(void);
void handle_data_pin_IT(void);
void init_dht22();
uint8_t get_data(pin_type* pin);
void application_callback(void);


#endif
