#include "mnu_max_hodnoty.h"
#include "variables.h"
#include "language.h"
#include "keys.h"
#include "mnu_bc.h"



char mnu_max_hodnoty(void)
{
/*
	lcd_gotoxy(0,0);
	lcd_putstring(PSTR(TXT_MAX_HODNOTY),1,0);


	lcd_gotoxy(2,0);
	lcd_putstring(PSTR(TXT_PRETAZENIE),1,0);

	lcd_gotoxy(3,0);
	lcd_putstring(PSTR("X:"),1,0);
	lcd_putnr(((max_pretazenie_x*2)+5)/10,1,1,0,2,' ');
	lcd_putstring(PSTR(" Y:"),1,0);
	lcd_putnr(((max_pretazenie_y*2)+5)/10,1,1,0,2,' ');


	lcd_gotoxy(5,0);
	lcd_putstring(PSTR(TXT_ZRYCHLENIE),1,0);
 	lcd_gotoxy(6,0);
	if (max_zrychlenie==0xFF) lcd_putstring(PSTR("     ---"),1,0);
	else lcd_putnr(max_zrychlenie, 1, 1, 0, 8, ' ');
	lcd_putstring(PSTR("s"),1,0);

	lcd_gotoxy(8,0);
	lcd_putstring(PSTR(TXT_SPOTREBA),1,0);

	lcd_gotoxy(9,0);
	lcd_putstring(PSTR(TXT_MIN_SPOTREBA1),1,0);
 	if (min_spotreba_1==0xFF) lcd_putstring(PSTR("---"),1,0);
	else lcd_putnr(min_spotreba_1, 1, 1, 0, 3, ' ');

	lcd_gotoxy(10,0);
	lcd_putstring(PSTR(TXT_MIN_SPOTREBA2),1,0);
 	if (min_spotreba_2==0xFF) lcd_putstring(PSTR("---"),1,0);
 	else lcd_putnr(min_spotreba_2, 1, 1, 0, 3, ' ');

	lcd_gotoxy(11,0);
	lcd_putstring(PSTR(TXT_MIN_SPOTREBA3),1,0);
 	if (min_spotreba_3==0xFF) lcd_putstring(PSTR("---"),1,0);
 	else	lcd_putnr(min_spotreba_3, 1, 1, 0, 3, ' ');


#ifdef DEVELOP	//------------------------------DEVELOP-------------------

	lcd_gotoxy(13,0);
	lcd_putstring(PSTR(TXT_DOJAZD),1,0);

	lcd_gotoxy(14,0);
 	lcd_putnr(max_dojazd, 0, 1, 0, 8, ' ');
	lcd_putstring(PSTR("Km"),1,0);
#endif


	if (tlacitka()==2) return(1);
*/
	return(0);
}


void max_hodnoty_zapis(void)
{
	unsigned char a;

	for (a=0;a<=5;a++)
	{
		if ((km-km_denne[a])/100>20&&min_spotreba_1>vypocet_priemerna_spotreba(a)) min_spotreba_1=vypocet_priemerna_spotreba(a);
		if ((km-km_denne[a])/100>100&&min_spotreba_2>vypocet_priemerna_spotreba(a)) min_spotreba_2=vypocet_priemerna_spotreba(a);
		if ((km-km_denne[a])/100>500&&min_spotreba_3>vypocet_priemerna_spotreba(a)) min_spotreba_3=vypocet_priemerna_spotreba(a);
	}


#ifdef DEVELOP	//------------------------------DEVELOP-------------------
	if (max_dojazd<(km-km_denne[4])/100) max_dojazd=(km-km_denne[4])/100;
#endif
}
