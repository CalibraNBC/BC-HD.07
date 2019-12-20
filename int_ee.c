#include "int_ee.h"
#include "definitions.h"
#include "settings.h"
#include <avr/eeprom.h>
#include "variables.h"
#include "language.h"
#include <avr/pgmspace.h>
#include "lcd_s65_ls020.h"
#include "settings.h"


typedef unsigned char BYTE;
BYTE *p_ee_zero=(BYTE*) 0;
 

/*
char skontroluj_ee(void)
{
	if (eeprom_read_byte(p_ee_zero + EE_VEE)!= PODP_EE) return(ERR_EE_VER);

	if (checksum_error(EE_HW_DATA_START,EE_HW_CHECKSUM)) return(ERR_EE_HW);
	if (checksum_error(EE_BC_DATA_START,EE_BC_CHECKSUM)) return(ERR_EE_NAST_BC);
	if (checksum_error(EE_DJ_DATA_START,EE_DJ_CHECKSUM)) return(ERR_EE_DATA);
	return(0);
}

*/
char checksum_error(unsigned int zero, unsigned int checksum)
{
	unsigned int a; 
	unsigned char	tmp=0;

	for (a=0;a<checksum-zero;a++) tmp=tmp+eeprom_read_byte(p_ee_zero + zero +a);
	if (tmp==eeprom_read_byte(p_ee_zero + checksum)) return(0);
	return(1);
}

void nacitaj_nastavenia(void)
{
	unsigned char a;
/*
	zapis_ee(' ',p_ee_zero + EE_NICK,1);
	zapis_ee(' ',p_ee_zero + EE_NICK + 1,1);
	zapis_ee(' ',p_ee_zero + EE_NICK + 2,1);
	zapis_ee('B',p_ee_zero + EE_NICK + 3,1);
	zapis_ee('Y',p_ee_zero + EE_NICK + 4,1);
	zapis_ee('E',p_ee_zero + EE_NICK + 5,1);
	zapis_ee(' ',p_ee_zero + EE_NICK + 6,1);
	zapis_ee(' ',p_ee_zero + EE_NICK + 7,1);
	zapis_ee(' ',p_ee_zero + EE_NICK + 8,1);
	zapis_ee(' ',p_ee_zero + EE_NICK + 9,1);
*/

	if (eeprom_read_byte(p_ee_zero + EE_VEE)!= PODP_EE)
	{
		lcd_putstring(PSTR("EE VERSION"),10,70,1,M_COL_TXT,M_COL_BCK,1);
		while(1);
	}


//---------------------------HW----------------------------------
	for (a=0;a<=9;a++) nick[a]=eeprom_read_byte(p_ee_zero + EE_NICK+a);
	eeprom_read_block(&bat_odb,p_ee_zero + EE_ODB,4);
	eeprom_read_block(&kvt,p_ee_zero + EE_KVT,2);
	eeprom_read_block(&kv1,p_ee_zero + EE_KV1,4);
	eeprom_read_block(&kv2,p_ee_zero + EE_KV2,4);
	eeprom_read_block(&kv3,p_ee_zero + EE_KV3,4);
	eeprom_read_block(&kp,p_ee_zero + EE_KP,4);
	eeprom_read_block(&kbl,p_ee_zero + EE_KBL,4);

	for (a=0;a<70;a++) 
	{
		eeprom_read_block(&dn[a],p_ee_zero + EE_DN+a*2,2);
//		dn[a]=dn[a]/kp;
	}


//--------------------------BC-----------------------------------
	eeprom_read_block(&obvod_kolesa,p_ee_zero + EE_KOLESA,2);
	poc_zubov_abs=eeprom_read_byte(p_ee_zero + EE_ABS);
	poc_valcov=eeprom_read_byte(p_ee_zero + EE_VALCE);
	eeprom_read_block(&vstrekovac,p_ee_zero + EE_VSTREK,2);
	eeprom_read_block(&cena_za_l,p_ee_zero + EE_CENA,2);
	eeprom_read_block(&servis,p_ee_zero + EE_SERVIS,2);
	eeprom_read_block(&servis_km,p_ee_zero + EE_SERVIS_KM,4);
	offset_x=eeprom_read_byte(p_ee_zero + EE_OFFSET_X);
	offset_y=eeprom_read_byte(p_ee_zero + EE_OFFSET_Y);
	for (a=0;a<4;a++) eeprom_read_block(&sv_nap_val[a],p_ee_zero + EE_SV_NAP_VAL+a*2,2);
	eeprom_read_block(&cena_za_l_u,p_ee_zero + EE_CENAU,4);

	if(cena_za_l_u>99999)cena_za_l_u=100;

	priemer=eeprom_read_byte(p_ee_zero + EE_PRIEMER_KOLESA);
	sirka=eeprom_read_byte(p_ee_zero + EE_SIRKA_KOLESA);
	profil=eeprom_read_byte(p_ee_zero + EE_PROFIL_KOLESA);


#ifdef MPH
	poc_des_mm_1_imp=(((obvod_kolesa*100)/poc_zubov_abs)+5) /16.1; // pocet desatín milimetra na jeden impulz
#endif
#ifndef MPH
	poc_des_mm_1_imp=(((obvod_kolesa*100)/poc_zubov_abs)+5) /10; // pocet desatín milimetra na jeden impulz
#endif
	poc_imp_10m =((1000000/poc_des_mm_1_imp)+5)/10;		// pocet impulzov na 10M
	dlzka_merania =(((1/(27.77778/poc_des_mm_1_imp))*100)+5)/10;	//dlzka merania rychlosti
	poc_ms_ml=(10000000/((vstrekovac*poc_valcov)/6));

}

/*
char zapis_nastaveni_kolesa_bc(unsigned char sirka, unsigned char profil, unsigned char priemer)
{
	if (zapis_ee(sirka,p_ee_zero + EE_SIRKA_KOLESA,1)) return(1);
	if (zapis_ee(profil,p_ee_zero + EE_PROFIL_KOLESA,1)) return(1);
	if (zapis_ee(priemer,p_ee_zero + EE_PRIEMER_KOLESA,1)) return(1);
	return (zapis_nastaveni_bc());
}
*/

char zapis_nastaveni_bc(void)
{
	unsigned char a;

	if (zapis_ee(offset_x,p_ee_zero + EE_OFFSET_X,1)) return(1);
	if (zapis_ee(offset_y,p_ee_zero + EE_OFFSET_Y,1)) return(1);
	if (zapis_ee(obvod_kolesa,p_ee_zero + EE_KOLESA,2)) return(1);
	if (zapis_ee(poc_zubov_abs,p_ee_zero + EE_ABS,1)) return(1);
	if (zapis_ee(poc_valcov,p_ee_zero + EE_VALCE,1)) return(1);
	if (zapis_ee(vstrekovac,p_ee_zero + EE_VSTREK,2)) return(1);
	if (zapis_ee(cena_za_l,p_ee_zero + EE_CENA,2)) return(1);
	if (zapis_ee(servis,p_ee_zero + EE_SERVIS,2)) return(1);
	if (zapis_ee(servis_km,p_ee_zero + EE_SERVIS_KM,4)) return(1);
	if (zapis_ee(sirka,p_ee_zero + EE_SIRKA_KOLESA,1)) return(1);
	if (zapis_ee(profil,p_ee_zero + EE_PROFIL_KOLESA,1)) return(1);
	if (zapis_ee(priemer,p_ee_zero + EE_PRIEMER_KOLESA,1)) return(1);
	for (a=0;a<3;a++) if (zapis_ee(sv_nap_val[a],p_ee_zero + EE_SV_NAP_VAL+a*2,2)) return(1);

	for (a=0;a<=9;a++) if (zapis_ee(nick[a],p_ee_zero + EE_NICK+a,1)) return(1);

	if (zapis_ee(cena_za_l_u,p_ee_zero + EE_CENAU,4)) return(1);

	zapis_checksum(EE_BC_DATA_START,EE_BC_CHECKSUM);
	return(0);
}


void nacitaj_data(void)
{
	unsigned char a;
	int temp1; 

	eeprom_read_block(&km,p_ee_zero + EE_KM,4);
	eeprom_read_block(&temp1,p_ee_zero + EE_TCNT1,2);
	eeprom_read_block(&spotrebovane_palivo,p_ee_zero + EE_SPOT_PALIVO,4);
	eeprom_read_block(&max_spd,p_ee_zero + EE_MAX_SPD,2);
	eeprom_read_block(&doba_jazdy,p_ee_zero + EE_DOBA_JAZDY,4);
	TCNT1=temp1;
	for (a=0; a<=4; a++)
	{
		eeprom_read_block(&km_denne[a],p_ee_zero + EE_KM + ((a+1)*EE_VELKOST_DAT),4);
		eeprom_read_block(&spotrebovane_palivo_denne[a],p_ee_zero + EE_SPOT_PALIVO + ((a+1)*EE_VELKOST_DAT),4);
		eeprom_read_block(&max_spd_denne[a],p_ee_zero + EE_MAX_SPD + ((a+1)*EE_VELKOST_DAT),2);
		eeprom_read_block(&doba_jazdy_denne[a],p_ee_zero + EE_DOBA_JAZDY + ((a+1)*EE_VELKOST_DAT),4);
	}

	for (a=0; a<3; a++)
	{
		eeprom_read_block(&km_ss[a],p_ee_zero + EE_KM_SS + (a*EE_VELKOST_DAT_SS),4);
		eeprom_read_block(&spotrebovane_palivo_ss[a],p_ee_zero + EE_SPOT_PALIVO_SS + (a*EE_VELKOST_DAT_SS),4);
		eeprom_read_block(&doba_jazdy_ss[a],p_ee_zero + EE_DOBA_JAZDY_SS + (a*EE_VELKOST_DAT_SS),4);
		eeprom_read_block(&status_ss[a],p_ee_zero + EE_STATUS_SS + (a*EE_VELKOST_DAT_SS),1);
	}

	eeprom_read_block(&max_pretazenie_y,p_ee_zero + EE_MAX_PRETAZENIE_Y,1);
	eeprom_read_block(&max_pretazenie_x,p_ee_zero + EE_MAX_PRETAZENIE_X,1);
	eeprom_read_block(&max_zrychlenie,p_ee_zero + EE_MAX_ZRYCHLENIE,1);
	eeprom_read_block(&min_spotreba_1,p_ee_zero + EE_MIN_SPOTREBA_1,1);
	eeprom_read_block(&min_spotreba_2,p_ee_zero + EE_MIN_SPOTREBA_2,1);
	eeprom_read_block(&min_spotreba_3,p_ee_zero + EE_MIN_SPOTREBA_3,1);
	eeprom_read_block(&max_dojazd,p_ee_zero + EE_MAX_DOJAZD,2);

}


char zapis_dat(void)
{
	unsigned char a;
	if (zapis_ee(TCNT1,p_ee_zero + EE_TCNT1,2)) return(1);
	if (zapis_ee(km,p_ee_zero + EE_KM,4)) return(1);
	if (zapis_ee(spotrebovane_palivo,p_ee_zero + EE_SPOT_PALIVO,4)) return(1);
	if (zapis_ee(max_spd,p_ee_zero + EE_MAX_SPD,2)) return(1);
	if (zapis_ee(doba_jazdy,p_ee_zero + EE_DOBA_JAZDY,4)) return(1);

	for (a=0; a<=4; a++)
	{
		if (zapis_ee(km_denne[a],p_ee_zero + EE_KM + ((a+1)*EE_VELKOST_DAT),4)) return(1);
		if (zapis_ee(spotrebovane_palivo_denne[a],p_ee_zero + EE_SPOT_PALIVO + ((a+1)*EE_VELKOST_DAT),4)) return(1);
		if (zapis_ee(max_spd_denne[a],p_ee_zero + EE_MAX_SPD + ((a+1)*EE_VELKOST_DAT),2)) return(1);
		if (zapis_ee(doba_jazdy_denne[a],p_ee_zero + EE_DOBA_JAZDY + ((a+1)*EE_VELKOST_DAT),4)) return(1);
	}

	for (a=0; a<3; a++)
	{
		if (zapis_ee(km_ss[a],p_ee_zero + EE_KM_SS + (a*EE_VELKOST_DAT_SS),4)) return(1);
		if (zapis_ee(spotrebovane_palivo_ss[a],p_ee_zero + EE_SPOT_PALIVO_SS + (a*EE_VELKOST_DAT_SS),4)) return(1);
		if (zapis_ee(doba_jazdy_ss[a],p_ee_zero + EE_DOBA_JAZDY_SS + (a*EE_VELKOST_DAT_SS),4)) return(1);
		if (zapis_ee(status_ss[a],p_ee_zero + EE_STATUS_SS + (a*EE_VELKOST_DAT_SS),1)) return(1);
	}

	if (zapis_ee(max_pretazenie_y,p_ee_zero + EE_MAX_PRETAZENIE_Y,1)) return(1);
	if (zapis_ee(max_pretazenie_x,p_ee_zero + EE_MAX_PRETAZENIE_X,1)) return(1);
	if (zapis_ee(max_zrychlenie,p_ee_zero + EE_MAX_ZRYCHLENIE,1)) return(1);
	if (zapis_ee(min_spotreba_1,p_ee_zero + EE_MIN_SPOTREBA_1,1)) return(1);
	if (zapis_ee(min_spotreba_2,p_ee_zero + EE_MIN_SPOTREBA_2,1)) return(1);
	if (zapis_ee(min_spotreba_3,p_ee_zero + EE_MIN_SPOTREBA_3,1)) return(1);
	if (zapis_ee(max_dojazd,p_ee_zero + EE_MAX_DOJAZD,2)) return(1);


	zapis_checksum(EE_DJ_DATA_START,EE_DJ_CHECKSUM);
	return(0);
}


char zapis_ee(unsigned long data, void *pointer_ee, int n)
{
	char count=3;
	int a;
	unsigned char temp_char, *p_temp_char;

	eeprom_write_block(&data,pointer_ee,n);
	a=0;
	p_temp_char=&data;
	for (a=0; a<n; a++)
	{
		temp_char=*p_temp_char;
		while (count)
		{
			if (eeprom_read_byte(pointer_ee+a)==temp_char) break;
			else eeprom_write_byte(pointer_ee+a,temp_char);
		count--;
		}
		if (count==0) return(1);
		p_temp_char++;
	}	
	return(0);
}



char zapis_checksum(unsigned int zero, unsigned int checksum)
{
	unsigned int a; 
	unsigned char tmpchecksum=0;

	for (a=0;a<checksum-zero;a++)
	{
		tmpchecksum=tmpchecksum+eeprom_read_byte(p_ee_zero + zero + a);
	}
	return(zapis_ee(tmpchecksum,p_ee_zero + checksum,1));
}
