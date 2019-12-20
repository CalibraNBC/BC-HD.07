#include "bw_picture.h"

void ee_write(void);

void ee_write(void)
{
unsigned int a;
	for (a=0;a<2000;a++) 
	{
		_delay_ms(10);
		serial_eeprom_write_byte(a,pgm_read_byte(&bw_picture[a]));
	}
	lcd_putstring(PSTR("WRITE OK"),0,10,0,M_COL_TXT,M_COL_BCK,1);
	for (a=0;a<2000;a++)
	{
		if (serial_eeprom_read_byte(a)!=pgm_read_byte(&bw_picture[a])) 
		{
			lcd_putstring(PSTR("Check NOK"),0,30,0,M_COL_TXT,M_COL_BCK,1);
			lcd_putnr(a, 0, '0', 1, 0, 50, 0, M_COL_TXT, M_COL_BCK, 1);
			lcd_putnr(serial_eeprom_read_byte(a), 0, ' ', 3, 20, 50, 0, M_COL_TXT, M_COL_BCK, 1);
			lcd_putnr(pgm_read_byte(&bw_picture[a]), 0, ' ', 3, 70, 50, 0, M_COL_TXT, M_COL_BCK, 1);
			while(1);
		}
	}
	lcd_putstring(PSTR("Check OK"),0,30,0,M_COL_TXT,M_COL_BCK,1);
	
	while(1);	
}
