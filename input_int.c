#include "input_int.h"
#include "lcd_s65_ls020.h"
#include "keys.h"
#include "definitions.h"
#include "variables.h"



int input_int(char x, char y, char size, char poc, unsigned int pred, unsigned int max)
{

	char a, temp_x;
	unsigned long cis1;
	unsigned long cis2;
	unsigned long cis3;
	unsigned long cis4;
	unsigned long cis5;

	while (tlacitka());

	if (max==0) max=0xFFFF;

	a=poc;
	cis1=(pred-((pred/10)*10));
	cis2=((pred/10)-((pred/100)*10));
	cis3=((pred/100)-((pred/1000)*10));
	cis4=((pred/1000)-((pred/10000)*10));
	cis5=(pred/10000);

	if (poc>5) poc=5;
	if (poc==0) poc=1;


	while(1)
	{
		temp_x=x;

		switch (poc)
			{
			case 5 :
				lcd_putchar(cis5+0x30,temp_x,y,size,(a==5)*M_COL_BCK+(a!=5)*M_COL_TXT,(a!=5)*M_COL_BCK+(a==5)*M_COL_TXT,2);
				temp_x=temp_x+CHAR_W*(size+1);
			case 4 :
				lcd_putchar(cis4+0x30,temp_x,y,size,(a==4)*M_COL_BCK+(a!=4)*M_COL_TXT,(a!=4)*M_COL_BCK+(a==4)*M_COL_TXT,2);
				temp_x=temp_x+CHAR_W*(size+1);
			case 3 :
				lcd_putchar(cis3+0x30,temp_x,y,size,(a==3)*M_COL_BCK+(a!=3)*M_COL_TXT,(a!=3)*M_COL_BCK+(a==3)*M_COL_TXT,2);
				temp_x=temp_x+CHAR_W*(size+1);
			case 2 :
				lcd_putchar(cis2+0x30,temp_x,y,size,(a==2)*M_COL_BCK+(a!=2)*M_COL_TXT,(a!=2)*M_COL_BCK+(a==2)*M_COL_TXT,2);
				temp_x=temp_x+CHAR_W*(size+1);
			case 1 :
				lcd_putchar(cis1+0x30,temp_x,y,size,(a==1)*M_COL_BCK+(a!=1)*M_COL_TXT,(a!=1)*M_COL_BCK+(a==1)*M_COL_TXT,2);
				temp_x=temp_x+CHAR_W*(size+1);
			}

		if (tlacitka()==2)
		{
			while (tlacitka());
			if (a==1) 
			{
				if ((cis1+cis2*10+cis3*100+cis4*1000+cis5*10000)>max) 
				{
					cis1=(max-((max/10)*10));
					cis2=((max/10)-((max/100)*10));
					cis3=((max/100)-((max/1000)*10));
					cis4=((max/1000)-((max/10000)*10));
					cis5=(max/10000);
					a=poc;
				}
				else 
				{
					temp_x=x;
					switch (poc)
						{
						case 5 :
							lcd_putchar(cis5+0x30,temp_x,y,size,M_COL_TXT,M_COL_BCK,2);
							temp_x=temp_x+CHAR_W*(size+1);
						case 4 :
							lcd_putchar(cis4+0x30,temp_x,y,size,M_COL_TXT,M_COL_BCK,2);
							temp_x=temp_x+CHAR_W*(size+1);
						case 3 :
							lcd_putchar(cis3+0x30,temp_x,y,size,M_COL_TXT,M_COL_BCK,2);
							temp_x=temp_x+CHAR_W*(size+1);
						case 2 :
							lcd_putchar(cis2+0x30,temp_x,y,size,M_COL_TXT,M_COL_BCK,2);
							temp_x=temp_x+CHAR_W*(size+1);
						case 1 :
							lcd_putchar(cis1+0x30,temp_x,y,size,M_COL_TXT,M_COL_BCK,2);
							temp_x=temp_x+CHAR_W*(size+1);
						}
					while (tlacitka());
					return (cis1+cis2*10+cis3*100+cis4*1000+cis5*10000);
				}
			}
			else a--;

		}

		if (tlacitka()==1)
		{
			while (tlacitka());
			switch (a)
				{
				case 5 :
					if (cis5==6) cis5=0;
					else cis5++;
					break;
				case 4 :
					if (cis4==9) cis4=0;
					else cis4++;
					break;
				case 3 :
					if (cis3==9) cis3=0;
					else cis3++;
					break;
				case 2 :
					if (cis2==9) cis2=0;
					else cis2++;
					break;
				case 1 :
					if (cis1==9) cis1=0;
					else cis1++;
					break;
				}			
		}
	}

}
