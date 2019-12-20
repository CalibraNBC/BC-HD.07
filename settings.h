#ifndef _settings_
#define _settings_
#include "bit_operations.h"
#include <avr/io.h>


#define HW09							//definícia hardvéru (HW02, HW08, HW08S65, HW09)
#define LIS302DL
#define LOGO_CZ


#define S65_LANG_DE 	 		//Jazyk	(SK, CZ, EN, UK, NOR, PLN, BR, BR1, IT, DE, HU, RO, RU, SP, BU, FR, EST, PORT, AUS, NL, FIN)
#define PODP_EE 			4
//#define DEVELOP					//vkladá funcie pre vývoj
//#define SENZ_SKODA

#define AS_TIMER_KM			1200				//Nastavenie dåžky merania aktuálnej spotreby za jazdy
#define AS_TIMER_H			1000				//Nastavenie dåžky merania aktuálnej pri stání

 
 
#ifdef HW09
//-----------------Nastavenie portov----------------------

	#define LCD_CS1_DISABLE()	(SetBit(PORTD,7))
	#define LCD_CS2_DISABLE()	(SetBit(PORTD,4))
	#define	LCD_CS1_ENABLE()		(ClrBit(PORTD,7))
	#define	LCD_CS2_ENABLE()		(ClrBit(PORTD,4))


	#define LCD_RST_DISABLE() (SetBit(PORTD,5))
	#define LCD_RST_ENABLE()  (ClrBit(PORTD,5))

	#define LCD_RS_DISABLE()  (SetBit(PORTD,6))
	#define LCD_RS_ENABLE()   (ClrBit(PORTD,6))


	#define NAPATIE					7
	#define TEPLOTA					6
	#define PALIVO					5
	#define TEPLOTABC 			0
	#define IN_OUT_1 				1
	#define IN_OUT_2 				2
	#define IN_OUT_3 				4
	#define PODSVIETENIE		3

	#define BACKLIGHT_ON 		(SetBit(PORTA,3))
	#define BACKLIGHT_OFF 	(ClrBit(PORTA,3))
	#define BACKLIGHT_CHCK 	(ChckBit(PORTA,3))


	#define MEASURE_BCK_ON  	(ClrBit(DDRA,3))
	#define MEASURE_BCK_OFF  	(SetBit(DDRA,3))



	#define BUZZER 			(ChckBit(PINB,4))
	#define BUZZER_ON 	(SetBit(PORTB,4))
	#define BUZZER_OFF 	(ClrBit(PORTB,4))


	//----------------Definícia tlacitiek----------------------------
	#define TLACITKO_START		(!(ChckBit(PINC,6)))
	#define TLACITKO_STOP		(!(ChckBit(PINC,7)))
	#define POWER_OFF			(!(ChckBit(PINB,0)))

//---------------------------------------------------------

	#define AD_REF	0x40		//výber referenèného zdroja pre AD prevodník

	#define PORT_A	0x08
	#define DDR_A		0x08
	#define PORT_B	0x00
	#define DDR_B		0xF0
	#define PORT_C	0xC0
	#define DDR_C		0x00
	#define PORT_D	0xF0
	#define DDR_D		0xF0

#endif


#ifdef HW08S65
//-----------------Nastavenie portov----------------------

	#define LCD_CS1_DISABLE()	(SetBit(PORTD,3))
	#define LCD_CS2_DISABLE()	(SetBit(PORTD,0))
	#define	LCD_CS1_ENABLE()		(ClrBit(PORTD,3))
	#define	LCD_CS2_ENABLE()		(ClrBit(PORTD,0))


	#define LCD_RST_DISABLE() (SetBit(PORTD,1))
	#define LCD_RST_ENABLE()  (ClrBit(PORTD,1))

	#define LCD_RS_DISABLE()  (SetBit(PORTD,2))
	#define LCD_RS_ENABLE()   (ClrBit(PORTD,2))


	#define NAPATIE					7
	#define TEPLOTA					6
	#define PALIVO					5
	#define TEPLOTABC 			0
	#define IN_OUT_1 				1
	#define IN_OUT_2 				2
	#define IN_OUT_3 				4
	#define PODSVIETENIE		3

	#define BACKLIGHT_ON 		(SetBit(PORTA,3))
	#define BACKLIGHT_OFF 	(ClrBit(PORTA,3))
	#define BACKLIGHT_CHCK 	(ChckBit(PORTA,3))


	#define MEASURE_BCK_ON  	(ClrBit(DDRA,3))
	#define MEASURE_BCK_OFF  	(SetBit(DDRA,3))



	#define BUZZER 			(ChckBit(PINB,4))
	#define BUZZER_ON 	(SetBit(PORTB,4))
	#define BUZZER_OFF 	(ClrBit(PORTB,4))


	//----------------Definícia tlacitiek----------------------------
	#define TLACITKO_START		(!(ChckBit(PINC,6)))
	#define TLACITKO_STOP		(!(ChckBit(PINC,7)))
	#define POWER_OFF			(!(ChckBit(PINB,0)))

//---------------------------------------------------------

	#define AD_REF	0x40		//výber referenèného zdroja pre AD prevodník

	#define PORT_A	0x08
	#define DDR_A		0x08
	#define PORT_B	0x00
	#define DDR_B		0xF0
	#define PORT_C	0xC0
	#define DDR_C		0x00
	#define PORT_D	0x00
	#define DDR_D		0xFF

#endif

#endif
