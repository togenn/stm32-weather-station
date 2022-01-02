/*
 * RTC.c
 *
 *  Created on: 29 Dec 2021
 *      Author: Toni
 */

#include "RTC.h"
#include "stm32f4xx.h"

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

void RTC_init(date_time_type *time) {
	RCC->APB1ENR |= 1u << 28;
	PWR->CR |= 1u << 8;
	RCC->BDCR |= 1u << 15;

	//unlock the write protection
	RTC->WPR = 0xCAu;
	RTC->WPR = 0x53u;

	//configure LSE clock for RTC
	RCC->BDCR |= 1u;
	while (!(RCC->BDCR & 2u));

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

}

date_time_type get_date_time() {

	date_time_type date_time;

	date_time.time_format = (RTC->CR & (1u << 6)) >> 6;
	date_time.am_pm = (RTC->TR & (1u << 22)) >> 22;

	date_time.seconds = bcd2bin(RTC->TR & 0x7Fu);
	date_time.minutes = bcd2bin((RTC->TR >> 8) & 0x7Fu);
	date_time.hours = bcd2bin((RTC->TR >> 16)  & 0x3Fu);

	date_time.date = bcd2bin(RTC->DR & 0x3Fu);
	date_time.month = bcd2bin((RTC->DR >> 8) & 0x1Fu);
	date_time.year = bcd2bin((RTC->DR >> 16) & 0xFFu);

	date_time.day = ((RTC->DR >> 13) & 0x7u);

	return date_time;
}

