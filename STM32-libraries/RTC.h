/*
 * RTC.h
 *
 *  Created on: 16 Dec 2021
 *      Author: peral
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include <stdint.h>
#include "stm32f4xx.h"

typedef enum {
	alarm_A,
	alarm_B
} alarm_type;

typedef enum {
	mask_disable,
	mask_enable
} mask_type;

typedef enum {
	monday = 1, tuesday, wednesday, thursday, friday, saturday, sunday
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
	uint8_t weekday;
} alarm_mask_type;

void RTC_init(date_time_type *time);

date_time_type get_date_time();


//handle interrupt in RTC_Alarm_IRQHandler
void set_alarm(date_time_type* time, alarm_mask_type* alarm_mask, alarm_type alarm);
void disable_alarm(alarm_type alarm);

void unlock_write_protection();
void enable_write_protection();


#endif /* INC_RTC_H_ */
