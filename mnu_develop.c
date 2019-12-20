#include "mnu_develop.h"
#include "menu.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "language.h"
#include "definitions.h"
#include "keys.h"
#include <avr/pgmspace.h>
#include "accelerometer.h"
#include "main.h"
#include <avr/eeprom.h>
#include "int_ee.h"
#include "meranie_nadrze.h"
#include "mnu_bc.h"
#include "input_int.h"


typedef unsigned char BYTE;
BYTE *p_ee_zero5=(BYTE*) 0;

unsigned char pal[30];

char mnu_develop(void)
{
	unsigned char y=0;//, a, b, c, d, e,f;
	unsigned char tmp;
//	unsigned int tmpint;
	float tmpfloat, tmp3;
//	long tmplong;
  unsigned long tmp1;


	zmeraj_pretazenie();
	lcd_putstring(PSTR("Naklon"),0,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("X"),80,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("Y"),128,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	tmp=accelerometer_x;
	lcd_putnr(tmp, 0, ' ', 3, 88, y, 0, M_COL_TXT, M_COL_BCK, 2);
	tmp=accelerometer_y;
	lcd_putnr(tmp, 0, ' ', 3, 136, y, 0, M_COL_TXT, M_COL_BCK, 2);
	y=y+12;

	lcd_putstring(PSTR("Ext"),0,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	nastav_ad(IN_OUT_1);
//	tmpfloat=181;
//	kv1=tmpfloat/get_advalue();

	lcd_putnr(get_advalue()*kv1, 2, ' ', 5, 32, y, 0, M_COL_TXT, M_COL_BCK, 2);
	nastav_ad(IN_OUT_2);
	lcd_putnr(get_advalue()*kv2, 2, ' ', 4, 88, y, 0, M_COL_TXT, M_COL_BCK, 2);
	nastav_ad(IN_OUT_3);
	lcd_putnr(get_advalue()*kv3, 2, ' ', 4, 136, y, 0, M_COL_TXT, M_COL_BCK, 2);
	y=y+12;
	
	lcd_putstring(PSTR("BL"),0,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(sv_nap, 2, ' ', 4, 16, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR("TMP"),60,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	nastav_ad(TEPLOTA);
	tmp3=1024;
	tmpfloat=(((kvt*tmp3)/(tmp3-get_advalue()))-kvt);
	if (tmpfloat>99999) tmpfloat=99999;
	lcd_putnr(tmpfloat/10, 2, ' ', 4, 84, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR("U"),128,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	meranie_baterky();
	lcd_putnr(napatie, 2, ' ', 4, 136, y, 0, M_COL_TXT, M_COL_BCK, 2);
	y=y+12;

	lcd_putstring(PSTR("CER-"),0,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(ChckBit(PINB,3), 0, ' ', 1, 32, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR("VST-"),48,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(ChckBit(PINB,2), 0, ' ', 1, 80, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR("KOL-"),96,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(ChckBit(PINB,1), 0, ' ', 1, 128, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR("15-"),144,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(ChckBit(PINB,0), 0, ' ', 1, 168, y, 0, M_COL_TXT, M_COL_BCK, 2);
	y=y+12;

	lcd_putstring(PSTR("PrSpot N"),0,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	tmp1=((vypocet_priemerna_spotreba(5)*POMER_DOJAZD_C)+(priemerna_spotreba_pv*POMER_DOJAZD_PV));
	lcd_putnr(priemerna_spotreba_pv, 1, ' ', 3, 72, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR("P"),112,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(tmp1/10, 2, ' ', 4, 120, y, 0, M_COL_TXT, M_COL_BCK, 2);
	y=y+12;

	if (tlacitka()==2) return(1); 

	if (tlacitka()==1) 
	{
		otacky_max=0;
	}


	return(0);
}


char mnu_develop2(void)
{
	unsigned char y=0, a, b, c, d, e,f;
//	unsigned char tmp;
	unsigned int tmpint;
//	float tmpfloat, tmp3;
	long tmplong;
 // unsigned long tmp1;

	menu_nr[1]++;
	if (menu_nr[1]>20) menu_nr[1]=0;

	lcd_putstring(PSTR("PAL AKT"),0,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	nastav_ad(PALIVO);
	tmpint=get_advalue();
	lcd_putnr(tmpint*kp, 2, ' ', 4, 56, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(hodnota_paliva(tmpint), 0, ' ', 2, 96, y, 0, M_COL_TXT, M_COL_BCK, 2);

	lcd_putstring(PSTR("P"),120,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	tmplong=(n_posledna_hodnota*1000)-((spotrebovane_palivo-n_spotrebovane_palivo));
	if (tmplong<0) tmplong=0;
	lcd_putnr(tmplong/10, 2, ' ', 5, 128, y, 0, M_COL_TXT, M_COL_BCK, 2);
	y=y+12;

	c=0;
	d=254;
	e=0;
	for (a=0;a<POC_MERANI_PALIVA;a++)
	{
		if (pal_tmp[a]<d) d=pal_tmp[a];
		if (pal_tmp[a]>e) e=pal_tmp[a];
	}

	while(c<POC_MERANI_PALIVA)
	{
		b=0;
		while (c<POC_MERANI_PALIVA&&b<160)
		{
			lcd_putnr(pal_tmp[c], 0, ' ', 2, b, y, 0, M_COL_TXT, M_COL_BCK, 2);
			c=c+1;
			b=b+24;
		}
		y=y+12;
	}
	if (d+N_MIN_ODCHYLKA<e) f=RED;
	else f= GREEN;
	lcd_putnr(d, 0, ' ', 2, 0, y, 1, M_COL_TXT, f, 2);
	lcd_putnr(e, 0, ' ', 2, 48, y, 1, M_COL_TXT, f, 2);
	lcd_putnr(e-d, 0, ' ', 2, 88, y, 1, M_COL_TXT, f, 2);
	lcd_putnr((e+d)/2, 0, ' ', 2, 144, y, 1, M_COL_TXT, f, 2);


	if (tlacitka()==2) return(1); 

	if (tlacitka()==1) 
	{
		otacky_max=0;
	}


	return(0);
}


char mnu_develop3(void)
{
	unsigned char a,b,d;
	unsigned int tmpint;

	
	if(!menu_nr[1]) for(a=0;a<70;a++) eeprom_read_block(&dndevelop[a],p_ee_zero5 + EE_DN+(a)*2,2);

	lcd_putstring(PSTR("PAL AKT"),0,0,0,COL_TXT_LCD2,M_COL_BCK,2);
	nastav_ad(PALIVO);
	tmpint=get_advalue();
	lcd_putnr(tmpint*kp, 2, ' ', 4, 56, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(hodnota_paliva(tmpint), 0, ' ', 2, 96, 0, 0, M_COL_TXT, M_COL_BCK, 2);


	d=0;
	for (b=0;b<3;b++)
	{
		for (a=0;a<10;a++)
		{
			if(menu_nr[1]-1==a+d) lcd_putnr(a+d, 0, ' ', 2, b*64, a*12+12, 0, M_COL_BCK, M_COL_TXT, 2);
			else lcd_putnr(a+d, 0, ' ', 2, b*64, a*12+12, 0, M_COL_TXT, M_COL_BCK, 2);
			if(menu_nr[2]&&menu_nr[1]-1==a+d) lcd_putnr(dndevelop[a+d], 0, ' ', 3, b*64+24, a*12+12, 0, M_COL_BCK, M_COL_TXT, 2);
			else lcd_putnr(dndevelop[a+d], 0, ' ', 3, b*64+24, a*12+12, 0, M_COL_TXT, M_COL_BCK, 2);
		}
		d=d+10;
	}



	if (tlacitka()==2)
	{ 
		if(!menu_nr[1]) return(1);
		else 
		{
			dndevelop[menu_nr[1]-1]++;
			menu_nr[2]=20;
		}
	}

	if (tlacitka()==1) 
	{
		if(!menu_nr[2])
		{
			if (tlacitka_long()) menu_nr[1]=menu_nr[1]-2;
			else menu_nr[1]++;
			if(menu_nr[1]==31)
			{
				for(a=0;a<70;a++) 
				{
					zapis_ee(dndevelop[a],p_ee_zero5 + EE_DN+(a)*2,2);
					dn[a]=dndevelop[a];
				}
				return(1);
			}
		}
		else 
		{
			dndevelop[menu_nr[1]-1]--;
			menu_nr[2]=20;
		}

	}
	
	if(menu_nr[2])menu_nr[2]--;

	return(0);

}


char mnu_develop4(void)
{
	unsigned char a,b,d;
	unsigned int tmpint;

	
	lcd_putstring(PSTR("PAL AKT"),0,0,0,COL_TXT_LCD2,M_COL_BCK,2);
	nastav_ad(PALIVO);
	tmpint=get_advalue();
	lcd_putnr(tmpint*kp, 2, ' ', 4, 56, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(hodnota_paliva(tmpint), 0, ' ', 2, 96, 0, 0, M_COL_TXT, M_COL_BCK, 2);


	
	d=0;
	for (b=0;b<3;b++)
	{
		for (a=0;a<10;a++)
		{
			if(menu_nr[1]-1==a+d) lcd_putnr(a+d+30, 0, ' ', 2, b*64, a*12+12, 0, M_COL_BCK, M_COL_TXT, 2);
			else lcd_putnr(a+d+30, 0, ' ', 2, b*64, a*12+12, 0, M_COL_TXT, M_COL_BCK, 2);
			if(menu_nr[2]&&menu_nr[1]-1==a+d) lcd_putnr(dndevelop[a+d+30], 0, ' ', 3, b*64+24, a*12+12, 0, M_COL_BCK, M_COL_TXT, 2);
			else lcd_putnr(dndevelop[a+d+30], 0, ' ', 3, b*64+24, a*12+12, 0, M_COL_TXT, M_COL_BCK, 2);
		}
		d=d+10;
	}



	if (tlacitka()==2)
	{ 
		if(!menu_nr[1]) return(1);
		else 
		{
			dndevelop[menu_nr[1]-1+30]++;
			menu_nr[2]=20;
		}
	}

	if (tlacitka()==1) 
	{
		if(!menu_nr[2])
		{
			if (tlacitka_long()) menu_nr[1]=menu_nr[1]-2;
			else menu_nr[1]++;
			if(menu_nr[1]==31)
			{
				for(a=0;a<70;a++) 
				{
					zapis_ee(dndevelop[a],p_ee_zero5 + EE_DN+(a)*2,2);
					dn[a]=dndevelop[a];
				}
				return(1);
			}
		}
		else 
		{
			dndevelop[menu_nr[1]-1+30]--;
			menu_nr[2]=20;
		}

	}
	
	if(menu_nr[2])menu_nr[2]--;

	return(0);

}


char mnu_develop5(void)
{
	unsigned char a,b,d;
	unsigned int tmpint;

	
	lcd_putstring(PSTR("PAL AKT"),0,0,0,COL_TXT_LCD2,M_COL_BCK,2);
	nastav_ad(PALIVO);
	tmpint=get_advalue();
	lcd_putnr(tmpint*kp, 2, ' ', 4, 56, 0, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(hodnota_paliva(tmpint), 0, ' ', 2, 96, 0, 0, M_COL_TXT, M_COL_BCK, 2);


	b=0;
	d=0;
		for (a=0;a<10;a++)
		{
			if(menu_nr[1]-1==a+d) lcd_putnr(a+d+60, 0, ' ', 2, b*64, a*12+12, 0, M_COL_BCK, M_COL_TXT, 2);
			else lcd_putnr(a+d+60, 0, ' ', 2, b*64, a*12+12, 0, M_COL_TXT, M_COL_BCK, 2);
			if(menu_nr[2]&&menu_nr[1]-1==a+d) lcd_putnr(dndevelop[a+d+60], 0, ' ', 3, b*64+24, a*12+12, 0, M_COL_BCK, M_COL_TXT, 2);
			else lcd_putnr(dndevelop[a+d+60], 0, ' ', 3, b*64+24, a*12+12, 0, M_COL_TXT, M_COL_BCK, 2);
		}



	if (tlacitka()==2)
	{ 
		if(!menu_nr[1]) return(1);
		else 
		{
			dndevelop[menu_nr[1]-1+60]++;
			menu_nr[2]=20;
		}
	}

	if (tlacitka()==1) 
	{
		if(!menu_nr[2])
		{
			if (tlacitka_long()) menu_nr[1]=menu_nr[1]-2;
			else menu_nr[1]++;
			if(menu_nr[1]==11)
			{
				for(a=0;a<70;a++) 
				{
					zapis_ee(dndevelop[a],p_ee_zero5 + EE_DN+(a)*2,2);
					dn[a]=dndevelop[a];
				}
				return(1);
			}
		}
		else 
		{
			dndevelop[menu_nr[1]-1+60]--;
			menu_nr[2]=20;
		}

	}
	
	if(menu_nr[2])menu_nr[2]--;

	return(0);

}


char mnu_develop6(void)
{
	unsigned int tmpint;




	lcd_putstring(PSTR("Lambda voltage"),0,0,0,COL_TXT_LCD2,M_COL_BCK,2);
	nastav_ad(IN_OUT_2);
	tmpint=get_advalue();
	lcd_putnr(tmpint*kv2, 2, ' ', 4, 120, 0, 0, M_COL_TXT, M_COL_BCK, 2);


	wbl_ratio=(wbl_afr_5V-wbl_afr_0V)/0.5;
	wbl_afr=wbl_afr_0V+((tmpint*kv2)*wbl_ratio)/1000;




	lcd_putstring(PSTR("AFR*10 at 0V"),0,12,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("AFR*10 at 5V"),0,24,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(wbl_afr_0V, 0, ' ', 3, 120, 12, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(wbl_afr_5V, 0, ' ', 3, 120, 24, 0, M_COL_TXT, M_COL_BCK, 2);

	lcd_putstring(PSTR("AFR="),0,36,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(wbl_afr, 1, ' ', 3, 120, 36, 0, M_COL_TXT, M_COL_BCK, 2);

	lcd_putstring(PSTR("green<"),0,60,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("yellow>"),72,60,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("red"),152,60,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(wbl_limitok, 0, ' ', 3, 48, 60, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(wbl_limitnok, 0, ' ', 3, 128, 60, 0, M_COL_TXT, M_COL_BCK, 2);






			if (tlacitka()==1) 
			{
				menu_nr[1]=1;
				wbl_afr_0V=input_int(120,12,0,3,wbl_afr_0V,999);
				wbl_afr_5V=input_int(120,24,0,3,wbl_afr_5V,999);
				wbl_limitok=input_int(48,60,0,3,wbl_limitok,255);
				wbl_limitnok=input_int(128,60,0,3,wbl_limitnok,255);
			}

	if (tlacitka()==2) return(1);



	return(0);

}
