#include "pomocne.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "definitions.h"
#include "mnu_bc.h"

	
#ifdef DEVELOP

void zobraz_nadrz_stav(void)
{
	long tmp;
	unsigned long tmp1;

	lcd_putnr(n_hodnota, 0, ' ', 3, 0, 120, 0, M_COL_TXT, M_COL_BCK, 1);
	lcd_putnr(n_adc*kp, 2, ' ', 3, 32, 120, 0, M_COL_TXT, M_COL_BCK, 1);
	tmp=(n_posledna_hodnota*1000)-((spotrebovane_palivo-n_spotrebovane_palivo));
	if (tmp<0) tmp=0;
	lcd_putnr(tmp/10, 2, ' ', 4, 64, 120, 0, M_COL_TXT, M_COL_BCK, 1);

	tmp1=((vypocet_priemerna_spotreba(5)*POMER_DOJAZD_C)+(priemerna_spotreba_pv*POMER_DOJAZD_PV));

	lcd_putnr(priemerna_spotreba_pv, 1, ' ', 3, 108, 120, 0, M_COL_TXT, M_COL_BCK, 1);
	lcd_putnr(tmp1/10, 2, ' ', 4, 140, 120, 0, M_COL_TXT, M_COL_BCK, 1);

}

#endif
