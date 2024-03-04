/*
 * 017_RTC_LCD.c
 *
 *  Created on: Mar 2, 2024
 *      Author: wyatt
 */

#include <stdio.h>
#include "ds1307.h"

/*
 * I2C1 Pins:
 * SCL --> PB8
 * SDA --> PB9
 * ALT Function Mode: 5
 */


// Helper Functions Prototypes
char* get_day_of_week(uint8_t day);


int main(void){

	RTC_time_t current_time;
	RTC_date_t current_date;

	printf("RTC test\n");

	if(ds1307_init()){
		printf("RTC Init Failed\n");
		while(1);
	}

	// Configure Date
	current_date.day = SUNDAY;
	current_date.date = 3;
	current_date.month = 3;
	current_date.year = 24;

	// Configure Time
	current_time.seconds = 41;
	current_time.minutes = 8;
	current_time.hours = 8;
	current_time.time_format = TIME_FORMAT_12HRS_PM;

	ds1307_set_current_date(&current_date);
	ds1307_set_current_time(&current_time);

	ds1307_get_current_date(&current_date);
	ds1307_get_current_time(&current_time);

	char *am_pm;
	if(current_time.time_format != TIME_FORMAT_24HRS){
		am_pm = (current_time.time_format) ? "PM" : "AM";
		printf("Current Time: %s %s\n", time_to_string(&current_time), am_pm); // 08:08:41 PM
	}else{
		// 24 Hours Format
		printf("Current Time: %s\n", time_to_string(&current_time)); // 20:08:41
	}

	printf("Current Date: %s <%s>\n", date_to_string(&current_date), get_day_of_week(current_date.day));


	while(1);

	return 0;
}



char* get_day_of_week(uint8_t day){
	char *days_list[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
	return days_list[day-1];
}


// hh:mm:ss
char* time_to_string(RTC_time_t *rtc_time){
	char buf[9];
	buf[2] = ':';
	buf[5] = ':';

	number_to_string(rtc_time->hours, buf);
}

char* date_to_string(RTC_date_t *rtc_date){

}








