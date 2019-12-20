#ifndef _menu_
#define _menu_
#include "settings.h"

#define MNU_BC_NR									1
#define MNU_PRETAZENIE_NR					2			
#define MNU_ZRYCHLENIE_NR					4	
#define MNU_MOTOR_NR							3
#define MNU_400M_NR								5
#define MNU_STOPKY_NR							6


#define MNU_DEVELOP_NR						7
#define MNU_DEVELOP2_NR						8
#define MNU_DEVELOP3_NR						9
#define MNU_DEVELOP4_NR						10
#define MNU_DEVELOP5_NR						11
#define MNU_DEVELOP6_NR						12





#define MNU_NASTAVENIA_NR					15	

#ifdef DEVELOP
	#define MNU_MAX										9
#endif

void menu(void);
void zmena_menu(unsigned char nove_menu);


unsigned char menu_nr[3];


#endif
