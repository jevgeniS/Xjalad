/*
 * Print.h
 *
 * Created: 16.09.2013 21:27:17
 *  Author: Jevgeni
 */ 

#ifndef __PRINT_H
#define __PRINT_H

#include <avr/io.h>

void print(const char * str);
void println(const char * str);
uint8_t printer_configured(void);
void printer_init(void);

#endif