#include "keys.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "reset.h"
#include <avr/pgmspace.h>
#include "definitions.h"
#include "mnu_bc.h"
#include "delay.h"
#include <avr/eeprom.h>
#include "int_ee.h"

typedef unsigned char BYTE;
BYTE *p_ee_zero7=(BYTE*) 0;

void reset(void)
{
	unsigned char a;

	if (TLACITKO_START&&TLACITKO_STOP)
	{
		lcd_putstring(PSTR("RESET ?"),32,70,1,M_COL_TXT,M_COL_BCK,1);
		if (tlacitka_long())
		{
			km=0;
			spotrebovane_palivo=0;
			TCNT1=0;
			max_spd=0;
			doba_jazdy=0;

			for(a=0;a<70;a++) eeprom_read_block(&dn[a],p_ee_zero7 + EE_DN1+(a)*2,2);
			for(a=0;a<70;a++) zapis_ee(dn[a],p_ee_zero7 + EE_DN+(a)*2,2);

			for (a=0;a<=4;a++) reset_denne(a);
			lcd_putstring(PSTR("RESET OK"),32,70,1,M_COL_TXT,M_COL_BCK,1);
			delay_s(5);
		}
		lcd_clr_dspl(M_COL_BCK,1);
	}

}
