#include "main.h"
#include "meranie_nadrze.h"
#include "variables.h"
#include "accelerometer.h"
#include "meranie_vzdialenosti_rychlosti.h"
#include "mnu_bc.h"
//#include "beep.h"
#include "vystraha.h"


void zmeraj_nadrz(void)
{
	unsigned char min,max,a;
	
	if (pal_korekcia!=6)
	{
		if (ChckBit(hodiny_ms,F_MERANIA)!=posledna_kontrola)
		{
			nastav_ad(PALIVO);
			posledna_kontrola=ChckBit(hodiny_ms,F_MERANIA);
			pal_tmp_poc++;

			if(pal_tmp_poc>=POC_MERANI_PALIVA) pal_tmp_poc=0;

			pal_tmp[pal_tmp_poc]=hodnota_paliva(get_advalue());
	
			min=255;
			max=0;
			for (a=0;a<POC_MERANI_PALIVA;a++)
			{
				if (pal_tmp[a]<min) min=pal_tmp[a];
				if (pal_tmp[a]>max) max=pal_tmp[a];
			}
			pal_act=(min+max)/2;
		}
	}
}


void zapis_nadrz(void)
{
	long pal_vypoc;
	char tmpx, tmpy;
	unsigned char min,max, a;

	if(pal_korekcia!=6)
	{
		pal_vypoc=n_posledna_hodnota-((spotrebovane_palivo-n_spotrebovane_palivo)/1000);

		if(pal_vypoc<SIG_NADRZ&&sig_nadrze&&vypocet_doba_jazdy(4)>CAS_SIG_PO_STARTE&&reset_j==0)
		{
			vystraha(NADRZ_S, 70, 46, 3, IKONA_X, IKONA_Y, 1, 5);
			sig_nadrze=0;
		}


		if(rychlost_p)
		{
			pal_stav=0;
			return;
		}
		if(!motor_on)
		{
			pal_stav=0;
			return;
		}
		
		if(pal_start&&vypocet_doba_jazdy(4)>N_CAK_START&&reset_j==0)
		{
			pal_start=0;
			if(pal_act+pal_korekcia>pal_vypoc)
			{
				if(pal_act+pal_korekcia>=pal_vypoc+N_MAX_ROZD_START)
				{
					//beep(2, 20, 10);
					n_posledna_hodnota=pal_act+pal_korekcia;
					n_spotrebovane_palivo=spotrebovane_palivo;
				}
			}
			else if(pal_act+pal_korekcia<=pal_vypoc-N_MIN_ROZD_START&&pal_vypoc>N_MIN_ROZD_START)
			{
				//beep(3, 20, 10);
				n_posledna_hodnota=pal_act+pal_korekcia;
				n_spotrebovane_palivo=spotrebovane_palivo;
			}
		}

		tmpx=accelerometer_x;
		tmpy=accelerometer_y;
		if(tmpx<0) tmpx=256-tmpx;
		if(tmpy<0) tmpy=256-tmpy;
		if(tmpy>N_PRETAZENIE_Y) return;
		if(tmpx>N_PRETAZENIE_X) return;


/*
		if(!pal_stav)
		{
			pal_stav=1;
			pal_doba=0;
			pal_cak=N_CAK_STOP;
			pal_s=hodiny_s;
		}
		if (hodiny_s!=pal_s)
		{
			pal_doba++;
			pal_s=hodiny_s;
		}
		if (pal_cak>pal_doba) return;
*/



		min=255;
		max=0;
		for (a=0;a<POC_MERANI_PALIVA;a++)
		{
			if (pal_tmp[a]<min) min=pal_tmp[a];
			if (pal_tmp[a]>max) max=pal_tmp[a];
		}

		if(min+N_MIN_ODCHYLKA<max)return;

		if(pal_act+pal_korekcia>pal_vypoc)
		{
			if(pal_act+pal_korekcia>=pal_vypoc+N_MAX_ROZD_STOP)
			{
				//beep(4, 20, 10);
				n_posledna_hodnota=pal_act+pal_korekcia;
				n_spotrebovane_palivo=spotrebovane_palivo;
			}
		}
		else if(pal_act+pal_korekcia<=pal_vypoc-N_MIN_ROZD_STOP&&pal_vypoc>N_MIN_ROZD_STOP)
		{
			//beep(5, 20, 10);
			n_posledna_hodnota=pal_act+pal_korekcia;
			n_spotrebovane_palivo=spotrebovane_palivo;
		}


	}
}


char hodnota_paliva(unsigned int adc)
{
	unsigned char a;
	for (a=0;a<70;a++) if (adc*kp>=dn[a]) break;
	return(a);
}



void meranie_spotreby_za_poslednu_vzdialenost(void)
{
	unsigned char a;
#ifdef PV_RESET_ON_START

	if (vypocet_km(3)*10< PV_M_NEMERANE)
	{
		for (a=0;a<PV_POC_MERANI;a++)
		{
			km_pv[a]=km;
			spotrebovane_palivo_pv[a]=spotrebovane_palivo;
		}
		priemerna_spotreba_pv=vypocet_priemerna_spotreba(5);
	}
#endif

	if ((km-km_pv[0])*10>PV_M/PV_POC_MERANI)
	{
		for (a=PV_POC_MERANI-1;a>0;a--)
		{
			km_pv[a]=km_pv[a-1];
			spotrebovane_palivo_pv[a]=spotrebovane_palivo_pv[a-1];
		}
		km_pv[0]=km;
		spotrebovane_palivo_pv[0]=spotrebovane_palivo;
	}
	
	if ((km-km_pv[PV_POC_MERANI-1])*10>PV_VYPOCET) priemerna_spotreba_pv=(((spotrebovane_palivo-spotrebovane_palivo_pv[PV_POC_MERANI-1])*100)/(km-km_pv[PV_POC_MERANI-1]));

}






