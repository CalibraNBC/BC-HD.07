#include "mnu_nastavenia.h"
#include "menu.h"
#include "main.h"
#include "variables.h"
#include "definitions.h"
#include "keys.h"
#include "language.h"
#include <avr/pgmspace.h>
#include "lcd_s65_ls020.h"
#include "input_int.h"
#include "int_ee.h"
#include "accelerometer.h"
#include "input_char.h"
#include "settings.h"



char mnu_nastavenia(void)
{
	unsigned int temp, tmp1_podsvietenie;
	unsigned long tmp_podsvietenie, temp_long;
	unsigned char a;
	char tmp;

	tmp_podsvietenie=sv_nap;
	tmp_podsvietenie=(tmp_podsvietenie*1000)/napatie;


	switch (menu_nr[1])
	{
		case 0 :
			zobraz_all();
			menu_nr[1]=1;
			break;

		case 1 :
			zobraz_hod(M_COL_BCK, M_COL_TXT);
			if (tlacitka()==1) 
			{
			#ifndef H12	
				hodiny_h= input_int(133,0,0,2,hodiny_h,23);
				hodiny_m= input_int(152,0,0,2,hodiny_m,59);
			#endif
			#ifdef H12	
HZ:			hodiny_h= input_int(133,0,0,2,hodiny_h,12);
				if(hodiny_h==0) goto HZ;
				hodiny_m= input_int(152,0,0,2,hodiny_m,59);
			#endif

			}
			dalsie();
			break;

		case 2 :
			zobraz_hod(M_COL_TXT, M_COL_BCK);
			zobraz_cenu_za_l(M_COL_BCK, M_COL_TXT);
			if (tlacitka()==1) 
			{

				temp_long=cena_za_l_u-((cena_za_l_u/100)*100);
				cena_za_l_u= input_int(124,12,0,3,cena_za_l_u/100,999);
				cena_za_l_u=cena_za_l_u*100;
				cena_za_l_u= cena_za_l_u+input_int(152,12,0,2,temp_long,99);
			}			
			dalsie();
			break;

		case 3 :
			zobraz_cenu_za_l(M_COL_TXT, M_COL_BCK);
			zobraz_servis_zostava(M_COL_BCK, M_COL_TXT);
			if (tlacitka()==1)
			{
				servis_km=km/100;
				zobraz_servis_zostava_c();
			}
			dalsie();
			break;

		case 4: 
			zobraz_servis_zostava(M_COL_TXT, M_COL_BCK);
			zobraz_servis_interval(M_COL_BCK, M_COL_TXT);
			if (tlacitka()==1) 
			{
				servis= input_int(128,36,0,5,servis,65535);
				zobraz_servis_zostava_c();
			}			
			dalsie();
			break;

		case 5 :
			zobraz_servis_interval(M_COL_TXT, M_COL_BCK);
			zobraz_farby_text(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) 
			{
	/*			switch (M_COL_TXT)
				{
					case WHITE:
						M_COL_TXT=RED;
						break;
					case RED:
						M_COL_TXT=GREEN;
						break;
					case GREEN:
						M_COL_TXT=BLUE;
						break;
					case BLUE:
						M_COL_TXT=BLACK;
						break;
					case BLACK:
						M_COL_TXT=YELLOW;
						break;
					case YELLOW:
						M_COL_TXT=WHITE;
						break;
				}
*/
 				if(M_COL_TXT==WHITE) M_COL_TXT=RED;
				else if(M_COL_TXT==RED) M_COL_TXT=GREEN;
				else if(M_COL_TXT==GREEN) M_COL_TXT=BLUE;
				else if(M_COL_TXT==BLUE) M_COL_TXT=BLACK;
				else if(M_COL_TXT==BLACK) M_COL_TXT=YELLOW;
				else if(M_COL_TXT==YELLOW) M_COL_TXT=WHITE;

				zobraz_all();
			}
			dalsie();
			break;

		case 6 :
			zobraz_farby_text(M_COL_TXT, M_COL_BCK);
			zobraz_farby_podklad(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) 
			{

/*				switch (M_COL_BCK)
				{
					case WHITE:
						M_COL_BCK=RED;
						break;
					case RED:
						M_COL_BCK=GREEN;
						break;
					case GREEN:
						M_COL_BCK=BLUE;
						break;
					case BLUE:
						M_COL_BCK=BLACK;
						break;
					case BLACK:
						M_COL_BCK=YELLOW;
						break;
					case YELLOW:
						M_COL_BCK=WHITE;
						break;
				}
*/
				if(M_COL_BCK==WHITE) M_COL_BCK=RED;
				else if(M_COL_BCK==RED) M_COL_BCK=GREEN;
				else if(M_COL_BCK==GREEN) M_COL_BCK=BLUE;
				else if(M_COL_BCK==BLUE) M_COL_BCK=BLACK;
				else if(M_COL_BCK==BLACK) M_COL_BCK=YELLOW;
				else if(M_COL_BCK==YELLOW) M_COL_BCK=WHITE;

				lcd_clr_dspl(M_COL_BCK,1);
				lcd_clr_dspl(M_COL_BCK,2);
				zobraz_all();
			}
			dalsie();
			break;

		case 7 :
			zobraz_farby_podklad(M_COL_TXT, M_COL_BCK);
			zobraz_podsvietenie_min(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) sv_nap_val[0]=tmp_podsvietenie;
			dalsie();
			break;

		case 8 :
			zobraz_podsvietenie_min(M_COL_TXT, M_COL_BCK);
			zobraz_podsvietenie_max(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) 
			{
				tmp1_podsvietenie=tmp_podsvietenie-sv_nap_val[0];
				tmp_podsvietenie=sv_nap_val[0];
	
				sv_nap_val[0]=((tmp1_podsvietenie*SV_POMER_0)/100)+tmp_podsvietenie;
				sv_nap_val[1]=((tmp1_podsvietenie*SV_POMER_1)/100)+tmp_podsvietenie;
				sv_nap_val[2]=((tmp1_podsvietenie*SV_POMER_2)/100)+tmp_podsvietenie;
			}
			dalsie();
			break;

		case 9 :
			zobraz_podsvietenie_max(M_COL_TXT, M_COL_BCK);
			zobraz_vstrekovac(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) 
			{
				temp=vstrekovac-((vstrekovac/10)*10);
				vstrekovac=input_int(104,72,0,3,vstrekovac/10,999)*10;
				vstrekovac=vstrekovac + input_int(132,72,0,1,temp,9);
			}
			dalsie();
			break;

		case 10 :
			zobraz_vstrekovac(M_COL_TXT, M_COL_BCK);
			zobraz_poc_valcov(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) poc_valcov=input_int(144,84,0,1,poc_valcov,8);
			dalsie();
			break;


		case 11 :
			zobraz_poc_valcov(M_COL_TXT, M_COL_BCK);
			zobraz_kolesa(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) 
			{
				sirka=input_int(104,96,0,3,sirka+100,355)-100;
				profil=input_int(136,96,0,2,profil,80);
				priemer=input_int(160,96,0,2,priemer,19);
				temp=3.14*((priemer*254/10)+(((sirka+100)*profil*2)/100));
				obvod_kolesa=temp-(((temp/10)+5)/10);
			}
			dalsie();
			break;

		case 12 :
			zobraz_kolesa(M_COL_TXT, M_COL_BCK);
			zobraz_cidlo_rychosti(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) poc_zubov_abs=input_int(136,108,0,3,poc_zubov_abs,255);
			dalsie();
			break;


		case 13 :
			lcd_clr_dspl(M_COL_BCK,2);
			zobraz_all_2();
			menu_nr[1]++;
			break;


		case 14 :
			zobraz_naklon(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1) 
			{
				offset_x=accelerometer_x+offset_x;
				offset_y=accelerometer_y+offset_y;
			}
			dalsie();
			break;


		case 15 :
			zobraz_naklon(M_COL_TXT, M_COL_BCK);
			zobraz_pocetbcmenu(M_COL_BCK, M_COL_TXT);
	
			if (tlacitka()==1) poc_bc_menu=input_int(160,12,0,1,poc_bc_menu,4);
			dalsie();
			break;


		case 16 :
			zobraz_pocetbcmenu(M_COL_TXT, M_COL_BCK);
			zobraz_max_doba_jazdy(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				kavicka_s=kavicka_s+1800;
				if (kavicka_s>35000) kavicka_s=3600;
				lcd_putnr(kavicka_s/360, 1, '0', 2, 144, 24, 0, M_COL_TXT, M_COL_BCK, 2);
				while (tlacitka());
			}
			dalsie();
			break;

		case 17 :
			zobraz_max_doba_jazdy(M_COL_TXT, M_COL_BCK);
			zobraz_mnu_zrychlenie_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				if(mnu_zrychlenie_on)	mnu_zrychlenie_on=0;
				else mnu_zrychlenie_on=1;
				while (tlacitka());
			}
			dalsie();
			break;

		case 18 :
			zobraz_mnu_zrychlenie_on(M_COL_TXT, M_COL_BCK);
			zobraz_mnu_pretazenie_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				if(mnu_pretazenie_on)	mnu_pretazenie_on=0;
				else mnu_pretazenie_on=1;
				while (tlacitka());
			}
			dalsie();
			break;

		case 19 :
			zobraz_mnu_pretazenie_on(M_COL_TXT, M_COL_BCK);
			zobraz_mnu_motor_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				if(mnu_motor_on)	mnu_motor_on=0;
				else mnu_motor_on=1;
				while (tlacitka());
			}
			menu_nr[2]=0;
			dalsie();
			break;

		case 20 :
			zobraz_mnu_motor_on(M_COL_TXT, M_COL_BCK);
			zobraz_mnu_400m_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				if(mnu_400m_on)	mnu_400m_on=0;
				else mnu_400m_on=1;
				while (tlacitka());
			}
			menu_nr[2]=0;
			dalsie();
			break;

		case 21 :
			zobraz_mnu_400m_on(M_COL_TXT, M_COL_BCK);
			zobraz_mnu_stopky_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				mnu_stopky_on++;
				if(mnu_stopky_on>2)mnu_stopky_on=0;
				while (tlacitka());
			}
			menu_nr[2]=0;
			dalsie();
			break;

		case 22 :
			zobraz_mnu_stopky_on(M_COL_TXT, M_COL_BCK);
			zobraz_mnu_develop_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1&&tlacitka_long())
			{
				if(TLACITKO_STOP&!TLACITKO_START)
				{
					if(mnu_develop_on)
					{
						mnu_develop_on=0;
						mnu_max=MNU_DEVELOP_NR;
					}
					else 
					{
						mnu_develop_on=1;
						mnu_max=MNU_DEVELOP6_NR+1;
					}
					while (tlacitka());
				}
			}
			menu_nr[2]=0;
			dalsie();
			break;


		case 23:
			lcd_clr_dspl(M_COL_BCK,2);
			zobraz_all_3();
			menu_nr[1]++;
			break;



		case 24 :
			lcd_putchar('+',128,0,0,M_COL_BCK,M_COL_TXT,2);

			if (tlacitka()==1)
			{
				if (pal_korekcia!=6) pal_korekcia++;
				while (tlacitka());
				n_posledna_hodnota=pal_act+pal_korekcia;
				n_spotrebovane_palivo=spotrebovane_palivo;
			}

			lcd_putnr(pal_act+pal_korekcia, 0, '0', 2, 96, 0, 0, M_COL_TXT, M_COL_BCK, 2);
						
			if (pal_korekcia<0)
			{
				tmp=256-pal_korekcia;
				lcd_putchar('-',144,0,0,M_COL_TXT,M_COL_BCK,2);
				lcd_putnr(tmp, 0, '0', 1, 152, 0, 0, M_COL_TXT, M_COL_BCK, 2);
			}
			else
			{
				lcd_putchar(' ',144,0,0,M_COL_TXT,M_COL_BCK,2);
				if (pal_korekcia!=6) lcd_putnr(pal_korekcia, 0, '0', 1, 152, 0, 0, M_COL_TXT, M_COL_BCK, 2);
				else lcd_putchar('F',152,0,0,M_COL_TXT,M_COL_BCK,2);
			}
			dalsie();
			break;

		case 25 :
			lcd_putchar('+',128,0,0,M_COL_TXT,M_COL_BCK,2);
			lcd_putchar('-',168,0,0,M_COL_BCK,M_COL_TXT,2);

			if (tlacitka()==1)
			{
				if (pal_korekcia!=-5) pal_korekcia--;
				while (tlacitka());
				n_posledna_hodnota=pal_act+pal_korekcia;
				n_spotrebovane_palivo=spotrebovane_palivo;
			}

			lcd_putnr(pal_act+pal_korekcia, 0, '0', 2, 96, 0, 0, M_COL_TXT, M_COL_BCK, 2);
			if (pal_korekcia<0)
			{
				tmp=256-pal_korekcia;
				lcd_putchar('-',144,0,0,M_COL_TXT,M_COL_BCK,2);
				lcd_putnr(tmp, 0, '0', 1, 152, 0, 0, M_COL_TXT, M_COL_BCK, 2);
			}
			else
			{
				lcd_putchar(' ',144,0,0,M_COL_TXT,M_COL_BCK,2);
				if (pal_korekcia!=6) lcd_putnr(pal_korekcia, 0, '0', 1, 152, 0, 0, M_COL_TXT, M_COL_BCK, 2);
				else lcd_putchar('F',152,0,0,M_COL_TXT,M_COL_BCK,2);
			}
			dalsie();
			break;


		case 26 :
			lcd_putchar('-',168,0,0,M_COL_TXT,M_COL_BCK,2);
			zobraz_zapispozdrav(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				for (a=0;a<=9;a++) nick[a]=input_char(96+(a*8),12,0,nick[a]);
			}
			dalsie();
			break;


		case 27 :
			zobraz_zapispozdrav(M_COL_TXT, M_COL_BCK);
			zobraz_nast_ot(M_COL_BCK, M_COL_TXT);
			
			if (tlacitka()==1) otacky_del=input_int(160,24,0,1,otacky_del,2);
			dalsie();
			break;


		case 28 :
			zobraz_nast_ot(M_COL_TXT, M_COL_BCK);
/*			zobraz_hod_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				if(hodiny_on)	hodiny_on=0;
				else hodiny_on=1;
				while (tlacitka());
			}
			menu_nr[2]=0;
			dalsie();
			break;

		case 29 :
			zobraz_hod_on(M_COL_TXT, M_COL_BCK);
*/			zobraz_lambda_on(M_COL_BCK, M_COL_TXT);

			if (tlacitka()==1)
			{
				if(lambda_on<4)	lambda_on++;
				else lambda_on=0;
				while (tlacitka());
			}
			menu_nr[2]=0;
			dalsie();
			break;


//		case 30 :
		case 29 :
			zapis_nastaveni_bc();
			nacitaj_nastavenia();
			nast_cpu();
			lcd_clr_dspl(M_COL_BCK,1);
			return(1);	
				
	}


	return(0);
}


void zobraz_all_3(void)
{
	unsigned char a;
	char tmp;

	zobraz_nast_nadrze(M_COL_TXT,M_COL_BCK);
	lcd_putnr(pal_act+pal_korekcia, 0, '0', 2, 96, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(TXT_L),112,0,0,M_COL_TXT,M_COL_BCK,2);
	lcd_putchar('+',128,0,0,M_COL_TXT,M_COL_BCK,2);
	lcd_putchar('-',168,0,0,M_COL_TXT,M_COL_BCK,2);
	if (pal_korekcia<0)
	{
		tmp=256-pal_korekcia;
		lcd_putchar('-',144,0,0,M_COL_TXT,M_COL_BCK,2);
		lcd_putnr(tmp, 0, '0', 1, 152, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	}
	else
	{
		lcd_putchar(' ',144,0,0,M_COL_TXT,M_COL_BCK,2);
		if (pal_korekcia!=6) lcd_putnr(pal_korekcia, 0, '0', 1, 152, 0, 0, M_COL_TXT, M_COL_BCK, 2);
		else lcd_putchar('F',152,0,0,M_COL_TXT,M_COL_BCK,2);
	}

	zobraz_zapispozdrav(M_COL_TXT,M_COL_BCK);
	for (a=0;a<=9;a++) lcd_putchar(nick[a],96+(a*8),12,0,M_COL_TXT,M_COL_BCK,2);;


	zobraz_nast_ot(M_COL_TXT,M_COL_BCK);
	lcd_putnr(otacky_del, 0, '0', 1, 160, 24, 0, M_COL_TXT, M_COL_BCK, 2);

//	zobraz_hod_on(M_COL_TXT,M_COL_BCK);

	zobraz_lambda_on(M_COL_TXT,M_COL_BCK);
}



void zobraz_all_2(void)
{
	zobraz_naklon(M_COL_TXT, M_COL_BCK);

	zobraz_pocetbcmenu(M_COL_TXT,M_COL_BCK);	
	lcd_putnr(poc_bc_menu, 0, '0', 1, 160, 12, 0, M_COL_TXT, M_COL_BCK, 2);

	zobraz_max_doba_jazdy(M_COL_TXT,M_COL_BCK);
	lcd_putnr(kavicka_s/360, 1, '0', 2, 144, 24, 0, M_COL_TXT, M_COL_BCK, 2);

	zobraz_mnu_zrychlenie_on(M_COL_TXT,M_COL_BCK);

	zobraz_mnu_pretazenie_on(M_COL_TXT,M_COL_BCK);

	zobraz_mnu_motor_on(M_COL_TXT,M_COL_BCK);

	zobraz_mnu_400m_on(M_COL_TXT,M_COL_BCK);

	zobraz_mnu_stopky_on(M_COL_TXT,M_COL_BCK);

	zobraz_mnu_develop_on(M_COL_TXT,M_COL_BCK);
}
void zobraz_all(void)
{
	zobraz_hod(M_COL_TXT,M_COL_BCK);	
	lcd_putnr(hodiny_h, 0, '0', 2, 133, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(":"),149,0,0,M_COL_TXT,M_COL_BCK,2);
	lcd_putnr(hodiny_m, 0, '0', 2, 152, 0, 0, M_COL_TXT, M_COL_BCK, 2);

	zobraz_cenu_za_l(M_COL_TXT, M_COL_BCK);

	lcd_putnr(cena_za_l_u, 2, ' ', 5, 124, 12, 0, M_COL_TXT, M_COL_BCK, 2);


	zobraz_servis_zostava(M_COL_TXT, M_COL_BCK);
	zobraz_servis_zostava_c();

	zobraz_servis_interval(M_COL_TXT, M_COL_BCK);

	lcd_putstring(PSTR(TXT_FARBY),0,48,0,M_COL_TXT,M_COL_BCK,2);
	zobraz_farby_text(M_COL_TXT, M_COL_BCK);
	zobraz_farby_podklad(M_COL_TXT, M_COL_BCK);

	lcd_putstring(PSTR(TXT_PODSVIETENIE),0,60,0,M_COL_TXT,M_COL_BCK,2);
	zobraz_podsvietenie_max(M_COL_TXT, M_COL_BCK);
	zobraz_podsvietenie_min(M_COL_TXT, M_COL_BCK);

	zobraz_vstrekovac(M_COL_TXT, M_COL_BCK);
	zobraz_poc_valcov(M_COL_TXT, M_COL_BCK);
	zobraz_kolesa(M_COL_TXT, M_COL_BCK);

	lcd_putnr(vstrekovac, 1, ' ', 4, 104, 72, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(poc_valcov, 0, '0', 1, 144, 84, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(" ccm"),144,72,0,M_COL_TXT,M_COL_BCK,2);

	lcd_putnr(sirka+100, 0, ' ', 3, 104, 96, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(profil, 0, ' ', 2, 136, 96, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(priemer, 0, ' ', 2, 160, 96, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putchar('/',128,96,0,M_COL_TXT,M_COL_BCK,2);
	lcd_putchar('/',152,96,0,M_COL_TXT,M_COL_BCK,2);

	zobraz_cidlo_rychosti(M_COL_TXT, M_COL_BCK);
	lcd_putnr(poc_zubov_abs, 0, ' ', 3, 136, 108, 0, M_COL_TXT, M_COL_BCK, 2);

}

void zobraz_lambda_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_LAMBDA_M),0,36,0,txt,bck,2);
		if(lambda_on==1)	lcd_putstring(PSTR(TXT_NB),152,36,0,M_COL_TXT,M_COL_BCK,2);
		else if(lambda_on==2)	lcd_putstring(PSTR(TXT_BUFFER),152,36,0,M_COL_TXT,M_COL_BCK,2);
		else if(lambda_on==3)	lcd_putstring(PSTR(TXT_5V),152,36,0,M_COL_TXT,M_COL_BCK,2);
		else if(lambda_on==4)	lcd_putstring(PSTR(TXT_WB),152,36,0,M_COL_TXT,M_COL_BCK,2);
		else lcd_putstring(PSTR(TXT_OFF),152,36,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_hod_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_HODINY),0,36,0,txt,bck,2);
		if(hodiny_on)	lcd_putstring(PSTR(TXT_ON),152,36,0,M_COL_TXT,M_COL_BCK,2);
		else lcd_putstring(PSTR(TXT_OFF),152,36,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_nast_ot(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_OTACKY),0,24,0,txt,bck,2);
}
void zobraz_nast_nadrze(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_NAST_NADRZE),0,0,0,txt,bck,2);
}
void zobraz_zapispozdrav(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_WELCOMETEXT),0,12,0,txt,bck,2);
}
void zobraz_mnu_motor_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_OBR_MOTOR),0,60,0,txt,bck,2);
		if(mnu_motor_on)	lcd_putstring(PSTR(TXT_ON),152,60,0,M_COL_TXT,M_COL_BCK,2);
		else lcd_putstring(PSTR(TXT_OFF),152,60,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_mnu_pretazenie_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_OBR_PRETAZENIE),0,48,0,txt,bck,2);
		if(mnu_pretazenie_on)	lcd_putstring(PSTR(TXT_ON),152,48,0,M_COL_TXT,M_COL_BCK,2);
		else lcd_putstring(PSTR(TXT_OFF),152,48,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_mnu_zrychlenie_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_OBR_ZRYCHLENIE),0,36,0,txt,bck,2);
		if(mnu_zrychlenie_on)	lcd_putstring(PSTR(TXT_ON),152,36,0,M_COL_TXT,M_COL_BCK,2);
		else lcd_putstring(PSTR(TXT_OFF),152,36,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_mnu_stopky_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_OBR_STOPKY),0,84,0,txt,bck,2);
		if(mnu_stopky_on==1) lcd_putstring(PSTR(TXT_INT),152,84,0,M_COL_TXT,M_COL_BCK,2);
		if(mnu_stopky_on==2) lcd_putstring(PSTR(TXT_LAP),152,84,0,M_COL_TXT,M_COL_BCK,2);
		if(mnu_stopky_on==0) lcd_putstring(PSTR(TXT_OFF),152,84,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_mnu_develop_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_OBR_DEVELOP),0,96,0,txt,bck,2);
		if(mnu_develop_on)	lcd_putstring(PSTR(TXT_ON),152,96,0,M_COL_TXT,M_COL_BCK,2);
		else lcd_putstring(PSTR(TXT_OFF),152,96,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_mnu_400m_on(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_OBR_SPRINT),0,72,0,txt,bck,2);
		if(mnu_400m_on)	lcd_putstring(PSTR(TXT_ON),152,72,0,M_COL_TXT,M_COL_BCK,2);
		else lcd_putstring(PSTR(TXT_OFF),152,72,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_max_doba_jazdy(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_MAX_DOBA),0,24,0,txt,bck,2);
		lcd_putstring(PSTR(TXT_H),164,24,0,M_COL_TXT,M_COL_BCK,2);
}
void zobraz_pocetbcmenu(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_POCETMENUBC),0,12,0,txt,bck,2);
}
void zobraz_hod(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_HODINY),0,0,0,txt,bck,2);
}
void zobraz_cenu_za_l(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_CENA),0,12,0,txt,bck,2);
}
void zobraz_servis_zostava(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_SERVIS_Z),0,24,0,txt,bck,2);
}
void zobraz_servis_interval(int txt, int bck)
{
		lcd_putstring(PSTR(TXT_SERVIS_I),0,36,0,txt,bck,2);
}
void zobraz_naklon(int txt, int bck)
{
	lcd_putstring(PSTR(TXT_NAKLON),0,0,0,txt,bck,2);
}
void zobraz_cidlo_rychosti(int txt, int bck)
{
	lcd_putstring(PSTR(TXT_CIDLO),0,108,0,txt,bck,2);
}
void zobraz_vstrekovac(int txt, int bck)
{
	lcd_putstring(PSTR(TXT_VSTREKOVAC),0,72,0,txt,bck,2);
}
void zobraz_poc_valcov(int txt, int bck)
{
	lcd_putstring(PSTR(TXT_VALCE),0,84,0,txt,bck,2);
}
void zobraz_kolesa(int txt, int bck)
{
	lcd_putstring(PSTR(TXT_KOLESA),0,96,0,txt,bck,2);
}
void zobraz_podsvietenie_min(int txt, int bck)
{
#ifndef S65_LANG_RUS
	lcd_putstring(PSTR(TXT_MIN),120,60,0,txt,bck,2);
#endif
#ifdef S65_LANG_RUS
	lcd_putstring(PSTR(TXT_MIN),112,60,0,txt,bck,2);
#endif
}
void zobraz_podsvietenie_max(int txt, int bck)
{
#ifndef S65_LANG_RUS
	lcd_putstring(PSTR(TXT_MAX),152,60,0,txt,bck,2);
#endif

#ifdef S65_LANG_RUS
	lcd_putstring(PSTR(TXT_MAX),144,60,0,txt,bck,2);
#endif
}
void zobraz_farby_text(int txt, int bck)
{
	lcd_putstring(PSTR(TXT_TEXT),80,48,0,txt,bck,2);
}
void zobraz_farby_podklad(int txt, int bck)
{
	lcd_putstring(PSTR(TXT_PODKLAD),120,48,0,txt,bck,2);
}
void zobraz_servis_zostava_c(void)
{
	lcd_putnr(servis, 0, ' ', 5, 128, 36, 0, M_COL_TXT, M_COL_BCK, 2);
	if ((servis_km+servis)<(km/100)) 
	{
		lcd_putchar('-',120,24,0,WHITE,RED,2);
		lcd_putnr((km/100)-(servis_km+servis), 0, ' ', 5, 128, 24, 0, WHITE, RED, 2);
	}
	else lcd_putnr((servis_km+servis)-(km/100), 0, ' ', 6, 120, 24, 0, M_COL_TXT, M_COL_BCK, 2);
}

void dalsie(void)
{
	if (tlacitka()==2) menu_nr[1]++;	
	while (tlacitka());
}
