#include "lcd_s65_ls020.h"
#include "beep.h"
#include "logo.h"
#include "variables.h"
#include "delay.h"
#include <avr/pgmspace.h>
#include "language.h"


void logo(char lcd)
{
	unsigned int a,b;


	lcd_clr_dspl(M_COL_BCK,2);


#ifdef LOGO_CONCEPT
//	lcd_put_bw_picture(LOGO_CONCEPT_S,(176-LOGO_CONCEPT_X)/2,(132-LOGO_CONCEPT_Y)/2,1 ,LOGO_CONCEPT_X,LOGO_CONCEPT_Y,M_COL_TXT,M_COL_BCK,2); 
#endif

#ifdef LOGO_CZ
	lcd_put_bw_picture(LOGO_CZ_S,(176-LOGO_CZ_X)/2,(132-LOGO_CZ_Y)/2,1 ,LOGO_CZ_X,LOGO_CZ_Y,M_COL_TXT,M_COL_BCK,2); 
#endif

	for (a=0;a<=9;a++) lcd_putchar(nick[a],15+(a*16),70,1,M_COL_TXT,M_COL_BCK,1);;

//	lcd_on(2);
	delay1s();		


#ifdef LOGO_CONCEPT
	for (a=0;a<=176;a++)
	{
		lcd_area(a, 0, a, 134, 2);
		for(b=0;b<134;b++) lcd_sendd(M_COL_BCK, 2);
		lcd_scroll(176-a, 2); 
		_delay_ms(10);
		if (motor_on&&!POWER_OFF) a=177;
	}
#endif


#ifdef LOGO_CZ
#ifndef LCD_MIRROR
	if(lcd_type==1)
	{
		for (a=0;a<=176;a++)
		{
			lcd_area(176-a, 0, 176-a, 134, 2);
			for(b=0;b<134;b++) lcd_sendd(M_COL_BCK, 2);
			lcd_scroll(a, 2); 
			_delay_ms(10);
			if (motor_on&&!POWER_OFF) a=177;
		}
	}
	else if(lcd_type==2)
	{
		lcd_scroll_set(0,176, 3, 2);
		for (a=0;a<=174;a++)
		{
//			lcd_area(0, 0, 1, 134, 2);
//			lcd_sendc(0x5C,0x00, lcd);
//			for(b=0;b<134;b++) lcd_sendd(WHITE, 2);
			obdlznik(176-a,0,1,134,M_COL_BCK);
			lcd_scroll(a, 2);
			_delay_ms(10);
		}
		lcd_scroll(0, 2);

	}
#endif

#ifdef LCD_MIRROR
	for (a=0;a<=176;a++)
	{
		lcd_area(176-a, 0, 176-a, 134, 2);
		for(b=0;b<134;b++) lcd_sendd(M_COL_BCK, 2);
		lcd_scroll(176-a, 2); 
		_delay_ms(10);
		if (motor_on&&!POWER_OFF) a=177;
	}
#endif
#endif

	lcd_scroll(0, 2);
	lcd_clr_dspl(M_COL_BCK,1);
	lcd_clr_dspl(M_COL_BCK,2);

}
