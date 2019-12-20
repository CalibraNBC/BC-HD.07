#include "mnu_pretazenie.h"
#include "menu.h"
#include "main.h"
#include "lcd_s65_ls020.h"
#include "variables.h"
#include "definitions.h"
#include "keys.h"
#include <avr/pgmspace.h>
#include "accelerometer.h"
#include "delay.h"
#include "language.h"

#define 	STVOREC_X 	76
#define 	STVOREC_Y		55
#define 	DLZKA				24




char mnu_pretazenie(void)
{
	char tmpx,tmpy;

	zmeraj_pretazenie();

	graf(accelerometer_x,accelerometer_y);
	
	lcd_putstring(PSTR("X:"),0,0,1,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("Y:"),113,0,1,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("X:"),0,106,1,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR("Y:"),113,106,1,COL_TXT_LCD2,M_COL_BCK,2);

#ifndef S65_LANG_RUS
	lcd_putstring(PSTR(TXT_MAX),0,94,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR(TXT_MAX),152,94,0,COL_TXT_LCD2,M_COL_BCK,2);
#endif
#ifdef S65_LANG_RUS
	lcd_putstring(PSTR(TXT_MAX),0,94,0,COL_TXT_LCD2,M_COL_BCK,2);
	lcd_putstring(PSTR(TXT_MAX),144,94,0,COL_TXT_LCD2,M_COL_BCK,2);
#endif


	tmpx=accelerometer_x;
	tmpy=accelerometer_y;


	if (tmpx<0) tmpx=256-tmpx;
	if (tmpy<0) tmpy=256-tmpy;
	if (tmpx>max_pretazenie_x) max_pretazenie_x=tmpx;
	if (tmpy>max_pretazenie_y) max_pretazenie_y=tmpy;


	lcd_putnr(((tmpx*2)+5)/10, 1, ' ', 2, 24, 0, 1, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(((tmpy*2)+5)/10, 1, ' ', 2, 137, 0, 1, M_COL_TXT, M_COL_BCK, 2);

	lcd_putnr(((max_pretazenie_x*2)+5)/10, 1, ' ', 2, 24, 106, 1, M_COL_TXT, M_COL_BCK, 2);
	lcd_putnr(((max_pretazenie_y*2)+5)/10, 1, ' ', 2, 137, 106, 1, M_COL_TXT, M_COL_BCK, 2);


	if (tlacitka()==1)
	{
		max_pretazenie_y=0;
		max_pretazenie_x=0;
	}	

	if (tlacitka()==2) return(1);

	return(0);
}


void graf(int x, int y)
{
	unsigned int tmp_color_x, tmp_color_y;


	if (y>STVOREC_Y) y=STVOREC_Y;
	if (y<-STVOREC_Y) y=-STVOREC_Y;
	if (x>STVOREC_X) x=STVOREC_X;
	if (x<-STVOREC_X) x=-STVOREC_X;

	tmp_color_x=M_COL_TXT;
	tmp_color_y=M_COL_TXT;

	if (M_COL_BCK!=RED && M_COL_BCK!=YELLOW)
	{
		if (x>50||x<-50) tmp_color_x=RED;
		else if (x>40||x<-40) tmp_color_x=YELLOW;
		if (y>50||y<-50) tmp_color_y=RED;
		else if (y>40||y<-40) tmp_color_y=YELLOW;
	}


	obdlznik(STVOREC_X, STVOREC_Y, 5, DLZKA, BLUE);
	obdlznik(STVOREC_X+21, STVOREC_Y, 3, DLZKA, BLUE);

	lcd_putstring(PSTR("G"),STVOREC_X+5,STVOREC_Y,1,WHITE,BLUE,2);


	if(y>0)
	{
		obdlznik(STVOREC_X, 0, DLZKA, STVOREC_Y, M_COL_BCK);
		obdlznik(STVOREC_X, STVOREC_Y+DLZKA, DLZKA, y, tmp_color_y);
		obdlznik(STVOREC_X, STVOREC_Y+DLZKA+y, DLZKA, STVOREC_Y-y, M_COL_BCK);
	}
	else
	{
		obdlznik(STVOREC_X, STVOREC_Y+DLZKA, DLZKA, STVOREC_Y, M_COL_BCK);
		obdlznik(STVOREC_X, STVOREC_Y+y, DLZKA, 256-y, tmp_color_y);
		obdlznik(STVOREC_X, 0, DLZKA, STVOREC_Y+y, M_COL_BCK);
	}

	if(x>0)
	{
		obdlznik(0, STVOREC_Y, STVOREC_X, DLZKA, M_COL_BCK);
		obdlznik(STVOREC_X+DLZKA, STVOREC_Y, x, DLZKA, tmp_color_x);
		obdlznik(STVOREC_X+DLZKA+x, STVOREC_Y, STVOREC_X-x, DLZKA, M_COL_BCK);
	}
	else
	{
		obdlznik(STVOREC_X+DLZKA, STVOREC_Y, STVOREC_X, DLZKA, M_COL_BCK);
		obdlznik(STVOREC_X+x, STVOREC_Y, 256-x, DLZKA, tmp_color_x);
		obdlznik(0, STVOREC_Y, STVOREC_X+x, DLZKA, M_COL_BCK);
	}
}



