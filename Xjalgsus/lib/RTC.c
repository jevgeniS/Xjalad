/*
 * RTC.c
 *
 * Created: 15.09.2013 18:51:31
 *  Author: Jevgeni
 */ 



#include <stdio.h>
#include <string.h>
#include "ds1307.h"
#include "I2C.h"
#include "RTC.h"

 
 void initCalendar(void){
	 
	 I2CInit();
	 
	 
 }

 uint8_t setCurrentTimeIn24Format(uint8_t hour,uint8_t minute, uint8_t second){
	 
	 uint8_t hourOnes,hourTens,minuteOnes,minuteTens,secondOnes,secondTens;
	 
	 hourOnes=hour%10;
	 hourTens=(hour-hourOnes)/10;
	 minuteOnes=minute%10;
	 minuteTens=(minute-minuteOnes)/10;
	 secondOnes=second%10;
	 secondTens=(second-secondOnes)/10;
	 
	 hour=(hourOnes)|(hourTens<<4);
	 minute=(minuteOnes)|(minuteTens<<4);
	 second=(secondOnes)|(secondTens<<4);
	 

	 return (
	 DS1307Write(0x02,hour)&&
	 DS1307Write(0x01,minute)&&
	 DS1307Write(0x00,second)
	 );
 }

 uint8_t setCurrentDate(uint8_t date,uint8_t month, uint8_t year){
	 
	 uint8_t dateOnes,dateTens,monthOnes,monthTens,yearOnes,yearTens;
	 
	 dateOnes=date%10;
	 dateTens=(date-dateOnes)/10;
	 monthOnes=month%10;
	 monthTens=(month-monthOnes)/10;
	 yearOnes=year%10;
	 yearTens=(year-yearOnes)/10;
	 
	 date=(dateOnes)|(dateTens<<4);
	 month=(monthOnes)|(monthTens<<4);
	 year=(yearOnes)|(yearTens<<4);
	 

	 return (
	 DS1307Write(0x04,date)&&
	 DS1307Write(0x05,month)&&
	 DS1307Write(0x06,year)
	 );
 }

 uint8_t getCurrentHour(void){
	 uint8_t hour;
	 uint8_t data;
	 DS1307Read(0x02,&data);
	 hour=(data & 0b00001111);
	 hour+=((data & 0b00110000)>>4)*10;
	 return hour;
 }

 uint8_t getCurrentMinute(void){
	 uint8_t minute;
	 uint8_t data;
	 DS1307Read(0x01,&data);
	 minute=(data & 0b00001111);
	 minute+=((data & 0b01110000)>>4)*10;
	 return minute;
 }

 uint8_t getCurrentSecond(void){
	 uint8_t second;
	 uint8_t data;
	 DS1307Read(0x00,&data);
	 second=(data & 0b00001111);
	 second+=((data & 0b01110000)>>4)*10;
	 return second;
 }

 uint8_t getCurrentDate(void){
	 uint8_t date;
	 uint8_t data;
	 DS1307Read(0x04,&data);
	 date=(data & 0b00001111);
	 date+=((data & 0b00110000)>>4)*10;
	 return date;
 }

 uint8_t getCurrentMonth(void){
	 uint8_t month;
	 uint8_t data;
	 DS1307Read(0x05,&data);
	 month=(data & 0b00001111);
	 month+=((data & 0b00010000)>>4)*10;
	 return month;
 }


 uint8_t getCurrentYear(void){
	 uint8_t year;
	 uint8_t data;
	 DS1307Read(0x06,&data);
	 year=(data & 0b00001111);
	 year+=((data & 0b11110000)>>4)*10;
	 return year;
 }


 char* getCurrentTimeString(void){
	 char time[12];	//hh:mm:ss AM/PM
	 char temp[2];
	 
	 sprintf(temp, "%d", getCurrentHour());
	 strcpy(time,temp);
	 strcat(time,":");
	 sprintf(temp, "%d", getCurrentMinute());
	 strcat(time,temp);
	 strcat(time,":");
	 sprintf(temp, "%d", getCurrentSecond());
	 strcat(time,temp);
	 
	 // fix that
	 return time;
 }

 char* getCurrentDateString(void){
	 char time[12];	//dd:MM:yy AM/PM
	 char temp[2];
	 
	 sprintf(temp, "%d", getCurrentDate());
	 strcpy(time,temp);
	 strcat(time,"-");
	 sprintf(temp, "%d", getCurrentMonth());
	 strcat(time,temp);
	 strcat(time,"-");
	 sprintf(temp, "%d", getCurrentYear());
	 strcat(time,temp);
	 
	 //fix that
	 return time;
 }

