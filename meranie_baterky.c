#include "meranie_baterky.h"
#include "variables.h"
#include "beep.h"
#include "definitions.h"
#include "main.h"
#include "menu.h"
#include "lcd_s65_ls020.h"
#include "vystraha.h"
#include "delay.h"


void meranie_baterky(void)
{
	nastav_ad(NAPATIE);			
	napatie=((get_advalue()*bat_odb)+BAT_ND);

	if (napatie<BAT_BEEP&&motor_on) 
	{
		if (battery_beep_s==0)
		{
			battery_beep_s=1;
			battery_beep_l_s=hodiny_s;
			battery_beep_t=BAT_BEEP_TIMER;
		}
		if (battery_beep_s==1&&battery_beep_l_s!=hodiny_s)
		{
			battery_beep_t--;
			battery_beep_l_s=hodiny_s;
			if (battery_beep_t==0)
			{
				battery_beep_s=2;
				vystraha(BATERKA_S, 70, 46, 3, IKONA_X, IKONA_Y, 3, 5);
			}
		}
	}
}
