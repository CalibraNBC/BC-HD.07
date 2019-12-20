#include "verzia.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "definitions.h"
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "language.h"
#include "settings.h"



 
void verzia(void)
{
unsigned int sn;
	typedef unsigned char BYTE;
	BYTE *p_ee_zero1=(BYTE*) 0;

	lcd_putstring(PSTR("NBC"),64,8,1,M_COL_TXT,M_COL_BCK,1);
	lcd_putstring(PSTR(TXT_WWW),0,32,0,M_COL_TXT,M_COL_BCK,1);
	lcd_putstring(PSTR(TXT_WWW2),0,44,0,M_COL_TXT,M_COL_BCK,1);

/*
	lcd_putstring(PSTR("kadel"),24,30,0,M_COL_TXT,M_COL_BCK,1);
	lcd_putchar(129,64,30,0,M_COL_TXT,M_COL_BCK,1);
	lcd_putstring(PSTR("calibra.cz"),74,30,0,M_COL_TXT,M_COL_BCK,1);
*/
	lcd_putstring(PSTR("HW"),28,69,0,M_COL_TXT,M_COL_BCK,1);

	lcd_putnr(eeprom_read_byte(p_ee_zero1 + EE_VHWMA), 0, '0', 2, 16, 82, 0, M_COL_TXT, M_COL_BCK, 1);
	lcd_putstring(PSTR("."),32,82,0,M_COL_TXT,M_COL_BCK,1);
	lcd_putnr(eeprom_read_byte(p_ee_zero1 + EE_VHWMI), 0, '0', 2, 40, 82, 0, M_COL_TXT, M_COL_BCK, 1);
	if(lcd_type==2)lcd_putstring(PSTR("2"),56,82,0,M_COL_TXT,M_COL_BCK,1);



	lcd_putstring(PSTR("FW"),132,69,0,M_COL_TXT,M_COL_BCK,1);
	lcd_putstring(PSTR(TXT_VERZIA),120,82,0,M_COL_TXT,M_COL_BCK,1);

	lcd_putstring(PSTR("SN"),80,69,0,M_COL_TXT,M_COL_BCK,1);
	eeprom_read_block(&sn,p_ee_zero1 + EE_SN,2);
	lcd_putnr(sn, 0, '0', 4, 70, 82, 0, M_COL_TXT, M_COL_BCK, 1);

}


