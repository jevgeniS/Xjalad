
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "lib/SPI_routines.h"
#include "lib/SD_routines.h"

#include "lib/FAT32.h"
#include "lib/Print.h"

#define LED0 PB7


 
 

 
void toggleLed(){
	// Set PE6 (LED) as output
	DDRB |= _BV(LED0);
	PORTB ^= _BV(LED0); // toggle LED pin
}


void port_init(void)
{
	
	//SPI
	//SS,SCLK,MOSI to outputs
	DDRB=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2);
	// Set PB3 (MISO) as input
	DDRB &= ~(1 << PORTB3);
}




int main() {
	// Remove CLKDIV8
	CLKPR = 0x80;
	CLKPR = 0x00;
	printer_init();
	// DISABLE JTAG - take control of F port
	MCUCR = _BV(JTD);
	MCUCR = _BV(JTD);
 	while (!printer_configured()) /* wait */ ;
	initCalendar();
	
	
	//setCurrentTimeIn24Format(23,21,30);
	setCurrentDate(15,9,13);
	
	
	 port_init();
	 spi_init();
	 
	 unsigned char option, error, data, FAT32_active;
	 unsigned int i;
	 unsigned char fileName[13];
	cardType = 0;
	 
	for (i=0; i<10; i++)
	{
		error = SD_init();
		if(!error) break;
	}
	
	toggleLed();
	if(error)
	{
		/*
		if(error == 1) ;
		if(error == 2) transmitString_F(PSTR("Card Initialization failed.."));
*/
		while(1);  //wait here forever if error in SD init
	}
	_delay_ms(3000);
	toggleLed();

	
	switch (cardType)
	{
		case 1:println("Standard Capacity Card (Ver 1.x) Detected!");
		break;
		case 2:println("High Capacity Card Detected!");
		break;
		case 3:println("Standard Capacity Card (Ver 2.x) Detected!");
		break;
		default:println("Unknown SD Card Detected!");
		break;
	}
	
	SPI_HIGH_SPEED;	//SCK - 4 MHz
	_delay_ms(1);   //some delay

	
	FAT32_active = 1;
	error = getBootSectorData (); //read boot sector and keep necessary data in global variables
	if(error)
	{
		
		println("FAT32 not found!");  //FAT32 incompatible drive
		FAT32_active = 0;
	}
	println("Trying to write to file");
	//struct dir_Structure *dir; 
	//dir=findFiles(GET_LIST,0);
	writeTextToFile("testData","TEST");
	//findFiles(GET_LIST,0);
	
	
	while(1)
	{
		
		
		_delay_ms(1000); // sleep 1 second
		
	}
 
}