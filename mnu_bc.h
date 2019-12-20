#ifndef _mnu_bc_
#define _mnu_bc_


char mnu_bc(void);
void zobraz_lcd1(void);
void zobraz_km(unsigned char cis);
void zobraz_cislo_menu(unsigned char cis);
void zobraz_rychlost(unsigned char cis);
void zobraz_spotrebu(unsigned char cis);
void zobraz_cenu(unsigned char cis);
void zobraz_dobu(unsigned char cis);

unsigned long vypocet_km(unsigned char cis);
unsigned long vypocet_spotrebovane_palivo(unsigned char cis);
unsigned long vypocet_doba_jazdy(unsigned char cis);
unsigned int vypocet_priemerna_rychlost(unsigned long vzdialenost, unsigned long cas);
unsigned int vypocet_priemerna_spotreba(unsigned char cis);
void reset_denne(unsigned char a);

#endif
