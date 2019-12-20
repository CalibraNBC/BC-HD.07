#include "meranie_spotreby.h"
#include <avr/interrupt.h>
#include "variables.h"
#include "meranie_vzdialenosti_rychlosti.h"


ISR(INT2_vect)
{

	if (ChckBit(PINB,3))
	{
		if (ChckBit(EICRA,ISC20))
		{													//Koniec vstreku
			TCCR2B=0;
			ClrBit(EICRA,ISC20);
			doba_vstreku=dlzka_vstreku-vstrek_start;
			if (dlzka_vstreku>poc_ms_ml) 
			{
				dlzka_vstreku=dlzka_vstreku-poc_ms_ml; 
				spotrebovane_palivo++;
			}
			//------------------------------------------------Výpoèet aktuálnej spotreby-------------------------------
			#ifdef MPH
				if (rychlost<7)
			#endif
			#ifndef MPH
				if (rychlost<10)
			#endif
			{
			//-----------------------------litre za hodinu---------------------------------
				if (as_timer>AS_TIMER_H)
				{
					as_timer=0;
					as_doba_merania=(((hodiny_s-as_s_old)*1000)+hodiny_ms)-as_ms_old;	
					as_ms_old=hodiny_ms;
					as_s_old=hodiny_s;
					as_mnozstvo_paliva_h=(((dlzka_vstreku+((spotrebovane_palivo-as_spotrebovane_palivo_h_old)*poc_ms_ml))-as_vstrek_h_old)*1000)/poc_ms_ml;
					as_vstrek_h_old=dlzka_vstreku;
					as_spotrebovane_palivo_h_old=spotrebovane_palivo;
					as_h=(as_mnozstvo_paliva_h*(36000/as_doba_merania))/1000;
				}
			}
			if (rychlost>0)
			{
			//-----------------------------litre na 100km----------------------------------
				if (as_timer>AS_TIMER_KM)
				{
					as_timer=0;	
					as_mnozstvo_paliva_km=(((dlzka_vstreku+((spotrebovane_palivo-as_spotrebovane_palivo_km_old)*poc_ms_ml))-as_vstrek_km_old)*10000)/poc_ms_ml;
					as_vstrek_km_old=dlzka_vstreku;
					as_spotrebovane_palivo_km_old=spotrebovane_palivo;		
					as_vzdialenost=((TCNT1+((km-as_km_old)*poc_imp_10m))-as_tcnt_old)*poc_des_mm_1_imp;
					as_tcnt_old=TCNT1;
					as_km_old=km;
					as_km=as_mnozstvo_paliva_km/(as_vzdialenost/1000);
				}
			}
			//--------------------------------------------------------------------------------------------------------
		}
		else
		{													//Zaciatok vstreku
			TCCR2B=1;		
			SetBit(TIMSK2,OCIE2A);
//			OCR2A=79;								//Nastavenie prerusenia na 10uS
			OCR2A=159;								//Nastavenie prerusenia na 10uS
			SetBit(TIFR2,OCF2A);
			SetBit(EICRA,ISC20);
			motor_on=1;
			vstrek_start=dlzka_vstreku;
			dlzka_vstreku++;
			TCNT2=0;

			//-----------------------------Meranie otáèok motoru-------------------------
			ot_imp++;
			if (ot_mer_imp==ot_imp&&ot_status==2)
			{
				ot_cas_old=ot_cas+hodiny_ms;
				ot_imp_old=ot_mer_imp;
				ot_status=0;
			}

			if (ot_status==1)	
			{
				ot_cas=-hodiny_ms;
				ot_imp=0;
				ot_mer_imp=0;
				ot_status=2;
			}
			//-----------------------------------------------------------------------------

		}
	}
}


ISR(TIMER2_COMPA_vect)	//prerusenie pri vstreku kazdých 10uS
{
	dlzka_vstreku++;	
}

