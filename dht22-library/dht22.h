#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#include "GPIO_Lib.h"

#define SENDING_DATA 0u
#define INITIALIZING 1u
#define INITIALIZING_2 2u
#define SLEEPING 3u

uint16_t temperature_tmp;
uint16_t humidity_tmp;

uint8_t bits_read;

struct dht22_data {
	uint16_t temperature;
	uint16_t humidity;
};

struct dht22_data dht22_data;

uint8_t dht_status;


//init gpio and pin_num members before calling init_dht22()
pin_type dht22;

void dht22_handle_delay_IT(void);
void dht22_handle_data_pin_IT(void);

//init SYSTICK and TIM5 before using dht22
void init_dht22();

uint8_t dht22_get_data();
void dht22_get_data_and_wait();

//user definable
void dht22_application_callback(void);



#endif
