/*
 * RTC.h
 *
 *  Created on: 16 Dec 2021
 *      Author: peral
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include <stdint.h>

#define ALARM_A 0
#define ALARM_B 1

#define MASK_DISABLE 0
#define MASK_ENABLE 1

typedef enum {
	monday = 1, tuesday, wednesday, thurday, friday, saturday, sunday
} weekday;

typedef enum {
	format_24, format_12
} time_format;

typedef enum {
	AM, PM
} am_pm;

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t date;
	weekday day;
	uint8_t month;
	uint8_t year; //last two digits
	time_format time_format;
	am_pm am_pm;
} date_time_type;


//defines which units are used to trigger the alarm
//disable means unit is dont care
typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t date;
	uint8_t day;
} alarm_type;

void RTC_init(date_time_type *time);

date_time_type get_date_time();

void set_alarm(uint8_t alarm);

#endif /* INC_RTC_H_ */
