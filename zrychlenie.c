#include "zrychlenie.h"
#include "menu.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "language.h"
#include "definitions.h"
#include "keys.h"
#include "meranie_vzdialenosti_rychlosti.h"
#include <avr/pgmspace.h>
#include "input_int.h"




char mnu_zrychlenie(void)
{

	if (!menu_nr[1])
	{
#ifdef MPH
		zrychlenie_max=60;	
#endif
#ifndef MPH
		zrychlenie_max=100;	
#endif
		
		menu_nr[1]=1;
		zrychlenie_stav=1;
	}	


	lcd_putstring(PSTR(TXT_ZRYCHLENIE),2,0,0,M_COL_TXT,M_COL_BCK,2);
	lcd_putnr(zrychlenie_max, 0, ' ', 3, 146, 0, 0, M_COL_TXT, M_COL_BCK, 2);

	lcd_putstring(PSTR(TXT_CAS),2,46,1,COL_TXT_LCD2,M_COL_BCK,2);
//	lcd_putnr(zrychlenie_cas/100, 1, ' ', 3, 74, 36, 2, M_COL_TXT, M_COL_BCK, 2);
//	lcd_putstring(PSTR(TXT_S),160,50,1,COL_TXT_LCD2,M_COL_BCK,2);


	lcd_putnr(zrychlenie_cas/100, 1, ' ', 3, 82, 36, 2, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(TXT_S),168,54,0,COL_TXT_LCD2,M_COL_BCK,2);

	if (tlacitka()==2) return(1); 

	if (tlacitka()==1) 
	{
		if (tlacitka_long()) zrychlenie_max=input_int(146,0,0,3,zrychlenie_max,255);
		zrychlenie_stav=1;
		lcd_clr_dspl(M_COL_BCK,2);
	}


	return(0);
}

void zrychlenie(void)
{

	if (zrychlenie_stav==3) zrychlenie_cas++;
	if (zrychlenie_cas>59900) zrychlenie_stav=1;
	if (!TCCR2B)//  operácie sa vykonajú len keï sa nevstrekuje benzín
	{
		switch (zrychlenie_stav)
		{
			case 1:
				zrychlenie_tcnt_start=TCNT1;
				zrychlenie_cas=0;
				zrychlenie_rychlost=0;
				if (rychlost==0) zrychlenie_stav=2;
				break;
		
			case 2:
				if (TCNT1>zrychlenie_tcnt_start) zrychlenie_stav=3;
				break;

			case 3:
				zrychlenie_rychlost_old=zrychlenie_rychlost;
				if (zrychlenie_rychlost<rychlost) zrychlenie_rychlost=rychlost+0.82*(rychlost-zrychlenie_rychlost_old);
				else  zrychlenie_rychlost=rychlost;

				if (zrychlenie_rychlost>=zrychlenie_max)				
				{
					zrychlenie_stav=0;
					zrychlenie_cas=(zrychlenie_cas+(zrychlenie_max-zrychlenie_rychlost_old)*(dlzka_merania/(zrychlenie_rychlost-zrychlenie_rychlost_old)))-dlzka_merania;	//100
					if (max_zrychlenie>zrychlenie_cas/100)max_zrychlenie=zrychlenie_cas/100;
				}
		}
	}

}


