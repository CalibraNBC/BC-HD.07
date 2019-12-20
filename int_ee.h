#ifndef _int_ee_
#define _int_ee_

char skontroluj_ee(void);
char checksum_error(unsigned int zero, unsigned int checksum);//vracia 1 pri chybe checksumu
void nacitaj_nastavenia(void);
void nacitaj_data(void);
char zapis_ee(unsigned long data, void *pointer_ee, int n);		//vracia 1 pri chybe zápisu
char zapis_checksum(unsigned int zero, unsigned int pocet);		//vracia 1 pri chybe zápisu checksumu
//char zapis_nastaveni_kolesa_bc(unsigned char sirka, unsigned char profil, unsigned char priemer);  //vracia 1 pri chybe zápisu
char zapis_nastaveni_bc(void);
char zapis_dat(void);


#endif
