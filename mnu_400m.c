#include "mnu_400m.h"
#include "menu.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "language.h"
#include "definitions.h"
#include "keys.h"
#include "meranie_vzdialenosti_rychlosti.h"
#include <avr/pgmspace.h>
#include "input_int.h"




char mnu_400m(void)
{
	if (!menu_nr[1])
	{
#ifdef MPH
		meranie_400m_max=25;	
#endif
#ifndef MPH
		meranie_400m_max=40;	
#endif
		menu_nr[1]=1;
		meranie_400m_stav=1;
	}	

//	lcd_putnr((km-meranie_400m_km)*10, 0, ' ', 4, 10, 30, 0, M_COL_TXT, M_COL_BCK, 2);

	lcd_putstring(PSTR(TXT_400M),2,0,0,M_COL_TXT,M_COL_BCK,2);
#ifndef MPH
	lcd_putnr(meranie_400m_max*10, 0, ' ', 4, 136, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(TXT_M),168,0,0,COL_TXT_LCD2,M_COL_BCK,2);
#endif
#ifdef MPH
	lcd_putnr(meranie_400m_max, 2, ' ', 3, 140, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(TXT_KM),168,0,0,COL_TXT_LCD2,M_COL_BCK,2);
#endif

	lcd_putstring(PSTR(TXT_CAS),2,46,1,COL_TXT_LCD2,M_COL_BCK,2);
//	lcd_putnr(meranie_400m_cas/100, 1, ' ', 3, 74, 36, 2, M_COL_TXT, M_COL_BCK, 2);
//	lcd_putstring(PSTR(TXT_S),160,48,1,COL_TXT_LCD2,M_COL_BCK,2);

	lcd_putnr(meranie_400m_cas/100, 1, ' ', 3, 82, 36, 2, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(TXT_S),168,54,0,COL_TXT_LCD2,M_COL_BCK,2);

	lcd_putstring(PSTR(TXT_RYCHLOST),2,84,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(meranie_400m_rychlost, 0, ' ', 3, 104, 84, 1, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(TXT_KMHR),152,84,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR(TXT_KMSR),152,96,0,COL_TXT_LCD2,M_COL_BCK,2);

	if (tlacitka()==2) return(1); 

	if (tlacitka()==1) 
	{
#ifndef MPH
		if (tlacitka_long()) meranie_400m_max=input_int(136,0,0,3,meranie_400m_max,255);
#endif
#ifdef MPH
		unsigned int temp;
		if (tlacitka_long()) 
		{
			temp=meranie_400m_max-((meranie_400m_max/100)*100);
			meranie_400m_max=input_int(140,0,0,1,meranie_400m_max/100,2)*100;
			meranie_400m_max=meranie_400m_max + input_int(152,0,0,2,temp,99);
			if (meranie_400m_max>255) meranie_400m_max=255;
		}
#endif
		meranie_400m_stav=1;
		lcd_clr_dspl(M_COL_BCK,2);
	}


	return(0);
}


void meranie_400m(void)
{

	if (meranie_400m_stav==3) meranie_400m_cas++;
	if (meranie_400m_cas>59900) meranie_400m_stav=1;
	if (!TCCR2B)//  operácie sa vykonajú len keï sa nevstrekuje benzín
	{
		switch (meranie_400m_stav)
		{
			case 1:
				meranie_400m_tcnt_start=TCNT1;
				meranie_400m_cas=0;
				meranie_400m_km=km;
				meranie_400m_rychlost=0;
				if (rychlost==0) meranie_400m_stav=2;
				break;
		
			case 2:
				if (TCNT1>meranie_400m_tcnt_start) meranie_400m_stav=3;
				break;

			case 3:
				if (km-meranie_400m_km>=meranie_400m_max&&TCNT1>=meranie_400m_tcnt_start)
				{
					meranie_400m_stav=4;
					meranie_400m_rychlost=rychlost;
				}
				
		}
	}

}



