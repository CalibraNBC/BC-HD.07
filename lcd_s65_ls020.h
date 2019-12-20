#ifndef _lcd_s65_ls020_
#define _lcd_s65_ls020_

#define CHAR_H 12
#define CHAR_W 8

//#define LCD_MIRROR
//#define LCD_ROTATE

#if defined(LCD_ROTATE)
# define LCD_WIDTH           (132)
# define LCD_HEIGHT          (176)
#else
# define LCD_WIDTH           (176)
# define LCD_HEIGHT          (132)
#endif

unsigned char lcd_type;


void lcd_init(void);
void lcd_clr_dspl(unsigned int color, unsigned char lcd);
void lcd_sendd(unsigned int color, unsigned char lcd);
void lcd_sendc(unsigned int reg, unsigned int param, unsigned char lcd);
void lcd_putchar(unsigned char c, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd);
void lcd_putstring(char *addre, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd);
void lcd_area(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned char lcd);
void lcd_cursor(unsigned int x, unsigned int y, unsigned char lcd);
void spi_write(char c);
void lcd_on(unsigned char lcd);
void lcd_off(unsigned char lcd);
void lcd_putnr(unsigned long c, char ciarka, char znak, unsigned char poc_miest, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd);
unsigned char lcd_putchars(char poc, char znak, unsigned char x, unsigned char y, unsigned char size, unsigned int textcolor, unsigned int backcolor, unsigned char lcd);
void lcd_put_bw_picture(unsigned int c, unsigned char x, unsigned char y, unsigned char size, unsigned char area_x, unsigned char area_y,unsigned int color, unsigned int bckcolor, unsigned char lcd);
void lcd_scroll(unsigned char offset, unsigned char lcd);
void obdlznik (unsigned char x, unsigned char y, unsigned char x_dlzka, unsigned char y_dlzka, unsigned int farba);
void lcd_sendd0(unsigned char data, unsigned char lcd);


#endif
