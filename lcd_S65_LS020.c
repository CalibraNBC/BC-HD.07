#include <util/delay.h>
#include <avr/pgmspace.h>
#include "lcd_s65_ls020.h"
#include <avr/io.h>
#include "bit_operations.h"
#include "main.h"
#include "font_8_12.h"
#include "settings.h"
#include "delay.h"
#include "bw_picture.h"
#include "language.h"
//#include "eeprom_24Cxx.h"
#include "variables.h"

extern const char init1[] PROGMEM;
extern const char init2[] PROGMEM;
extern const char init1_l2f50[] PROGMEM;
extern const char init2_l2f50[] PROGMEM;
extern const char init3_l2f50[] PROGMEM;
extern const char init4_l2f50[] PROGMEM;



void lcd_putnr(unsigned long c, char ciarka, char znak, unsigned char poc_miest, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd)
{
	if (c>=100000 || ciarka ==5) goto vypis6;
	else
		if (c>=10000 || ciarka ==4) 
		{
			if (poc_miest==6) 
			{
				lcd_putchar(znak, x, y, size, textcolor, backcolor, lcd);
				x=x+CHAR_W*(size+1);
			}
			goto vypis5;
		}
		else
			if (c>=1000 || ciarka ==3) 
			{
				x=lcd_putchars(poc_miest-4, znak, x, y, size, textcolor, backcolor, lcd);
				goto vypis4;
			}
			else
				if (c>=100 || ciarka ==2) 
				{
					x=lcd_putchars(poc_miest-3, znak, x, y, size, textcolor, backcolor, lcd);
					goto vypis3;
				}
				else 
					if (c>=10 || ciarka ==1) 
					{
						x=lcd_putchars(poc_miest-2, znak, x, y, size, textcolor, backcolor, lcd);
						goto vypis2;
					}
					else
					{
						x=lcd_putchars(poc_miest-1, znak, x, y, size, textcolor, backcolor, lcd);
						goto vypis1;
					}

vypis6:
		lcd_putchar((c/100000)+0x30, x, y, size, textcolor, backcolor, lcd);
		x=x+CHAR_W*(size+1);
		if (ciarka ==5) 
		{
			lcd_putchar(',', x, y, size, textcolor, backcolor, lcd);
			x=x+4*(size+1);
		}
vypis5:
		lcd_putchar(((((c/10000)*10000)-((c/100000)*100000))/10000)+0x30, x, y, size, textcolor, backcolor, lcd);
		x=x+CHAR_W*(size+1);
		if (ciarka ==4)
		{
			lcd_putchar(',', x, y, size, textcolor, backcolor, lcd);
			x=x+4*(size+1);
		}
vypis4:
		lcd_putchar(((((c/1000)*1000)-((c/10000)*10000))/1000)+0x30, x, y, size, textcolor, backcolor, lcd);
		x=x+CHAR_W*(size+1);
		if (ciarka ==3)
		{
			lcd_putchar(',', x, y, size, textcolor, backcolor, lcd);
			x=x+4*(size+1);
		}
vypis3:
		lcd_putchar(((((c/100)*100)-((c/1000)*1000))/100)+0x30, x, y, size, textcolor, backcolor, lcd);
		x=x+CHAR_W*(size+1);
		if (ciarka ==2)
		{
			lcd_putchar(',', x, y, size, textcolor, backcolor, lcd);
			x=x+4*(size+1);
		}
vypis2:
		lcd_putchar(((((c/10)*10)-((c/100)*100))/10)+0x30, x, y, size, textcolor, backcolor, lcd);
		x=x+CHAR_W*(size+1);
		if (ciarka ==1)
		{
			lcd_putchar(',', x, y, size, textcolor, backcolor, lcd);
			x=x+4*(size+1);
		}
vypis1:
		lcd_putchar((c - ((c/10)*10))+0x30, x, y, size, textcolor, backcolor, lcd);

}


unsigned char lcd_putchars(char poc, char znak, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd)
{
	char a;
	for (a=0;a<poc;a++) 
	{
		lcd_putchar(znak, x, y, size, textcolor, backcolor, lcd);
		x=x+CHAR_W*(size+1);
	}
	return(x);
}


void lcd_cursor(unsigned int x, unsigned int y, unsigned char lcd)
{
  lcd_sendc(0xEF, 0x90, lcd);
#if defined(LCD_ROTATE)
# if defined(LCD_MIRROR)
  lcd_sendc(0x06, (LCD_WIDTH-1)-x, lcd);  //set x cursor pos
  lcd_sendc(0x07, (LCD_HEIGHT-1)-y, lcd); //set y cursor pos
# else
  lcd_sendc(0x06, x, lcd);                //set x cursor pos
  lcd_sendc(0x07, y, lcd);                //set y cursor pos
# endif
#else
# if defined(LCD_MIRROR)
  lcd_sendc(0x06, (LCD_HEIGHT-1)-y, lcd); //set y cursor pos
  lcd_sendc(0x07, x, lcd);                //set x cursor pos
# else
  lcd_sendc(0x06, y, lcd);                //set y cursor pos
  lcd_sendc(0x07, (LCD_WIDTH-1)-x, lcd);  //set x cursor pos
# endif
#endif

  return;
}


void lcd_area(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned char lcd)
{
  //set area

	if(lcd_type==1)
	{

	  lcd_sendc(0xEF, 0x90, lcd);
	#if defined(LCD_ROTATE)
	# if defined(LCD_MIRROR)
	  lcd_sendc(0x08, (LCD_WIDTH-1)-x0, lcd);  //set x0
	  lcd_sendc(0x09, (LCD_WIDTH-1)-x1, lcd);  //set x1
	  lcd_sendc(0x0A, (LCD_HEIGHT-1)-y0, lcd); //set y0
	  lcd_sendc(0x0B, (LCD_HEIGHT-1)-y1, lcd); //set y1
	# else
	  lcd_sendc(0x08, x0, lcd);                //set x0
	  lcd_sendc(0x09, x1, lcd);                //set x1
	  lcd_sendc(0x0A, y0, lcd);                //set y0
	  lcd_sendc(0x0B, y1, lcd);                //set y1
	# endif
	#else
	# if defined(LCD_MIRROR)
	  lcd_sendc(0x08, (LCD_HEIGHT-1)-y0, lcd); //set y0
	  lcd_sendc(0x09, (LCD_HEIGHT-1)-y1, lcd); //set y1
	  lcd_sendc(0x0A, x0, lcd);                //set x0
	  lcd_sendc(0x0B, x1, lcd);                //set x1
	# else
	  lcd_sendc(0x08, y0, lcd);                //set y0
	  lcd_sendc(0x09, y1, lcd);                //set y1
	  lcd_sendc(0x0A, (LCD_WIDTH-1)-x0, lcd);  //set x0
	  lcd_sendc(0x0B, (LCD_WIDTH-1)-x1, lcd);  //set x1
	# endif
	#endif

  	//set cursor
  	lcd_cursor(x0, y0, lcd);
	}

	else if(lcd_type==2)
	{
	  lcd_sendc(0x15, 0x00, lcd);               //column address set 
	  lcd_sendd0(0x08+y0, lcd);                //start column
	  lcd_sendd0(0x01, lcd);                   //start column
	  lcd_sendd0(0x08+y1, lcd);                //end column
	  lcd_sendd0(0x01, lcd);                   //end column

	  lcd_sendc(0x75,0x00, lcd);                    //page address set 
	  lcd_sendd0(x0, lcd);                     //start page, начало по оси х
	  lcd_sendd0(x1, lcd);                     //end page, конец по оси х
	}



}


void lcd_putstring(char *addre, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd)
{
	char c;

	while ((c = pgm_read_byte(addre++)))
	{
		lcd_putchar(c, x, y, size, textcolor, backcolor, lcd);
		x=x+CHAR_W*(size+1);
		if (c==44)x=x-4*(size+1);
		if (c==58)x=x-5*(size+1);
	}
}


void lcd_putchar(unsigned char c, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd)
{
	unsigned char h,ch,p,mask,a,b,temp_char_w, i;
	unsigned char cha[CHAR_H];

 	temp_char_w=CHAR_W;
	if (c==44)temp_char_w=CHAR_W-4;
	if (c==58)temp_char_w=CHAR_W-5;

	if(lcd_type==1)
	{
		lcd_area(x, y, x+(temp_char_w*(size+1))-1, y+(CHAR_H*(size+1))-1, lcd);

	  for (h=0; h<CHAR_H; h++)
	  {
			ch=pgm_read_byte(&font_8_12[((c-0x20)*CHAR_H)+h]);

			for(a=0;a<size+1;a++)
			{
		   	mask=0x80;
		    for (p=0; p<temp_char_w; p++)
		    {
			  	if (ch&mask) for(b=0;b<size+1;b++) lcd_sendd(textcolor, lcd);                
		 	  	else for(b=0;b<size+1;b++) lcd_sendd(backcolor, lcd);
		      mask=mask/2;
		    }
			}
		}
	}
	else if(lcd_type==2)
	{
		lcd_area(x, y, x+(temp_char_w*(size+1))-1, y+(CHAR_H*(size+1))-1, lcd);

		lcd_sendc(0x5C,0x00, lcd);
	
		for(a=0;a<CHAR_H;a++) cha[a]=pgm_read_byte(&font_8_12[((c-0x20)*CHAR_H)+a]);

		mask=0x80;
		for(h=0; h<temp_char_w;h++)
		{
			for(i=0;i<size+1;i++)
			{
				for(p=0; p<CHAR_H;p++)
				{
					if (cha[p]&mask) for(b=0;b<size+1;b++) lcd_sendd(textcolor, lcd);                
				 	else for(b=0;b<size+1;b++) lcd_sendd(backcolor, lcd);		
		//		for(tmp=50; tmp!=0;tmp--) _delay_ms(10);
				}
			}
	    mask=mask/2;
		}
	}

}



void lcd_put_bw_picture(unsigned int c, unsigned char x, unsigned char y, unsigned char size, unsigned char area_x, unsigned char area_y,unsigned int color, unsigned int bckcolor, unsigned char lcd)
{
	unsigned int a,mask;
	unsigned char ch,b,d; 
	
	
	mask=1;

	if(lcd_type==1)
	{
		lcd_area(x, y, x+area_x*size-1, y+area_y*size-1, lcd);
		for (a=0;a<area_y*size;a++)
		{
			for (d=1;d<=area_x;d++)
			{
				if (mask==1)
				{
		   		mask=0x100;
					ch=pgm_read_byte(&bw_picture[(((a/size)*area_x)/8)+c+(d/8)]);
				}
	    	mask=mask/2;
				if (ch&mask) for(b=0;b<size;b++) lcd_sendd(color, lcd);                
	 	  	else for(b=0;b<size;b++) lcd_sendd(bckcolor, lcd);
			}
		}
	}
	else if(lcd_type==2)
	{
		for (a=0;a<area_y*size;a++)
		{
			for (d=1;d<=area_x;d++)
			{
				if (mask==1)
				{
					lcd_area(x+d*size, y+a, x+d*size+8*size, y+a, lcd);
					lcd_sendc(0x5C,0x00, lcd);
		   		mask=0x100;
					ch=pgm_read_byte(&bw_picture[(((a/size)*area_x)/8)+c+(d/8)]);
				}
	    	mask=mask/2;

				if (ch&mask) for(b=0;b<size;b++) lcd_sendd(color, lcd);                
	 	  	else for(b=0;b<size;b++) lcd_sendd(bckcolor, lcd);

			}
		}

/*		for (a=0;a<area_y*size;a++)
		{
			for (d=1;d<=area_x;d++)
			{
				if (mask==1)
				{
					lcd_area(x+d, y+a, x+d+8, y+a, lcd);
					lcd_sendc(0x5C,0x00, lcd);
		   		mask=0x100;
					ch=pgm_read_byte(&bw_picture[(((a/size)*area_x)/8)+c+(d/8)]);
				}
	    	mask=mask/2;
				if (ch&mask) for(b=0;b<size;b++) lcd_sendd(color, lcd);                
	 	  	else for(b=0;b<size;b++) lcd_sendd(bckcolor, lcd);
			}
		}

*/
	}

}


void lcd_scroll(unsigned char offset, unsigned char lcd)
{
	if(lcd_type==1)	lcd_sendc(0x11, offset, lcd);
	else if(lcd_type==2)
	{
		lcd_sendc(0xAB, 0x00, lcd);
		lcd_sendd0(offset, lcd);
	}
}


void lcd_scroll_set(unsigned char start, unsigned char end, unsigned char mode, unsigned char lcd)
{
 	lcd_sendc(0xAA, 0x00, lcd);
	lcd_sendd0(start, lcd);
	lcd_sendd0(end-1, lcd);
	lcd_sendd0(end-1, lcd);
	lcd_sendd0(mode, lcd);
}

void lcd_clr_dspl(unsigned int color, unsigned char lcd)
{
 unsigned int a;

 

	if(lcd_type==1)
	{
  	lcd_area(0, 0, (LCD_WIDTH-1), (LCD_HEIGHT-1), lcd);
	 	LCD_RS_ENABLE(); //data
		if (lcd==1) LCD_CS1_ENABLE();
		else if (lcd==2) LCD_CS2_ENABLE();
		else if (lcd==3) 
		{
			LCD_CS2_ENABLE();
			LCD_CS1_ENABLE();
		}

		for(a=(LCD_WIDTH*LCD_HEIGHT);a!=0;a--) spi_write(color); 
	}
	else if(lcd_type==2)
	{

	  lcd_area(0,0,176,132, lcd);

		lcd_sendc(0x5C,0x00, lcd);
 		
		LCD_RS_DISABLE();
 		if (lcd==1) LCD_CS1_ENABLE();
		else if (lcd==2) LCD_CS2_ENABLE();
		else if (lcd==3) 
		{
			LCD_CS2_ENABLE();
			LCD_CS1_ENABLE();
		}

 		for(a=(LCD_WIDTH*LCD_HEIGHT);a!=0;a--)
		{
			spi_write(color>>8);
			spi_write(color);
		}
//			lcd_sendd(color, lcd);
//			_delay_ms(10);
	}


  LCD_CS1_DISABLE();
  LCD_CS2_DISABLE();

}

void lcd_init(void)
{
	unsigned char a;
//----------------init port-----------------------
	SPCR=80;
//	SPCR = (1<<SPE)|(1<<MSTR);//|(1<<SPR1)|(1<<SPR0)); 								//enable SPI, Master, clock=f_cpu/4
	SPSR = (1<<SPI2X); 										//x2 -> clock=f_cpu/2

//------------------------------------------------

	if(lcd_type==1)
	{

		RED=0xE0;
		GREEN=0x1C;
		BLUE=0x03;
 		YELLOW=0xFC;
		WHITE=0xFF;
		BLACK=0x00;
		GREY=0xB6;

	  LCD_CS1_DISABLE();
	  LCD_CS2_DISABLE();
	  LCD_RS_DISABLE();
	  LCD_RST_ENABLE();
	  _delay_ms(50);
	  LCD_RST_DISABLE();
	  _delay_ms(10);
		for (a=0;a<20;a=a+2) lcd_sendc(pgm_read_byte(&init1[a]),pgm_read_byte(&init1[a+1]),3);
	  _delay_ms(5); //important: 7-8 ms
		for (a=0;a<40;a=a+2) lcd_sendc(pgm_read_byte(&init2[a]),pgm_read_byte(&init2[a+1]),3);
	  _delay_ms(50);
	  lcd_sendc(0x80, 0x01, 3); 
		lcd_sendc(0xEF, 0x90, 3);
		#if defined(LCD_ROTATE)
		# if defined(LCD_MIRROR)
		  lcd_sendc(0x01, 0xC0, 3); //x1->x0, y1->y0
		  lcd_sendc(0x05, 0x00, 3); //0x04=rotate, 0x00=normal
		# else
		  lcd_sendc(0x01, 0x00, 3); //x0->x1, y0->y1
		  lcd_sendc(0x05, 0x00, 3); //0x04=rotate, 0x00=normal
		# endif
		#else
		# if defined(LCD_MIRROR)
		  lcd_sendc(0x01, 0x80, 3); //x0->x1, y1->y0
		  lcd_sendc(0x05, 0x04, 3); //0x04=rotate, 0x00=normal
		# else
		  lcd_sendc(0x01, 0x40, 3); //x1->x0, y0->y1
		  lcd_sendc(0x05, 0x04, 3); //0x04=rotate, 0x00=normal
		# endif
		#endif
		lcd_sendc(0xe8, 0x00, 3);
	}
	else if(lcd_type==2)
	{
		RED=0xF800;
		GREEN=0x7E0;
		BLUE=0x1F;
 		YELLOW=0xFFE0;
		WHITE=0xFFFF;
		BLACK=0x0000;
//		GREY=0xC618;
		GREY=0xA514;

		LCD_RST_ENABLE();
	  LCD_CS1_DISABLE();
	  LCD_CS2_DISABLE();
	  LCD_RS_DISABLE();
	  _delay_ms(10);
	  LCD_RST_DISABLE();
	  _delay_ms(35);
	 	LCD_CS1_ENABLE();
	 	LCD_CS2_ENABLE();
		lcd_sendc(0xBC, 0x00, 3);
		lcd_sendd0(0x2B, 3);
	  LCD_CS1_DISABLE();
	  LCD_CS2_DISABLE();
	  LCD_CS1_ENABLE();
	  LCD_CS2_ENABLE();
		lcd_sendc(0xCA, 0x00, 3);
	 	for (a=0;a<9;a++) lcd_sendd0(pgm_read_byte(&init1_l2f50[a]), 3);	
		lcd_sendc(0xCB, 0x00, 3);
	 	for (a=0;a<29;a++)
		{
			lcd_sendd0(pgm_read_byte(&init2_l2f50[a]), 3);	
			lcd_sendd0(0x00, 3);
		}
	 	for (a=0;a<34;a++)
		{
			lcd_sendd0(pgm_read_byte(&init3_l2f50[a]), 3);	
			lcd_sendd0(0x01, 3);
		}
		lcd_sendc(0xCC, 0x00, 3);
	 	for (a=0;a<15;a++) lcd_sendd0(pgm_read_byte(&init4_l2f50[a]), 3);	
		lcd_sendc(0xCD, 0x00, 3);
		lcd_sendd0(0x00, 3);
		lcd_sendc(0xD0, 0x00, 3);
		lcd_sendd0(0x00, 3);
		lcd_sendc(0x94, 0x00, 3);
	  _delay_ms(7);
		lcd_area(0,0,176,132, 3);
		lcd_sendc(0xAF, 0x00, 3);
	}



	lcd_clr_dspl(0, 3);

}


void lcd_sendd0(unsigned char data, unsigned char lcd)
{
  LCD_RS_DISABLE(); //data
//	LCD_RS_ENABLE();
  if (lcd==1) LCD_CS1_ENABLE();
	else if (lcd==2) LCD_CS2_ENABLE();
	else if (lcd==3) 
	{
		LCD_CS2_ENABLE();
		LCD_CS1_ENABLE();
	}
  spi_write(data);
  spi_write(0x00);
  LCD_CS1_DISABLE();
  LCD_CS2_DISABLE();
}



void obdlznik (unsigned char x, unsigned char y, unsigned char x_DLZKA, unsigned char y_DLZKA, unsigned int farba)
{
	unsigned int a;
	lcd_area(x,y,x+x_DLZKA-1,y+y_DLZKA-1,2);
	if (lcd_type==2)	lcd_sendc(0x5C,0x00, 2);	
	for (a=0; a<(x_DLZKA*y_DLZKA); a++) lcd_sendd(farba, 2);
}




void lcd_on(unsigned char lcd)
{
	if(lcd_type==1)
	{
	 	lcd_sendc(0xef, 0x90, lcd);
	  lcd_sendc(0x00, 0x00, lcd);
	}
	else if(lcd_type==2) lcd_sendc(0xAF, 0x00, lcd);
}


void lcd_off(unsigned char lcd)
{
	if(lcd_type==1)
	{
	 	lcd_sendc(0xef, 0x90, lcd);
	  lcd_sendc(0x00, 0x40, lcd);
	}
	else if(lcd_type==2) lcd_sendc(0xAE, 0x00, lcd);
}

void lcd_sendd(unsigned int color, unsigned char lcd)
{
  if(lcd_type==1) LCD_RS_ENABLE(); //data
	else if(lcd_type==2) LCD_RS_DISABLE();

  if (lcd==1) LCD_CS1_ENABLE();
	else if (lcd==2) LCD_CS2_ENABLE();
	else if (lcd==3) 
	{
		LCD_CS2_ENABLE();
		LCD_CS1_ENABLE();
	}

  if(lcd_type==2) spi_write(color>>8);
  spi_write(color);

  LCD_CS1_DISABLE();
  LCD_CS2_DISABLE();
}


void lcd_sendc(unsigned int reg, unsigned int param, unsigned char lcd)
{
  if(lcd_type==1) LCD_RS_DISABLE(); //cmd
	else if(lcd_type==2) LCD_RS_ENABLE();

  if (lcd==1) LCD_CS1_ENABLE();
	else if (lcd==2) LCD_CS2_ENABLE();
	else if (lcd==3) 
	{
		LCD_CS2_ENABLE();
		LCD_CS1_ENABLE();
	}

  spi_write(reg);
  spi_write(param);

  LCD_CS1_DISABLE();
  LCD_CS2_DISABLE();
}


void spi_write(char c)
{
	SPDR = c;
	while (ChckBit(SPSR,SPIF)==0);
}



const char init1[] PROGMEM = 
{
	0xEF, 0x00, 0xEE, 0x04, 0x1B, 0x04, 0xFE, 0xFE, 0xFE, 0xFE, 
	0xEF, 0x90, 0x4A, 0x04, 0x7F, 0x3F, 0xEE, 0x04, 0x43, 0x06,
};


const char init2[] PROGMEM = 
{
	0xEF, 0x90, 0x09, 0x83, 0x08, 0x00, 0x0B, 0xAF, 0x0A, 0x00, 
	0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0xEF, 0x00, 0xEE, 0x0C,
	0xEF, 0x90, 0x00, 0x80, 0xEF, 0xB0, 0x49, 0x02, 0xEF, 0x00, 
	0x7F, 0x01, 0xE1, 0x81, 0xE2, 0x02, 0xE2, 0x76, 0xE1, 0x83,
};


const char init1_l2f50[] PROGMEM = 
{
	0x4C, 0x01, 0x53, 0x00, 0x02, 0xB4, 0xB0, 0x02, 0x00,
};


const char init2_l2f50[] PROGMEM = 
{
	0x11,0x27,0x3C,0x4C,0x5D,0x6C,0x78,0x84,0x90,0x99,
	0xA2,0xAA,0xB2,0xBA,0xC0,0xC7,0xCC,0xD2,0xD7,0xDC,
	0xE0,0xE4,0xE8,0xED,0xF0,0xF4,0xF7,0xFB,0xFE,
};


const char init3_l2f50[] PROGMEM = 
{
	0x01,0x03,0x06,0x09,0x0B,0x0E,0x10,0x13,0x15,0x17,
	0x19,0x1C,0x1E,0x20,0x22,0x24,0x26,0x28,0x2A,0x2C,
	0x2D,0x2F,0x31,0x33,0x35,0x37,0x39,0x3B,0x3D,0x3F,
	0x42,0x44,0x47,0x5E,
};

const char init4_l2f50[] PROGMEM = 
{
	0x13,0x23,0x2D,0x33,0x38,0x3C,0x40,0x43,0x46,0x48,
	0x4A,0x4C,0x4E,0x50,0x64,
};
