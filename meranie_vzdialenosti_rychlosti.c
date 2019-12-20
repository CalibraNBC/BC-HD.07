#include <avr/interrupt.h>
#include "meranie_vzdialenosti_rychlosti.h"
#include "variables.h"



ISR(TIMER1_COMPA_vect)
{
	km++;
}


//------------------------------------------------Výpoèet aktuálnej rýchlosti-------------------------------
void vypocet_aktualnej_rychlosti(void)
{
	r_meranie++;
	if (r_meranie>=dlzka_merania)
	{
		r_end=TCNT1;
		r_meranie=0;
		r_end=r_end+((km-r_km)*poc_imp_10m);
		rychlost= r_end-r_start;
		r_start=TCNT1;
		if (r_start==0&&ChckBit(TIFR1,OCF1A))r_km=km+1;
		else r_km=km;
		rychlost_p=(rychlost+r_old1+r_old2)/3;
		r_old2=r_old1;		
		r_old1=rychlost;		
		if (rychlost_p<300)
		{
			if (rychlost_p>max_spd) max_spd=rychlost_p;
			if (rychlost_p>max_spd_denne[0]&&status_ss[0]==0) max_spd_denne[0]=rychlost_p;
			if (rychlost_p>max_spd_denne[1]&&status_ss[1]==0) max_spd_denne[1]=rychlost_p;
			if (rychlost_p>max_spd_denne[2]&&status_ss[2]==0) max_spd_denne[2]=rychlost_p;
			if (rychlost_p>max_spd_denne[3]) max_spd_denne[3]=rychlost_p;
			if (rychlost_p>max_spd_denne[4]) max_spd_denne[4]=rychlost_p;
		}
	}
}

