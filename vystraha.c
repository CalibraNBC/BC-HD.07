#include "lcd_s65_ls020.h"
#include "delay.h"
#include "vystraha.h"
#include "beep.h"
#include "definitions.h"
#include "variables.h"




void vystraha(unsigned int picture, unsigned char px, unsigned char py, unsigned char psize, unsigned int pareax, unsigned int pareay, unsigned char poc_opakovani, unsigned char pauza)
{
	float f;
	unsigned char a, x, sirka;
	unsigned int b;

	x=79;
	sirka=20;
	f=0;	

	if(lcd_type==1)	lcd_off(1);
	lcd_clr_dspl(BLACK, 1);
	lcd_put_bw_picture(picture,px,py,psize,pareax,pareay,WHITE,BLACK,1);

	if(lcd_type==1)
	{
		for (a=0;a<135;a++)
		{
			lcd_area(x-f, a, x-f+sirka, a, 1);
			for(b=1;b<sirka;b++) lcd_sendd(0xE0, 1); 
			lcd_area(x+f, a, x+f+sirka, a, 1);
			for(b=1;b<sirka;b++) lcd_sendd(0xE0, 1); 
			f=f+0.7;
		}
	
		lcd_area(0, 115, 176, 134, 1);
		for(b=1;b<3344;b++) lcd_sendd(0xE0, 1);
	}

	if(lcd_type==2)
	{
		for (a=0;a<135;a++)
		{
			lcd_area(x-f, a, x-f+sirka, a, 1);
			lcd_sendc(0x5C,0x00, 1);
			for(b=1;b<sirka;b++) lcd_sendd(RED, 1); 
			lcd_area(x+f, a, x+f+sirka, a, 1);
			lcd_sendc(0x5C,0x00, 1);
			for(b=1;b<sirka;b++) lcd_sendd(RED, 1); 
			f=f+0.7;
		}
	
		lcd_area(0, 115, 176, 134, 1);
		lcd_sendc(0x5C,0x00, 1);
		for(b=1;b<3344;b++) lcd_sendd(RED, 1);

	b=0;
	while(b<poc_opakovani)
	{
//		lcd_off(1);
		for (a=0;a<5;a++) delay100ms();		
//		lcd_on(1);
		beep(0, 50, 0);
		b++;
	}


	}



	delay_s(pauza);
	lcd_clr_dspl(M_COL_BCK, 1);
}
