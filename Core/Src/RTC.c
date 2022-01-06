/*
 * RTC.c
 *
 *  Created on: 29 Dec 2021
 *      Author: Toni
 */

#include "RTC.h"
#include "NVIC_lib.h"
#include "EXTI_lib.h"

static uint16_t bin2bcd(uint8_t bin) {
	uint8_t digit;
	uint8_t shift = 0;
	uint16_t bcd = 0;

	while (bin) {
		digit = bin % 10;
		bin /= 10;
		bcd |= (0xFu & digit) << (4 * shift++);
	}

	return bcd;
}

static uint8_t bcd2bin(uint16_t bcd) {

	uint8_t multiplier = 1;
	uint8_t bin = 0;

	while (bcd) {
		bin += (bcd & 0xFu) * multiplier;
		bcd >>= 4;
		multiplier *= 10;
	}

	return bin;
}

static void unlock_write_protection() {
	RTC->WPR = 0xCAu;
	RTC->WPR = 0x53u;

}

static void enable_write_protection() {
	RTC->WPR |= 0xFFu;

}

void RTC_init(date_time_type *time) {
	RCC->APB1ENR |= 1u << 28;
	PWR->CR |= 1u << 8;
	RCC->BDCR |= 1u << 15;

	unlock_write_protection();

	//configure LSE clock for RTC
	RCC->BDCR |= 1u;
	while (!(RCC->BDCR & 2u))
		;

	RCC->BDCR |= 1u << 8;

	//Set INIT bit to 1 in the RTC_ISR register to enter initialization mode
	RTC->ISR |= 1u << 7;

	//Poll INITF bit of in the RTC_ISR register. The initialization phase mode is entered when
	//INITF is set to 1
	while (!(RTC->ISR & (1u << 6)))
		;

	//configure date and time
	uint32_t time_tmp = 0;
	uint32_t date_tmp = 0;

	time_tmp |= 0x7Fu & bin2bcd(time->seconds);
	time_tmp |= (0x7Fu & bin2bcd(time->minutes)) << 8;
	time_tmp |= (0x3Fu & bin2bcd(time->hours)) << 16;

	if (time->time_format == format_12) {
		time_tmp |= 1u << 6;
		time_tmp |= time->am_pm << 22;
	}

	date_tmp |= 0x3Fu & bin2bcd(time->date);
	date_tmp |= (0x1Fu & bin2bcd(time->month)) << 8;
	date_tmp |= (0x7u & time->day) << 13;
	date_tmp |= (0xFFu & bin2bcd(time->year)) << 16;

	RTC->TR = time_tmp;
	RTC->DR = date_tmp;

	//exit the initialization mode
	RTC->ISR &= ~(1u << 7);

	enable_write_protection();

}

date_time_type get_date_time() {

	date_time_type date_time;

	date_time.time_format = (RTC->CR >> 6) & 1u;
	date_time.am_pm = (RTC->TR >> 22) & 1u;

	date_time.seconds = bcd2bin(RTC->TR & 0x7Fu);
	date_time.minutes = bcd2bin((RTC->TR >> 8) & 0x7Fu);
	date_time.hours = bcd2bin((RTC->TR >> 16) & 0x3Fu);

	date_time.date = bcd2bin(RTC->DR & 0x3Fu);
	date_time.month = bcd2bin((RTC->DR >> 8) & 0x1Fu);
	date_time.year = bcd2bin((RTC->DR >> 16) & 0xFFu);

	date_time.day = ((RTC->DR >> 13) & 0x7u);

	return date_time;
}

void set_alarm(date_time_type *time, alarm_mask_type *alarm_mask,
		alarm_type alarm) {

	enable_IR(RTC_Alarm_IRQn);
	enable_EXTI(17, EXTI_RE);

	uint32_t RTC_base = 0x40002800u;

	volatile uint32_t *alarm_reg = (uint32_t*) (
			alarm ? RTC_base + 0x20 : RTC_base + 0x1C);

	unlock_write_protection();
	uint8_t enable_alarm = alarm ? 9 : 8;
	RTC->CR &= ~(1u << enable_alarm);

	uint8_t ready_flag = alarm ? 1 : 0;
	while (!((RTC->ISR >> ready_flag) & 1u))
		;

	*alarm_reg = 0;

	*alarm_reg |= (bin2bcd(time->seconds) | (~(alarm_mask->seconds) << 7))
			& 0xFF;

	*alarm_reg |= ((bin2bcd(time->minutes) | (~(alarm_mask->minutes) << 7))
			& 0xFF) << 8;

	*alarm_reg |= ((bin2bcd(time->hours) | (~(alarm_mask->hours) << 7)
			| (time->am_pm << 6)) & 0xFF) << 16;

	uint8_t selection = alarm_mask->weekday ? 1 : 0;
	uint8_t mask = ~(alarm_mask->weekday) | ~(alarm_mask->date);
	*alarm_reg |= ((bin2bcd(time->hours) | (mask << 7) | (selection << 6))
			& 0xFF) << 24;

	RTC->CR |= 1u << enable_alarm;

	uint8_t enable_alarm_interrupt = alarm ? 13 : 12;
	RTC->CR |= 1u << enable_alarm_interrupt;

	enable_write_protection();

}

void disable_alarm(alarm_type alarm) {

	unlock_write_protection();

	uint8_t disable_alarm = alarm ? 9 : 8;
	RTC->CR &= ~(1u << disable_alarm);

	uint8_t enable_alarm_interrupt = alarm ? 13 : 12;
	RTC->CR &= ~(1u << enable_alarm_interrupt);

	disable_IR(RTC_Alarm_IRQn);
	disable_EXTI(17);

	enable_write_protection();
}

