#include "mnu_hlavne.h"
#include "menu.h"
#include "lcd_s65_ls020.h"
#include "keys.h"
#include "variables.h"
#include "language.h"
#include <avr/pgmspace.h>





char mnu_hlavne(void)
{

	mnu_hl_text(menu_nr[1]);

	if (tlacitka()==2)
	{
		if (menu_nr[1]==6) menu_nr[1]=0;		//6 - Max
		else menu_nr[1]=menu_nr[1]+1;
		
		while (tlacitka());
	}

	if (tlacitka()==1)
	{
		switch (menu_nr[1])
			{
			case 0 :
				menu_nr[0]=MNU_BC_NR;
				break;

			case 1 :
//				menu_nr[0]=MNU_PRETAZENIE_NR;
				break;
	
			case 2 :
//				menu_nr[0]=MNU_ZRYCHLENIE_NR;
				break;

			case 3 :
//				menu_nr[0]=MNU_MAX_HODNOTY;
				break;

			case 4 :
				menu_nr[0]=MNU_NASTAVENIA_NR;
				break;

			case 5 :
//				menu_nr[0]=MNU_RESET_NR;
				break;

			case 6 :
//				menu_nr[0]=MNU_VERZIA_NR;
				break;
			}
		return(1);
	}
	
	return(0);
}



void mnu_hl_text(char a)
{

	lcd_putstring(PSTR(TXT_MENU),0,0,1,M_COL_TXT,M_COL_BCK,2);

	lcd_putstring(PSTR(TXT_BC________),0,36,0,(a==0)*M_COL_BCK+(a!=0)*M_COL_TXT,(a!=0)*M_COL_BCK+(a==0)*M_COL_TXT,2);

	lcd_putstring(PSTR(TXT_PRETAZENIE),0,48,0,(a==1)*M_COL_BCK+(a!=1)*M_COL_TXT,(a!=1)*M_COL_BCK+(a==1)*M_COL_TXT,2);

	lcd_putstring(PSTR(TXT_ZRYCHLENIE),0,60,0,(a==2)*M_COL_BCK+(a!=2)*M_COL_TXT,(a!=2)*M_COL_BCK+(a==2)*M_COL_TXT,2);

	lcd_putstring(PSTR(TXT_MAX_HODNOTY),0,72,0,(a==3)*M_COL_BCK+(a!=3)*M_COL_TXT,(a!=3)*M_COL_BCK+(a==3)*M_COL_TXT,2);

	lcd_putstring(PSTR(TXT_NASTAVENIA),0,84,0,(a==4)*M_COL_BCK+(a!=4)*M_COL_TXT,(a!=4)*M_COL_BCK+(a==4)*M_COL_TXT,2);

	lcd_putstring(PSTR(TXT_RESET_____),0,96,0,(a==5)*M_COL_BCK+(a!=5)*M_COL_TXT,(a!=5)*M_COL_BCK+(a==5)*M_COL_TXT,2);

	lcd_putstring(PSTR(TXT_VERZIA____),0,108,0,(a==6)*M_COL_BCK+(a!=6)*M_COL_TXT,(a!=6)*M_COL_BCK+(a==6)*M_COL_TXT,2);



//	zobraz_nick(15);

}


void zobraz_nick(unsigned char x)
{
	//unsigned char a;



//	for (a=0;a<=9;a++) lcd_putchar(nick[a],1,0);
}


