#include "string_formatting.h"
#include <stdio.h>
#include <string.h>

static void int2string(uint16_t num, char *buffer) {

	sprintf(buffer, "%d", num);
}

void format_dht22_values(char *buffer, uint16_t value) {
	uint8_t decimal = value % 10;
	uint8_t integer = value / 10;

	char integer_str[3];
	int2string(integer, integer_str);
	integer_str[2] = '\0';

	char decimal_str[2];
	int2string(decimal, decimal_str);
	decimal_str[1] = '\0';

	char comma[] = ",";
	strcat(buffer, integer_str);
	strcat(buffer, comma);
	strcat(buffer, decimal_str);

}

void format_date_time(char *buffer, date_time_type *date_time) {
	char format[] = "%02d:%02d %02d/%02d/20%02d\n\r";
	sprintf(buffer, format, (int) date_time->hours, (int) date_time->minutes,
			(int) date_time->date,
			(int) date_time->month, (int) date_time->year);
}

