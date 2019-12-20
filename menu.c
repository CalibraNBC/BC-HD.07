#include "menu.h"
#include "main.h"
#include "keys.h"
#include "beep.h"
#include "lcd_s65_ls020.h"
#include "mnu_bc.h"
#include "definitions.h"
#include "mnu_nastavenia.h"
#include "variables.h"
#include "mnu_pretazenie.h"
#include "zrychlenie.h"
#include "mnu_motor.h"
#include "mnu_develop.h"
#include "mnu_400m.h"
#include "mnu_stopky.h"

#include "settings.h"



void menu(void)
{
	unsigned char old_menu;


	
	old_menu=menu_nr[0];




	switch (menu_nr[0])
	{

				case MNU_BC_NR :
					if (mnu_bc()) zmena_menu(menu_nr[0]);
					break;

				case MNU_PRETAZENIE_NR :
					if (!mnu_pretazenie_on) zmena_menu(menu_nr[0]+1);
					else if (mnu_pretazenie()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_ZRYCHLENIE_NR :
					if (!mnu_zrychlenie_on) zmena_menu(menu_nr[0]+1);	
					else if (mnu_zrychlenie()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_MOTOR_NR :	
					if (!mnu_motor_on) zmena_menu(menu_nr[0]+1);
					else if (mnu_motor()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_400M_NR :	
					if (!mnu_400m_on) zmena_menu(menu_nr[0]+1);
					else if (mnu_400m()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_STOPKY_NR :	
					if (!mnu_stopky_on) zmena_menu(menu_nr[0]+1);
					else if (mnu_stopky()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_DEVELOP_NR :	

					if (mnu_develop()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_DEVELOP2_NR :	

					if (mnu_develop2()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_DEVELOP3_NR :	

					if (mnu_develop3()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_DEVELOP4_NR :	

					if (mnu_develop4()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_DEVELOP5_NR :	

					if (mnu_develop5()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_DEVELOP6_NR :	

					if (mnu_develop6()) zmena_menu(menu_nr[0]+1);	
					break;

				case MNU_NASTAVENIA_NR :
					if (mnu_nastavenia()) zmena_menu(MNU_BC_NR);	
					break;
	}
}


void zmena_menu(unsigned char nove_menu)
{
	if(nove_menu==mnu_max) nove_menu=1;
	menu_nr[0]=nove_menu;
	menu_nr[1]=0;
	menu_nr[2]=0;
	while (tlacitka());
	lcd_clr_dspl(M_COL_BCK,2);
}


