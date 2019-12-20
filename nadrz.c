#include "keys.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "nadrz.h"
#include <avr/pgmspace.h>
#include "definitions.h"
#include "mnu_bc.h"
#include "delay.h"
#include <avr/eeprom.h>
#include "int_ee.h"

typedef unsigned char BYTE;
BYTE *p_ee_zero6=(BYTE*) 0;


void nadrz(void)
{
	unsigned char a;

	if (TLACITKO_STOP)
	{
		if (!TLACITKO_START)
		{
			lcd_putstring(PSTR(" LCD ?"),32,70,1,M_COL_TXT,M_COL_BCK,1);
			if (tlacitka_long())
			{
				for(a=0;a<70;a++) eeprom_read_block(&dn[a],p_ee_zero6 + EE_DN2+(a)*2,2);
				for(a=0;a<70;a++) zapis_ee(dn[a],p_ee_zero6 + EE_DN+(a)*2,2);
//				for(a=0;a<70;a++)	dn[a]=dn[a]/kp;
				lcd_putstring(PSTR(" LCD OK"),32,70,1,M_COL_TXT,M_COL_BCK,1);
				delay_s(5);
			}
			lcd_clr_dspl(M_COL_BCK,1);
		}
	}

}
