#include "meranie_podsvietenia.h"
#include "variables.h"
#include "definitions.h"
#include "main.h"
#include "menu.h"



void meranie_podsvietenia(void)
{
	char a=0;
	unsigned long	tmp;


	if (BACKLIGHT_CHCK)
	{
		BACKLIGHT_OFF;
		a=1;
	}

	MEASURE_BCK_ON;
	nastav_ad(PODSVIETENIE);
	sv_nap=get_advalue()*kbl;
	MEASURE_BCK_OFF;

	if (a) BACKLIGHT_ON;


	tmp=sv_nap;
	tmp=(tmp*1000)/napatie;
/*	
	if (tmp<sv_nap_val[0]) sv_hodnota=0;
	if (tmp<sv_nap_val[0]) sv_hodnota=1;
	if (tmp>sv_nap_val[1]) sv_hodnota=2;
	if (tmp>sv_nap_val[2]||tmp<sv_nap_val[0]/2) sv_hodnota=3;
*/
	
	if (sv_hodnota==2)
	{
		if (tmp<sv_nap_val[1]*SV_MIN) sv_hodnota=1;
		if (tmp>sv_nap_val[2]*SV_MAX||tmp<sv_nap_val[0]/2) sv_hodnota=3;
	}
	else if (sv_hodnota==1)
	{
		if (tmp>sv_nap_val[1]*SV_MAX) sv_hodnota=2;
		if (tmp>sv_nap_val[2]||tmp<sv_nap_val[0]/2) sv_hodnota=3;
	}
	else
	{
		if (tmp<sv_nap_val[2]*SV_MIN) sv_hodnota=2;
		if (tmp<sv_nap_val[1]) sv_hodnota=1;
	}
	if (tmp<sv_nap_val[1]/2) sv_hodnota=3;

}
