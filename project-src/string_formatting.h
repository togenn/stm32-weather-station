#ifndef __STRING_FORMATTING_H
#define __STRING_FORMATTING_H

#include "stdint.h"
#include "RTC.h"

format_dht22_values(char *buffer, uint16_t value);
format_date_time(char *buffer, date_time_type *date_time);

#endif
