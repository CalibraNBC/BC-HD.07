#include "input_char.h"
#include "lcd_s65_ls020.h"
#include "keys.h"
#include "definitions.h"
#include "variables.h"
#include "language.h"



unsigned char input_char(unsigned char x, unsigned char y, char size, unsigned char pred)
{
	while (tlacitka());
	while(1)
	{
		if (tlacitka()==1)
		{
			while (tlacitka());

			#ifndef AZBUKA
				if(pred<32) pred=126;
				pred=pred+1;
				if (pred>126) pred=32;
			#endif

			#ifdef AZBUKA
				if(pred<32) pred=31;
				pred=pred+1;
				if (pred>57&&pred<161) pred=161;
				if (pred>227) pred=32;
			#endif

		}
		lcd_putchar(pred,x,y,size,M_COL_BCK,M_COL_TXT,2);
		if (tlacitka()==2)
		{
			while (tlacitka());
			lcd_putchar(pred,x,y,size,M_COL_TXT,M_COL_BCK,2);
			return (pred);
		}
	}
}
