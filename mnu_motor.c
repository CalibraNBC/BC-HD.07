#include "mnu_motor.h"
#include "menu.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "language.h"
#include "definitions.h"
#include "keys.h"
#include <avr/pgmspace.h>
#include "mnu_pretazenie.h"
#include "main.h"


char mnu_motor(void)
{
	unsigned char y;
	unsigned char col;
	unsigned char	graph_back_color;
	unsigned int lambda_tmp;
	unsigned char wbl_lambda_low, wbl_lambda_high;
	unsigned long	tmplong;

	lcd_putnr(otacky*10, 0, ' ', 4, 80, 0, 2, M_COL_TXT, M_COL_BCK, 2);
	
	lcd_putstring(PSTR(TXT_OTACKY),0,0,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR(TXT_MAX),0,12,0,COL_TXT_LCD2,M_COL_BCK,2);
	
	lcd_putnr(otacky_max*10, 0, ' ', 4, 32, 12, 0, M_COL_TXT, M_COL_BCK, 2);


	y=48;

/*
teplota_motoru=96;
teplota_motoru_cidlo=1;
*/
	if(teplota_motoru_cidlo) 
	{
		y=84;
		col=M_COL_BCK;
		if(teplota_motoru<TEPLOTA_MOTORU_MIN) col=BLUE;
		if(teplota_motoru>TEPLOTA_MOTORU_MAX) col=RED;
		lcd_putstring(PSTR(TXT_TEPLOTA_MOTORU),0,48,0,COL_TXT_LCD2,M_COL_BCK,2);
		if(teplota_motoru)	lcd_putnr(teplota_motoru, 0, ' ', 3, 112, 48, 1, M_COL_TXT, col, 2);
		else lcd_putstring(PSTR("---"),112,48,1,M_COL_TXT,M_COL_BCK,2);
		lcd_putstring(PSTR("C"),168,48,0,COL_TXT_LCD1,M_COL_BCK,2);
		lcd_putchar(128,160,48,0,COL_TXT_LCD1,M_COL_BCK,2);
	}
	else 
	{
		lcd_putstring(PSTR("                      "),0,60,0,COL_TXT_LCD1,M_COL_BCK,2);
		lcd_putstring(PSTR("                      "),0,84,0,COL_TXT_LCD1,M_COL_BCK,2);
	}

	lcd_putstring(PSTR(TXT_DLZKA_VSTREKU),0,y,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putnr(doba_vstreku/10, 1, ' ', 4, 123, y, 0, M_COL_TXT, M_COL_BCK, 2);
	lcd_putstring(PSTR("ms"),160,y,0,COL_TXT_LCD2,M_COL_BCK,2);

	meranie_lambdy();

/*	
	wbl_afr=(wbl_afr+1)*3;
	if (wbl_afr>500)wbl_afr=wbl_afr-500;
	if (wbl_afr>500)wbl_afr=wbl_afr-500;
	if (wbl_afr>500)wbl_afr=wbl_afr-500;
	lambda=wbl_afr;
*/
	if(lambda_on)
	{
		if(M_COL_BCK==YELLOW||M_COL_BCK==GREEN||M_COL_BCK==RED) graph_back_color=BLACK;
		else graph_back_color=M_COL_BCK;

		if(lambda_on<4)
		{
			lcd_putstring(PSTR(TXT_LAMBDA),2,103,0,COL_TXT_LCD2,M_COL_BCK,2);
			lcd_putnr(lambda, 2, ' ', 3, 2, 115, 0, M_COL_TXT, M_COL_BCK, 2);
			lcd_putstring(PSTR(TXT_V),30,115,0,COL_TXT_LCD2,M_COL_BCK,2);
		}
		else
		{
			tmplong=wbl_afr_0V+(lambda*((wbl_afr_5V-wbl_afr_0V)/0.5)+500)/1000;
			lcd_putnr(tmplong, 1, ' ', 3, 2, 103, 1, M_COL_TXT, M_COL_BCK, 2);
		}



		if(lambda_on>2) lambda=lambda/5;

		if(lambda>100)lambda_tmp=100;
		else lambda_tmp=lambda;

		if(lambda_on<3)
		{
			if(lambda_tmp<LAMBDA_LOW)
			{
				obdlznik(75, 104, lambda_tmp, 22, RED);
				obdlznik(lambda_tmp+75, 104, LAMBDA_LOW-lambda_tmp, 22, graph_back_color);

				obdlznik(LAMBDA_LOW+76, 104, LAMBDA_HIGH-LAMBDA_LOW-1, 22, graph_back_color);
				obdlznik(LAMBDA_HIGH+76, 104, 99-LAMBDA_HIGH, 22, graph_back_color);
			}

			if(lambda_tmp>=LAMBDA_LOW&&lambda_tmp<=LAMBDA_HIGH)
			{
				obdlznik(76+LAMBDA_LOW, 104, lambda_tmp-LAMBDA_LOW, 22, GREEN);
				obdlznik(lambda_tmp+75, 104, LAMBDA_HIGH-lambda_tmp, 22, graph_back_color);

				obdlznik(75, 104, LAMBDA_LOW, 22, GREEN);
				obdlznik(LAMBDA_HIGH+76, 104, 99-LAMBDA_HIGH, 22, graph_back_color);
			}

			if(lambda_tmp>LAMBDA_HIGH)
			{
				obdlznik(76+LAMBDA_HIGH, 104, lambda_tmp-LAMBDA_HIGH, 22, YELLOW);
				obdlznik(lambda_tmp+75, 104, 100-lambda_tmp, 22, graph_back_color);


				obdlznik(75, 104, LAMBDA_LOW, 22, YELLOW);
				obdlznik(76+LAMBDA_LOW, 104, LAMBDA_HIGH-1-LAMBDA_LOW, 22, YELLOW);
			}
			obdlznik(75+LAMBDA_LOW, 101, 1, 28, COL_TXT_LCD2);
			obdlznik(75+LAMBDA_HIGH, 101, 1, 28, COL_TXT_LCD2);
		}
		else if(lambda_on==3)
		{
				obdlznik(75, 104, lambda_tmp, 22, GREEN);
				obdlznik(lambda_tmp+75, 104, 100-lambda_tmp, 22, graph_back_color);
		}
		else
		{
			
			wbl_lambda_low=((wbl_limitok-wbl_afr_0V)*100)/(wbl_afr_5V-wbl_afr_0V);
			wbl_lambda_high=((wbl_limitnok-wbl_afr_0V)*100)/(wbl_afr_5V-wbl_afr_0V);


			if(lambda_tmp<wbl_lambda_low)
			{
				obdlznik(75, 104, lambda_tmp, 22, GREEN);
				obdlznik(lambda_tmp+75, 104, wbl_lambda_low-lambda_tmp, 22, graph_back_color);

				obdlznik(wbl_lambda_low+76, 104, wbl_lambda_high-wbl_lambda_low-1, 22, graph_back_color);
				obdlznik(wbl_lambda_high+76, 104, 99-wbl_lambda_high, 22, graph_back_color);
			}

			if(lambda_tmp>=wbl_lambda_low&&lambda_tmp<=wbl_lambda_high)
			{
				obdlznik(76+wbl_lambda_low, 104, lambda_tmp-wbl_lambda_low, 22, YELLOW);
				obdlznik(lambda_tmp+75, 104, wbl_lambda_high-lambda_tmp, 22, graph_back_color);

				obdlznik(75, 104, wbl_lambda_low, 22, YELLOW);
				obdlznik(wbl_lambda_high+76, 104, 99-wbl_lambda_high, 22, graph_back_color);
			}

			if(lambda_tmp>wbl_lambda_high)
			{
				obdlznik(76+wbl_lambda_high, 104, lambda_tmp-wbl_lambda_high, 22, RED);
				obdlznik(lambda_tmp+75, 104, 100-lambda_tmp, 22, graph_back_color);


				obdlznik(75, 104, wbl_lambda_low, 22, RED);
				obdlznik(76+wbl_lambda_low, 104, wbl_lambda_high-1-wbl_lambda_low, 22, RED);
			}
			obdlznik(75+wbl_lambda_low, 101, 1, 28, COL_TXT_LCD2);
			obdlznik(75+wbl_lambda_high, 101, 1, 28, COL_TXT_LCD2);
		}

		obdlznik(74, 103, 102, 1, COL_TXT_LCD2);
		obdlznik(74, 103, 1, 24, COL_TXT_LCD2);
		obdlznik(74, 126, 102, 1, COL_TXT_LCD2);
		obdlznik(175, 103, 1, 24, COL_TXT_LCD2);


	}

	if (tlacitka()==2) return(1); 

	if (tlacitka()==1) 
	{
		otacky_max=0;
	}


	return(0);
}



void vypocet_ot_motoru(void)
{
	unsigned long temp;
	temp=ot_imp_old;

	otacky=(temp*12000)/ot_cas_old/otacky_del;
	if (otacky>1000) otacky=0;

	if (otacky_max<otacky) otacky_max=otacky;

	ot_imp_old=0;
	ot_cas_old=0;
}


void meranie_lambdy(void)
{
	unsigned int tmp;

	nastav_ad(IN_OUT_2);

	if(lambda_on==2)
	{
		tmp=get_advalue()*kv2;
		if(tmp<10) lambda_meas=0;
		if(lambda_meas==3)
		{
		 	lambda=lambda_old1;
			lambda_old1=lambda_old;
			lambda_old=tmp;
		}
		if(lambda_meas==2)
		{
			lambda_old1=lambda_old;
			lambda_old=tmp;
			lambda_meas++;
		} 				
		if(lambda_meas==1)
		{
			lambda_old=tmp;
			lambda_meas++;
		} 				
		if(!lambda_meas&&tmp>10) lambda_meas++;	
		if(!doba_vstreku)	lambda=0;
	}	
	else
	{
		lambda=get_advalue()*kv2;
	}	

}
