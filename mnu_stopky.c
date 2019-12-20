#include "mnu_stopky.h"
#include "menu.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "language.h"
#include "definitions.h"
#include "keys.h"
#include "meranie_vzdialenosti_rychlosti.h"
#include <avr/pgmspace.h>




char mnu_stopky(void)
{

	if (!menu_nr[1])
	{
	
		menu_nr[1]=1;
		stopky_stav=1;
	}	


	lcd_putstring(PSTR(TXT_STOPKY),2,0,0,M_COL_TXT,M_COL_BCK,2);

	lcd_putstring(PSTR(TXT_CAS),2,36,0,COL_TXT_LCD2,M_COL_BCK,2);

	if(mnu_stopky_on==1)
	{
		lcd_putstring(PSTR(TXT_INT),144,0,0,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_INT),2,62,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_INT),2,86,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_INT),2,110,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR("-1:"),30,62,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR("-2:"),30,86,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR("-3:"),30,110,0,COL_TXT_LCD2,M_COL_BCK,2);

		lcd_putstring(PSTR(":"),95,24,2,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,43,0,M_COL_TXT,M_COL_BCK,2);

		lcd_putnr(stopky_cas/60000, 0, '0', 2, 48, 24, 2, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_cas-((stopky_cas/60000)*60000))/1000, 0, '0', 2, 104, 24, 2, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_cas-((stopky_cas/1000)*1000)), 0, '0', 2, 160, 43, 0, M_COL_TXT, M_COL_BCK, 2);

		lcd_putstring(PSTR(":"),113,58,1,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,68,0,M_COL_TXT,M_COL_BCK,2);

		lcd_putnr(stopky_mcas1/60000, 0, '0', 2, 80, 58, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_mcas1-((stopky_mcas1/60000)*60000))/1000, 0, '0', 2, 120, 58, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_mcas1-((stopky_mcas1/1000)*1000)), 0, '0', 2, 160, 68, 0, M_COL_TXT, M_COL_BCK, 2);

		lcd_putstring(PSTR(":"),113,82,1,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,92,0,M_COL_TXT,M_COL_BCK,2);

		lcd_putnr(stopky_mcas2/60000, 0, '0', 2, 80, 82, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_mcas2-((stopky_mcas2/60000)*60000))/1000, 0, '0', 2, 120, 82, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_mcas2-((stopky_mcas2/1000)*1000)), 0, '0', 2, 160, 92, 0, M_COL_TXT, M_COL_BCK, 2);

		lcd_putstring(PSTR(":"),113,106,1,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,116,0,M_COL_TXT,M_COL_BCK,2);

		lcd_putnr(stopky_mcas3/60000, 0, '0', 2, 80, 106, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_mcas3-((stopky_mcas3/60000)*60000))/1000, 0, '0', 2, 120, 106, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr((stopky_mcas3-((stopky_mcas3/1000)*1000)), 0, '0', 2, 160, 116, 0, M_COL_TXT, M_COL_BCK, 2);
	}
	if(mnu_stopky_on==2)
	{
		lcd_putstring(PSTR(TXT_LAP),144,0,0,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_LAP),2,62,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_LAP),2,86,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_LAP),2,110,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR("-1:"),30,62,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR("-2:"),30,86,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR("-3:"),30,110,0,COL_TXT_LCD2,M_COL_BCK,2);

		lcd_putstring(PSTR(":"),95,24,2,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,43,0,M_COL_TXT,M_COL_BCK,2);

		lcd_putnr((stopky_cas-stopky_mcas1)/60000, 0, '0', 2, 48, 24, 2, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_cas-stopky_mcas1)-(((stopky_cas-stopky_mcas1)/60000)*60000))/1000, 0, '0', 2, 104, 24, 2, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_cas-stopky_mcas1)-(((stopky_cas-stopky_mcas1)/1000)*1000)), 0, '0', 2, 160, 43, 0, M_COL_TXT, M_COL_BCK, 2);

		lcd_putstring(PSTR(":"),113,58,1,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,68,0,M_COL_TXT,M_COL_BCK,2);

		lcd_putnr((stopky_mcas1-stopky_mcas2)/60000, 0, '0', 2, 80, 58, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_mcas1-stopky_mcas2)-(((stopky_mcas1-stopky_mcas2)/60000)*60000))/1000, 0, '0', 2, 120, 58, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_mcas1-stopky_mcas2)-(((stopky_mcas1-stopky_mcas2)/1000)*1000)), 0, '0', 2, 160, 68, 0, M_COL_TXT, M_COL_BCK, 2);

		lcd_putstring(PSTR(":"),113,82,1,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,92,0,M_COL_TXT,M_COL_BCK,2);


		lcd_putnr((stopky_mcas2-stopky_mcas3)/60000, 0, '0', 2, 80, 82, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_mcas2-stopky_mcas3)-(((stopky_mcas2-stopky_mcas3)/60000)*60000))/1000, 0, '0', 2, 120, 82, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_mcas2-stopky_mcas3)-(((stopky_mcas2-stopky_mcas3)/1000)*1000)), 0, '0', 2, 160, 92, 0, M_COL_TXT, M_COL_BCK, 2);

		lcd_putstring(PSTR(":"),113,106,1,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR(":"),154,116,0,M_COL_TXT,M_COL_BCK,2);


		lcd_putnr((stopky_mcas3-stopky_mcas4)/60000, 0, '0', 2, 80, 106, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_mcas3-stopky_mcas4)-(((stopky_mcas3-stopky_mcas4)/60000)*60000))/1000, 0, '0', 2, 120, 106, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putnr(((stopky_mcas3-stopky_mcas4)-(((stopky_mcas3-stopky_mcas4)/1000)*1000)), 0, '0', 2, 160, 116, 0, M_COL_TXT, M_COL_BCK, 2);

	}


	if (tlacitka()==2)
	{ 
		if(stopky_stav==1||stopky_stav==3) return(1); 
		if(stopky_stav==2) stopky_stav=3;
		if(mnu_stopky_on==1) lcd_putnr((stopky_cas-((stopky_cas/1000)*1000)), 0, '0', 2, 160, 43, 0, M_COL_TXT, M_COL_BCK, 2);
		else lcd_putnr(((stopky_cas-stopky_mcas1)-(((stopky_cas-stopky_mcas1)/1000)*1000)), 0, '0', 2, 160, 43, 0, M_COL_TXT, M_COL_BCK, 2);
		while (tlacitka());
	}

	if (tlacitka()==1) 
	{
		if(stopky_stav==1) stopky_stav=2;
		if(stopky_stav==2) 
		{
			stopky_mcas4=stopky_mcas3;
			stopky_mcas3=stopky_mcas2;
			stopky_mcas2=stopky_mcas1;
			stopky_mcas1=stopky_cas;

		}

		if(stopky_stav==3)
		{
			stopky_mcas4=0;
			stopky_mcas3=0;
			stopky_mcas2=0;
			stopky_mcas1=0;
			stopky_cas=0;
			stopky_stav=1;
		}
		while (tlacitka());
	}

	return(0);
}

void stopky(void)
{
	if (stopky_stav==2) 
	{
		stopky_cas++;
		if (stopky_cas>5940000) stopky_stav=3;
	}
}


