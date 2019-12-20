#include "main.h"
#include <math.h>
#include "meranie_teploty.h"
#include "variables.h"
#include "meranie_vzdialenosti_rychlosti.h"
#include "lcd_s65_ls020.h"
#include "delay.h"
#include "vystraha.h"
#include "mnu_bc.h"



void meranie_teploty(void)
{
	float tmp;
	float tmp1;
	long  tmp3;
	nastav_ad(TEPLOTA);

	if(motor_on==0||rychlost_p>20)
	{
		tmp3=1024;
		tmp1=(((kvt*tmp3)/(tmp3-get_advalue()))-kvt)/TEMP_SENZOR;

		tmp=log(tmp1/100);
		teplota=10/(0.003354+0.000257*tmp+0.00000262*square(tmp))-2731.5;
	}


	if (teplota<NAMRAZA&&sig_namrazy&&vypocet_doba_jazdy(4)>10&&reset_j==0)
	{
		vystraha(VLOCKA_S, 55, 46, 2, VLOCKA_X, VLOCKA_Y, 1, 5);
		sig_namrazy=0;
	}
}


void meranie_teploty_motoru(void)
{
	float tmp;
	float tmp1;
	long  tmp3;
	nastav_ad(IN_OUT_3);

	tmp3=1024;
	tmp1=get_advalue();
	if(tmp1)
	{
		teplota_motoru_cidlo=1;
		tmp1=tmp1*kv3;
		tmp=1;
		tmp=log(1/(1/(tmp1/(napatie-tmp1)*TEMP_MOTOR_R)-tmp/TEMP_MOTOR_RD));

		tmp3=(1/(TEMP_MOTOR_A+TEMP_MOTOR_B*tmp+TEMP_MOTOR_C*(tmp*tmp*tmp)));
		if(tmp3>273&&tmp3<473) teplota_motoru= tmp3-273;
		else teplota_motoru=0;
	}
	else 
	{
		teplota_motoru_cidlo=0;
		teplota_motoru=0;
	}

/*
	teplota_motoru++;
	if(teplota_motoru>152)teplota_motoru=0;
*/	
	if(teplota_motoru<TEPLOTA_SIG)sig_teploty_motoru=1;
	if(sig_teploty_motoru&&teplota_motoru_cidlo&&teplota_motoru>TEPLOTA_MOTORU_MAX)
	{
		sig_teploty_motoru=0;
		vystraha(T_OLEJ_S, 52, 65, 2, T_OLEJ_X, T_OLEJ_Y, 1, 10);
	}
}
