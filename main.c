#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "main.h"
#include "i2c.h"
#include "settings.h"
#include "int_ee.h"
#include "language.h"
#include "variables.h"
#include "definitions.h"
#include "accelerometer.h"
#include "menu.h"
#include "meranie_spotreby.h"
#include "meranie_vzdialenosti_rychlosti.h"
#include "meranie_teploty.h"
#include "meranie_nadrze.h"
#include "delay.h"
#include "keys.h"
#include "beep.h"
#include "meranie_baterky.h"
#include "meranie_podsvietenia.h"
#include "lcd_s65_ls020.h"
#include "mnu_max_hodnoty.h"
#include "mnu_bc.h"
#include "zrychlenie.h"
#include "verzia.h"
#include "eeprom_24Cxx.h"
#include "vystraha.h"
#include "logo.h"
#include "reset.h"
#include "mnu_motor.h"
#include "mnu_400m.h"
#include "mnu_stopky.h"
#include "nadrz.h"

unsigned int ppp;

int main(void)
{ 



	set_ports();
	lcd_type=1;
	lcd_init();

	M_COL_BCK=BLACK;
	M_COL_TXT=WHITE;
 
	COL_TXT_LCD2=GREY;
	COL_TXT_LCD1=GREY;


	i2c_init();
	accelerometer_init();

/*
	if (skontroluj_ee())
	{ 
//		chyba(skontroluj_ee());
		while(1);
	}
*/

	nacitaj_nastavenia();
	nacitaj_data();
	nast_cpu();
	sv_hodnota=3;
	poc_bc_menu=1;
	mnu_zrychlenie_on=1;
	mnu_pretazenie_on=1;
	mnu_motor_on=1;
	mnu_400m_on=1;
	mnu_develop_on=0;
	mnu_max=MNU_DEVELOP_NR;
	otacky_del=1;
	hodiny_on=0;
	kavicka_s=14400; //14400=4h
	mnu_stopky_on=1;
	lambda_on=0;
	hodiny_h=12;
	PORTB=8;

	nadrz();

	reset();

//	logo(1);	

/*
	wbl_ratio=125;
	wbl_plus=70;
	wbl_lambda1=147;
*/

	wbl_afr_0V=103;
	wbl_afr_5V=194;
	wbl_limitok=135;
	wbl_limitnok=160;

	zmena_menu(MNU_NASTAVENIA_NR);


	while(1) 
	{

//		ppp=hodiny_ms;

		power_down();
		menu();
		zmeraj_nadrz();

//			if (ppp>hodiny_ms) ppp=ppp-1000;
//			lcd_putnr(hodiny_ms-ppp, 0, ' ', 6, 0, 48, 0, M_COL_TXT, M_COL_BCK, 1);


		if (menu_nr[0]!=MNU_NASTAVENIA_NR) zobraz_lcd1();
		else verzia();

		zmeraj_nadrz();

		operacie_na_pozadi();

	}
}



void operacie_na_pozadi(void)
{



	poc_stav++;
	switch (stav)
	{
//-----------------------------1x/1s----------------------------------------
		case 0 :
//			lcd_putnr(poc_stav, 0, ' ', 2, 80, 48, 0, M_COL_TXT, M_COL_BCK, 1);
//			poc_stav=0;

			zmeraj_pretazenie();
			reset_jazdy();
			kavicka();
			vypocet_ot_motoru();
			stav=1;
			break;
		case 1 :
//			meranie_nadrze();
			meranie_teploty();
			zapis_nadrz();
			stav=2;
			break;
		case 2 :
			meranie_baterky();
			meranie_spotreby_za_poslednu_vzdialenost();
			stav=3;
			break;
		case 3 :
			meranie_podsvietenia();
			max_hodnoty_zapis();
			stav=4;
			break;

		case 4 :
			meranie_teploty_motoru();
			stav=5;
			break;
		case 5:
		stav=6;
			break;
		case 6:
			stav=7;
			break;
		case 7:
			stav=8;
			break;
		case 8:
			stav=9;
			break;
		case 9:
			stav=10;
			break;
	}
}



void power_down(void)
{
	if (!POWER_OFF) return;
	lcd_clr_dspl(M_COL_BCK,1);
	logo(1);	
	if (!POWER_OFF) return;
//------------------------Prechod do spánku-----------
	motor_on=0;
	TCCR2B=0;

	if (zapis_dat()) 
	{
//		chyba(ERR_EE_DATA_BC);
	//	while (!tlacitka());
		zapis_dat();
	}
	ADCSRA=0;
	accelerometer_stby();
	reset_j=1;
	as_h=0;

	if(hodiny_on)
	{
		lcd_clr_dspl(BLACK,1);
		//---------------------Hodiny-----------------------------
		lcd_putnr(hodiny_h, 0, '0', 2, 4, 36, 4, WHITE, BLACK, 1);
		lcd_putchar(':',86,43,3,WHITE,BLACK,1);
		lcd_putnr(hodiny_m, 0, '0', 2, 100, 36, 4, WHITE, BLACK, 1);
	}
	else lcd_off(1);

	lcd_off(2);
	sv_hodnota=0;


//-------------------------Režim spánku---------------
	while POWER_OFF
	{

#ifdef HW09
		if(hodiny_on) PORTD=0x20;
		else PORTD=0x00;
#endif

#ifdef HW08S65
		if(hodiny_on) PORTD=0x02;
		else PORTD=0x00;
#endif
		ClrBit(DDRB,5);
		PRR0=0b11011111;	//vypnutie SPI
		SMCR=0b00000000;  //39H1
		SetBit(SMCR,SE);
		asm("sleep");

	}
//------------------------Prechod zo spánku-----------
	set_ports();
	PRR0=0;
	nast_cpu();
	lcd_init();
	i2c_init();
	accelerometer_init();
	sv_hodnota=3;
	lcd_clr_dspl(M_COL_BCK,1);
	lcd_on(1);
	lcd_on(2);
	if ((servis_km+servis)<=(km/100)) vystraha(OLEJ_S, 55, 75, 2, OLEJ_X, OLEJ_Y, 1, 2);
	if (menu_nr[0]==MNU_NASTAVENIA_NR) zmena_menu(MNU_NASTAVENIA_NR);
	battery_beep_s=0;
	nadrz_status=0;
 	n_obsah_temp=0xFFFF;
	sig_namrazy=1;
	sig_nadrze=1;
	pal_start=1;
	stav=0;
#ifndef DEVELOP
	logo(1);
#endif
}



ISR(TIMER0_COMPA_vect)	//Prerušenie každú 1ms.
{
	as_timer++;
	vypocet_aktualnej_rychlosti();
 	hodiny();
	bcklight();	
	zrychlenie();	
	meranie_400m();
	stopky();

	if (TCCR2B) dlzka_vstreku=dlzka_vstreku+1;		//Kompenzácia za dåžku trvania Timer0
}




//----------------------------------------------Podsvietenie---------------------
void bcklight(void)
{
	sv_odpocet--;
	if (sv_odpocet>=sv_hodnota) BACKLIGHT_OFF;
	else BACKLIGHT_ON;
	if (sv_odpocet==0) sv_odpocet=3;
}


//---------------------------------------------Hodiny---------------------------
void hodiny(void)
{
	hodiny_ms++;

	if (hodiny_ms==500) ot_mer_imp=ot_imp*1.8;					//meranie otáèok motoru

	if (TCCR2B==0||POWER_OFF)//  operácie sa vykonajú len keï sa nevstrekuje benzín
	{	
		if (hodiny_ms>1000)
		{															//operácie každú s
			hodiny_ms=hodiny_ms-1000;
			hodiny_s++;
			ot_status=1;
			if (hodiny_s==60)
			{													//operácie každú m
				hodiny_s=0;
				hodiny_m++;

				if (hodiny_m==60)				
				{												//operácie každú h
					hodiny_m=0;
					hodiny_h++;
				#ifndef H12	
					if (hodiny_h==24) hodiny_h=0;
				#endif
				#ifdef H12	
					if (hodiny_h==13) hodiny_h=1;
				#endif
					//--------------------------------------------operácie každú h---------------

					//-------------------------------------------------------------------------------
				}
				//----------------------------------------------operácie každú m---------------
				if (POWER_OFF&&reset_j) 
				{
//					lcd_clr_dspl();
//					zobraz_hodiny(7,3,2);	
//					zobraz_nick(15);
					if(hodiny_on)
					{
						//---------------------Hodiny-----------------------------
						DDRB=DDR_B;
						PRR0=0b11011011;	//zapnutie SPI
						SPCR=80;
						SPSR = (1<<SPI2X);
						lcd_putnr(hodiny_h, 0, '0', 2, 4, 36, 4, WHITE, BLACK, 1);
						lcd_putchar(':',86,43,3,WHITE,BLACK,1);
						lcd_putnr(hodiny_m, 0, '0', 2, 100, 36, 4, WHITE, BLACK, 1);
					}
				}

				//-------------------------------------------------------------------------------
			}
			//------------------------------------------------operácie každú s---------------

			if (motor_on||rychlost_p>0) doba_jazdy++;
			if (!motor_on)
			{
				as_h=0;
				as_km=0;
				doba_vstreku=0;
			}

			motor_on=0;
			stav_test=stav;

			stav=0;
			if (TCNT1>OCR1A)
			{ 		//vynulovanie TCNT1 v prípade chyby
				TCNT1=0;
				km++;
			}		

		//-------------------------------------------------------------------------------
		}
	}
}



void nast_cpu(void)
{
//--------------------Timer0 - prerušenie 1ms---------
	TCCR0A=2;
	TCCR0B=3;
	SetBit(TIMSK0,OCIE0A);
	OCR0A=249;
//--------------------Timer1 - prerušenie 10m---------
	TCCR1A=0;
	TCCR1B=15;		
	SetBit(TIMSK1,OCIE1A);
	OCR1A=poc_imp_10m;		
	OCR1B=dlzka_merania;	
//--------------------Timer2 - 10us-----------------
	TCCR2A=2;		
//-------------------Nastavenie AD prevodniku---------
	ADMUX=AD_REF+NAPATIE;				
	ADCSRA=0xC6;
	ADCSRB=0x00;
//-------------------Zapnutie prerušení---------------
	SetBit(EIMSK,INT2);
	SetBit(EIFR,INTF2);
	EICRA=32;
	SetBit(SREG,7);
}


void set_ports(void)
{
	PORTA=PORT_A;
	DDRA=DDR_A;
	PORTB=PORT_B;
	DDRB=DDR_B;			//výstup piezo
	PORTC=PORT_C;		//pullupy na tlaèítka
	DDRC=DDR_C;
	PORTD=PORT_D;
	DDRD=DDR_D;
}

void nastav_ad(unsigned char pin)
{
	while ChckBit(ADCSRA,ADSC);
	ADMUX=AD_REF+pin;			
	SetBit(ADCSRA,ADSC);

}

int get_advalue(void)
{
	while ChckBit(ADCSRA,ADSC);
	return(ADC);
}



void reset_jazdy(void)
{
	if (reset_j&&motor_on&&POWER_OFF==0)
	{
		km_denne[4]=km;
		spotrebovane_palivo_denne[4]=spotrebovane_palivo;
		max_spd_denne[4]=0;
		doba_jazdy_denne[4]=doba_jazdy;
		reset_j=0;
	}
}

void kavicka(void)
{
	if (vypocet_doba_jazdy(4)>kavicka_s+kavicka_o&&reset_j==0)
	{
		kavicka_o=kavicka_o+600;
		vystraha(KAVA_S, 54, 45, 3, KAVA_X, KAVA_Y, 3, 15);
	}
//		vystraha(KAVA_S, 54, 45, 3, KAVA_X, KAVA_Y, 3, 15);

}


