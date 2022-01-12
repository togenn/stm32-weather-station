#include "string_formatting.h"


static void int2string(uint16_t num, char *buffer) {

	sprintf(buffer, "%d", num);

}

void format_date_time(char *buffer, date_time_type *date_time) {
	char format[] = "%02d:%02d %02d/%02d/20%d";
	sprintf(buffer, format, (int) date_time->hours, (int) date_time->minutes,
			(int) date_time->date,
			(int) date_time->month, (int) date_time->year);
}

void format_dht22_values(char *buffer, uint16_t value) {
	uint8_t decimal = value % 10;
	uint8_t integer = value / 10;

	char integer_str[2];
	int2string(integer, integer_str);

	char decimal_str[1];
	int2string(decimal, decimal_str);

	char comma[] = ",";
	strncpy(buffer, strcat(strcat(integer_str, comma), decimal_str), 4);
	buffer[4] = '\0';
}