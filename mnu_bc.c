#include "mnu_bc.h"
#include "menu.h"
#include "main.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "definitions.h"
#include "language.h"
#include "keys.h"
#include "meranie_spotreby.h"
#include "meranie_vzdialenosti_rychlosti.h"
#include <avr/pgmspace.h>
#include "settings.h"


unsigned char lcd1_stav;


char mnu_bc(void)
{
	if (menu_nr[1]==poc_bc_menu)menu_nr[1]=4;

	switch (menu_nr[2])
	{
		case 0 :
			zobraz_cislo_menu(menu_nr[1]);	
			zobraz_km(menu_nr[1]);
			zobraz_rychlost(menu_nr[1]);
			menu_nr[2]=1;
			break;
		case 1 :
			zobraz_spotrebu(menu_nr[1]);
			zobraz_cenu(menu_nr[1]);
			zobraz_dobu(menu_nr[1]);
			menu_nr[2]=0;
			break;
	}

		if (menu_nr[1]<4&&tlacitka()==1)
		{
			if (tlacitka_long()) 
			{
				reset_denne(menu_nr[1]);
				zobraz_cislo_menu(menu_nr[1]);	
				zobraz_km(menu_nr[1]);
				zobraz_rychlost(menu_nr[1]);
				menu_nr[2]=1;
			}

			if (menu_nr[1]<3&&status_ss[menu_nr[1]]==0)
			{
				km_ss[menu_nr[1]]=vypocet_km(menu_nr[1]);
				spotrebovane_palivo_ss[menu_nr[1]]=vypocet_spotrebovane_palivo(menu_nr[1]);
				doba_jazdy_ss[menu_nr[1]]=vypocet_doba_jazdy(menu_nr[1]);
				status_ss[menu_nr[1]]=1;
			}
			else status_ss[menu_nr[1]]=0;
							
		}

		if (tlacitka()==2)
		{
			if (menu_nr[1]<5)
			{
				menu_nr[1]=menu_nr[1]+1;

				while (tlacitka());
			}
			else 
			{
				menu_nr[0]++;
				return(1);
			}
		}

		if (TLACITKO_START&&TLACITKO_STOP&&rychlost_p==0)
		{
				menu_nr[0]=MNU_NASTAVENIA_NR;
				lcd_clr_dspl(M_COL_BCK,1);
				return(1);
		}


	return(0);
}



void zobraz_dobu(unsigned char cis)
{
	unsigned long temp;
	unsigned int tmp_color;

	if (vypocet_doba_jazdy(cis)<3600)
	{
		temp=vypocet_doba_jazdy(cis)/60;
		lcd_putnr(temp, 0, '0', 2, 18, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putstring(PSTR(" "),50,102,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_M),50,114,0,COL_TXT_LCD2,M_COL_BCK,2);
		temp=vypocet_doba_jazdy(cis)-(temp*60);
		lcd_putnr(temp, 0, '0', 2, 58, 104, 1, M_COL_TXT, M_COL_BCK, 2);
	}
	else if (vypocet_doba_jazdy(cis)<360000)
	{
		temp=vypocet_doba_jazdy(cis)/3600;
		lcd_putnr(temp, 0, '0', 2, 18, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putstring(PSTR(" "),50,102,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR(TXT_H),50,114,0,COL_TXT_LCD2,M_COL_BCK,2);
		temp=(vypocet_doba_jazdy(cis)-(temp*3600))/60;
		lcd_putnr(temp, 0, '0', 2, 58, 104, 1, M_COL_TXT, M_COL_BCK, 2);
	}
	else
	{
		lcd_putnr(vypocet_doba_jazdy(cis)/3600, 0, ' ', 4, 18, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		lcd_putstring(PSTR(TXT_H),82,114,0,COL_TXT_LCD2,M_COL_BCK,2);
		lcd_putstring(PSTR(" "),82,104,0,COL_TXT_LCD2,M_COL_BCK,2);
	}

	if (M_COL_BCK==GREEN) tmp_color=BLUE;
	else tmp_color=GREEN;

	lcd_put_bw_picture(HODINY_S,2,104,1,IKONA_X,IKONA_Y,tmp_color,M_COL_BCK,2);

}



void zobraz_cenu(unsigned char cis)		//Zobrazí cenu
{
	unsigned long temp;


	if(cena_za_l_u>10000)temp=vypocet_spotrebovane_palivo(cis)*(cena_za_l_u/10)/100;
	else temp=vypocet_spotrebovane_palivo(cis)*cena_za_l_u/10000;


		if (cis<5&&temp<10000) lcd_putnr(temp, 1, ' ', 4, 104, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		if (cis<5&&temp>=10000&&temp<1000000) lcd_putnr(temp/10, 0, ' ', 5, 96, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		if (cis>4||temp>=1000000) lcd_putstring(PSTR("     "),96, 104, 1, M_COL_TXT, M_COL_BCK, 2);



/*
	#ifdef ZADAVANIE_CENY_0_DESATINNYCH_MIEST
		temp=vypocet_spotrebovane_palivo(cis)*cena_za_l/1000;

		if (cis<5&&temp<100000) lcd_putnr(temp, 0, ' ', 5, 96, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		if (cis>4||temp>=100000) lcd_putstring(PSTR("     "),96, 104, 1, M_COL_TXT, M_COL_BCK, 2);

	#endif

	#ifdef ZADAVANIE_CENY_1_DESATINNE_MIESTO
		temp=vypocet_spotrebovane_palivo(cis)*cena_za_l/1000;
	#endif

	#ifdef ZADAVANIE_CENY_2_DESATINNE_MIESTA
		temp=vypocet_spotrebovane_palivo(cis)*cena_za_l/10000;
	#endif

	#ifndef ZADAVANIE_CENY_0_DESATINNYCH_MIEST
		if (cis<5&&temp<1000) lcd_putnr(temp, 1, ' ', 4, 88, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		if (cis<5&&temp>=1000&&temp<100000) lcd_putnr(temp/10, 0, ' ', 4, 96, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		if (cis>4||temp>=100000) lcd_putstring(PSTR("     "),96, 104, 1, M_COL_TXT, M_COL_BCK, 2);
		else
		{
			#ifndef ZNAK_MENY
				lcd_putstring(PSTR(TXT_MENAHR),160,104,0,COL_TXT_LCD2,M_COL_BCK,2);
				lcd_putstring(PSTR(TXT_MENASR),160,116,0,COL_TXT_LCD2,M_COL_BCK,2);
			#endif	
			#ifdef EUR
				lcd_putchar(130,160,114,0,COL_TXT_LCD2,M_COL_BCK,2);
			#endif	
			#ifdef GBP
				lcd_putchar(131,160,114,0,COL_TXT_LCD2,M_COL_BCK,2);
			#endif	
			#ifdef USD
				lcd_putchar(132,160,114,0,COL_TXT_LCD2,M_COL_BCK,2);
			#endif	
		}
	#endif
*/

}


void zobraz_spotrebu(unsigned char cis) 		//Zobrazí priemernú spotrebu a spotrebované palivo
{
//	unsigned int temp;
	float temp;
	unsigned long tmp;

	if (vypocet_km(cis)>10) 
	{
		temp=vypocet_priemerna_spotreba(cis);
#ifdef MPH
		if (temp<5) temp=5;
		lcd_putnr(4.55/(temp/1000), 0, ' ', 3, 104, 53, 1, M_COL_TXT, M_COL_BCK, 2);
	}
	else lcd_putstring(PSTR(" --"),104,53,1,M_COL_TXT,M_COL_BCK,2);
#endif
#ifndef MPH
		if (temp>999) temp=999;
		lcd_putnr(temp, 1, ' ', 3, 96, 53, 1, M_COL_TXT, M_COL_BCK, 2);
	}
	else lcd_putstring(PSTR("  --"),86,53,1,M_COL_TXT,M_COL_BCK,2);
#endif

	lcd_putstring(PSTR(TXT_L100KMHR),152,53,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR(TXT_L100KMSR),152,65,0,COL_TXT_LCD2,M_COL_BCK,2);

#ifndef S65_LANG_RU
	lcd_putstring(PSTR(TXT_TOT),96,77,0,COL_TXT_LCD2,M_COL_BCK,2);
#endif

#ifdef S65_LANG_RU
	lcd_putstring(PSTR(TXT_TOT),80,77,0,COL_TXT_LCD2,M_COL_BCK,2);
#endif

	lcd_putstring(PSTR(TXT_L),168,77,0,COL_TXT_LCD2,M_COL_BCK,2);


	tmp=vypocet_spotrebovane_palivo(cis);

	if (tmp<100000) lcd_putnr(tmp/100, 1, ' ', 5, 124, 77, 0, M_COL_TXT, M_COL_BCK, 2);
	else	lcd_putnr(tmp/1000, 0, ' ', 6, 120, 77, 0, M_COL_TXT, M_COL_BCK, 2);


}


void zobraz_rychlost(unsigned char cis)			//Zobrazí priemernú a maximálnu rýchlos
{
	unsigned int temp;
	unsigned int tmp_color;

	lcd_putnr(vypocet_priemerna_rychlost(vypocet_km(cis),vypocet_doba_jazdy(cis)), 0, ' ', 3, 16, 53, 1, M_COL_TXT, M_COL_BCK, 2);


	if (cis==5) temp=max_spd;
	else temp=max_spd_denne[cis];
	lcd_putnr(temp, 0, ' ', 3, 40, 77, 0, M_COL_TXT, M_COL_BCK, 2);

	lcd_putstring(PSTR(TXT_MAX),2,77,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR(TXT_KMHR),64,53,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR(TXT_KMSR),64,65,0,COL_TXT_LCD2,M_COL_BCK,2);


	if (M_COL_BCK==GREEN) tmp_color=BLUE;
	else tmp_color=GREEN;

	lcd_put_bw_picture(PRIEMER_S,2,53,1,IKONA_X,IKONA_Y,tmp_color,M_COL_BCK,2);

}

void zobraz_cislo_menu(unsigned char cis)
{
	int tmp=0;
	
	if (cis<3) tmp=status_ss[cis];
	
	if (tmp)
	{
		if(M_COL_BCK==YELLOW||M_COL_TXT==YELLOW)tmp=RED;
		else tmp=YELLOW;
	}
	else tmp=M_COL_TXT;
	
	switch (cis)
		{
		case 0 :
			lcd_putstring(PSTR("1"),0,0,1,M_COL_BCK,tmp,2);
			break;
		case 1 :
			lcd_putstring(PSTR("2"),0,0,1,M_COL_BCK,tmp,2);
			break;
		case 2 :
			lcd_putstring(PSTR("3"),0,0,1,M_COL_BCK,tmp,2);
			break;
		case 3 :
			lcd_putstring(PSTR("4"),0,0,1,M_COL_BCK,tmp,2);
			break;
		case 4 :
			lcd_putstring(PSTR(TXT_J),0,0,1,M_COL_BCK,tmp,2);
			break;
		case 5 :
			lcd_putstring(PSTR(TXT_C),0,0,1,M_COL_BCK,tmp,2);
			break;
		}
}

void zobraz_km(unsigned char cis)			//Zobrazí najazdenú vzdialenos
{
	if (vypocet_km(cis)<99999)
	{
	 	lcd_putnr(vypocet_km(cis)/10, 1, ' ', 5, 28, 0, 2, M_COL_TXT, M_COL_BCK, 2);
	}
	else lcd_putnr(vypocet_km(cis)/100, 0, ' ', 6, 17, 0, 2, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR(TXT_KM),160,12,0,COL_TXT_LCD2,M_COL_BCK,2);
}


void zobraz_lcd1(void)
{
	int temp;
	unsigned int a, b, tmp_color, tmp_color1;
	unsigned long tmp1;
	long tmp;


//as_km=1;
//rychlost=20;

	switch (lcd1_stav)
	{
		case 0 :
			if (rychlost_p<300) lcd_putnr(rychlost_p, 0, ' ', 3, 0, 5, 2, M_COL_TXT, M_COL_BCK, 1);

			lcd_putstring(PSTR(TXT_KMH),40,39,0,COL_TXT_LCD1, M_COL_BCK,1);
#ifdef MPH
			if (rychlost<7)
			{
				lcd_putnr(as_h, 1, ' ', 3, 92, 5, 2, M_COL_TXT, M_COL_BCK, 1);
				lcd_putstring(PSTR("    "),120,39,0,COL_TXT_LCD1, M_COL_BCK,1);
				lcd_putstring(PSTR("l/h"),152,39,0,COL_TXT_LCD1, M_COL_BCK,1);
			}
#endif
#ifndef MPH
			if (rychlost<10)
			{
				lcd_putnr(as_h, 1, ' ', 3, 92, 5, 2, M_COL_TXT, M_COL_BCK, 1);
				lcd_putstring(PSTR("    "),120,39,0,COL_TXT_LCD1, M_COL_BCK,1);
				lcd_putstring(PSTR(TXT_L100KMHR),152,39,0,COL_TXT_LCD1, M_COL_BCK,1);
				lcd_putstring(PSTR(TXT_H),168,39,0,COL_TXT_LCD1, M_COL_BCK,1);
			}
#endif
			else
			{
#ifndef MPH
				if (as_km<1000)	lcd_putnr(as_km, 1, ' ', 4, 72, 5, 2, M_COL_TXT, M_COL_BCK, 1);
				else if (as_km<10000) lcd_putnr(as_km/10, 0, ' ', 4, 80, 5, 2, M_COL_TXT, M_COL_BCK, 1);
				lcd_putstring(PSTR(TXT_l100Km),120,39,0,COL_TXT_LCD1, M_COL_BCK,1);
#endif
#ifdef MPH
	float tmp2;
				tmp2=as_km;
				tmp2=4.55/(tmp2/10000);
				if (tmp2>=10000||as_km==0) 
				{
					lcd_putstring(PSTR(" ---"),80,5,2,M_COL_TXT, M_COL_BCK,1);
				}
				else
				{
					lcd_putnr(tmp2/10, 0, ' ', 4, 80, 5, 2, M_COL_TXT, M_COL_BCK, 1);
					lcd_putstring(PSTR(TXT_l100Km),120,39,0,COL_TXT_LCD1, M_COL_BCK,1);
				}
#endif
			}


			//----------------------Napatie---------------------------
		 	tmp_color=M_COL_BCK;
			b=M_COL_TXT;
			if (motor_on)
			{
				if (napatie<=BAT_INVERS)
				{
					tmp_color=YELLOW;//0xD8;
					b=BLACK;
				}
				if (napatie<=BAT_BEEP) 
				{
					tmp_color=RED;//0xD8;
					b=WHITE;
				}
			}
			lcd_putnr(napatie/10, 1, ' ', 3, 18, 72, 1, b, tmp_color, 1);
			lcd_putstring(PSTR(TXT_V),74,84,0,COL_TXT_LCD1,M_COL_BCK,1);
			lcd1_stav=1;
			break;

		case 1 :
			//----------------------Teplota---------------------------
			temp=teplota;
			a=M_COL_BCK;
			b=M_COL_TXT;
			if (temp<=NAMRAZA)
			{ 
				a=BLUE;
				b=WHITE;
			}
			if (temp<0)
			{
				temp=0xFFFF-temp+1;
				lcd_putstring(PSTR("-"),16,108,1,b,a,1);
				lcd_putnr((temp+5)/10, 0, ' ', 2, 32, 108, 1,b, a, 1);
			}
			else lcd_putnr((temp+5)/10, 0, ' ', 3, 16, 108, 1,b, a, 1);
			lcd_putstring(PSTR(TXT_OUT),64,108,0,COL_TXT_LCD1,M_COL_BCK,1);
			lcd_putstring(PSTR("C"),72,120,0,COL_TXT_LCD1,M_COL_BCK,1);
			lcd_putchar(128,64,120,0,COL_TXT_LCD1,M_COL_BCK,1);


			if (M_COL_BCK==BLUE||M_COL_BCK==RED)
			{
				tmp_color=GREEN;
				tmp_color1=GREEN;
			}
			else
			{
				tmp_color=RED;
				tmp_color1=BLUE;
			}

			lcd_put_bw_picture(TEPLOTA_S,2,108,1,IKONA_X,12,tmp_color,M_COL_BCK,1);
			lcd_put_bw_picture(TEPLOTA_S+24,2,120,1,IKONA_X,12,tmp_color1,M_COL_BCK,1);

	

			if(teplota_motoru_cidlo&&teplota_motoru<TEPLOTA_MOTORU_MIN) lcd_put_bw_picture(T_OLEJ_S,76,52,1,T_OLEJ_X,T_OLEJ_Y,WHITE,BLUE,1);
			else if(teplota_motoru_cidlo&&teplota_motoru>TEPLOTA_MOTORU_MAX) lcd_put_bw_picture(T_OLEJ_S,76,52,1,T_OLEJ_X,T_OLEJ_Y,WHITE,RED,1);
			else lcd_put_bw_picture(T_OLEJ_S,76,52,1,T_OLEJ_X,T_OLEJ_Y,M_COL_BCK,M_COL_BCK,1);


			//---------------------Hodiny-----------------------------
			lcd_putnr(hodiny_h, 0, '0', 2, 106, 108, 1, M_COL_TXT, M_COL_BCK, 1);
			lcd_putchar(':',138,108,1,M_COL_TXT,M_COL_BCK,1);
			lcd_putnr(hodiny_m, 0, '0', 2, 144, 108, 1, M_COL_TXT, M_COL_BCK, 1);


			if (pal_korekcia!=6)
			{
				tmp=(n_posledna_hodnota*1000)-((spotrebovane_palivo-n_spotrebovane_palivo));
				if (tmp<0) tmp=0;

				tmp1=(tmp*10)/(((vypocet_priemerna_spotreba(5)*POMER_DOJAZD_C)+(priemerna_spotreba_pv*POMER_DOJAZD_PV)));
				if (tmp1>99) tmp1=99;



					tmp_color=M_COL_BCK;
				a=M_COL_TXT;
				if (tmp1<=REZERVA_DOJAZD) 
				{
					tmp_color=RED;
					a=WHITE;
				}

				#ifdef DEVELOP
				if(ChckBit(hodiny_s,1))
				{
				#endif
					lcd_putnr(tmp1*10, 0, ' ', 3, 112, 72, 1, a, tmp_color, 1);
					lcd_putstring(PSTR(TXT_KM),160,84,0,COL_TXT_LCD1,M_COL_BCK,1);
				#ifdef DEVELOP
				}
				else
				{
					lcd_putnr(tmp/1000, 0, ' ', 3, 112, 72, 1, a, tmp_color, 1);
					//lcd_putnr(pal_act, 0, ' ', 3, 112, 72, 1, a, tmp_color, 1);
					lcd_putstring(PSTR("L "),160,84,0,COL_TXT_LCD1,M_COL_BCK,1);
				}
				#endif
			}
/*			else
			{
					lcd_putstring(PSTR("F"),144,72,1,M_COL_TXT,M_COL_BCK,1);
					lcd_putstring(PSTR(TXT_KM),160,84,0,COL_TXT_LCD1,M_COL_BCK,1);
			}
*/
			if (M_COL_BCK==GREEN) tmp_color=BLUE;
			else tmp_color=GREEN;

			if (pal_korekcia!=6) lcd_put_bw_picture(NADRZ_S,96,72,1,IKONA_X,IKONA_Y,tmp_color,M_COL_BCK,1);
			lcd_put_bw_picture(BATERKA_S,2,72,1,IKONA_X,IKONA_Y,tmp_color,M_COL_BCK,1);
			lcd1_stav=0;
			break;
	}	
	
}

//------------------------------------------Výpoèty-----------------------

unsigned long vypocet_km(unsigned char cis)
{
	if (cis==5) return(km);
	else if (cis<3)
	{
		if (status_ss[cis]) km_denne[cis]=km;
		return(km-km_denne[cis]+km_ss[cis]);
	}
	else return(km-km_denne[cis]);
}

unsigned long vypocet_spotrebovane_palivo(unsigned char cis)
{
	if (cis==5) return(spotrebovane_palivo);
	else if (cis<3)
	{
		if (status_ss[cis]) spotrebovane_palivo_denne[cis]=spotrebovane_palivo;
		return(spotrebovane_palivo-spotrebovane_palivo_denne[cis]+spotrebovane_palivo_ss[cis]);
	}
	else return(spotrebovane_palivo-spotrebovane_palivo_denne[cis]);
}

unsigned long vypocet_doba_jazdy(unsigned char cis)
{
	if (cis==5) return(doba_jazdy);
	else if (cis<3)
	{
		if (status_ss[cis]) doba_jazdy_denne[cis]=doba_jazdy;
		return(doba_jazdy-doba_jazdy_denne[cis]+doba_jazdy_ss[cis]);
	}
	else return(doba_jazdy-doba_jazdy_denne[cis]);
}

unsigned int vypocet_priemerna_spotreba(unsigned char cis)
{
	return(((vypocet_spotrebovane_palivo(cis)*100)/vypocet_km(cis)));
}

unsigned int vypocet_priemerna_rychlost(unsigned long vzdialenost, unsigned long cas)
{
	if (cas<36) return(0);
	
	if(cas<360000) return((vzdialenost*100)/((cas*1000+hodiny_ms)/360));
	else return((vzdialenost)/(cas/36));
	return(0);
}


void reset_denne(unsigned char a)
{
	km_denne[a]=km;
	spotrebovane_palivo_denne[a]=spotrebovane_palivo;
	max_spd_denne[a]=0;
	doba_jazdy_denne[a]=doba_jazdy;
	
	if (a<3)
	{
		km_ss[a]=0;
		spotrebovane_palivo_ss[a]=0;
		doba_jazdy_ss[a]=0;
		status_ss[a]=0;
	}
}


