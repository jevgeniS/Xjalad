/*
 * Print.c
 *
 * Created: 16.09.2013 21:32:54
 *  Author: Jevgeni
 */ 


#include "usb_serial.h"
#include "Print.h"

void print(const char * str){
	while (*str) {
		usb_serial_putchar(*str);
		str++;
	}
	
}


 void println(const char *str) {
	 while (*str) {
		 usb_serial_putchar(*str);
		 str++;
	 }
	 usb_serial_putchar('\n');
	 usb_serial_putchar('\r');
 }


uint8_t printer_configured(void)
{
	return usb_configured();
}

void printer_init(void){
	
	usb_init();
}