/*
 * RTC.h
 *
 * Created: 15.09.2013 18:54:29
 *  Author: Jevgeni
 */ 


#ifndef RTC_H_
#define RTC_H_
#include <avr/io.h>


void initCalendar(void);
uint8_t setCurrentTimeIn24Format(uint8_t hour,uint8_t minute, uint8_t second);
uint8_t setCurrentDate(uint8_t date,uint8_t month, uint8_t year);
uint8_t getCurrentHour(void);
uint8_t getCurrentMinute(void);
uint8_t getCurrentSecond(void);
uint8_t getCurrentDate(void);
uint8_t getCurrentMonth(void);
uint8_t getCurrentYear(void);
char* getCurrentTimeString(void);
char* getCurrentDateString(void);

#endif /* RTC_H_ */