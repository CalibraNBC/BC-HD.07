#ifndef _variables_
#define _variables_

#include "definitions.h"

unsigned char stav_test;


//-------------------------Nastavenia---------
unsigned int 		poc_ms_ml;
unsigned int 		poc_imp_10m;
unsigned int 		dlzka_merania;

unsigned long 	poc_des_mm_1_imp;
unsigned char 	poc_zubov_abs;
unsigned long 	obvod_kolesa;
unsigned char 	poc_valcov;
unsigned int 		vstrekovac;
unsigned int 		cena_za_l;
unsigned long		cena_za_l_u;
char 						offset_x, offset_y;
unsigned int 		servis;
unsigned long 	servis_km;
unsigned char 	nick[10];

unsigned char 	poc_bc_menu;

unsigned char priemer,sirka,profil;

float						bat_odb;
//unsigned char		bat_nd;

unsigned int		kvt;
//unsigned int		kvt_1;
//unsigned int		kvt_2;
float						kv1;
//float						kv1_1;
//unsigned int		kv1_2;
float						kv2;
//float						kv2_1;
//unsigned int		kv2_2;
float						kv3;
//float						kv3_1;
//unsigned int		kv3_2;
float						kp;
float						kbl;
unsigned int 		dn[70];
unsigned int 		dndevelop[70];
//float						kp_1;
//unsigned int		kp_2;


//--------------------------data------------
unsigned long 	km;
unsigned long 	spotrebovane_palivo;
unsigned int 		max_spd;
unsigned long 	doba_jazdy;

unsigned long 	km_denne[5];
unsigned long 	spotrebovane_palivo_denne[5];
unsigned int 		max_spd_denne[5];
unsigned long 	doba_jazdy_denne[5];
unsigned char		reset_j;

unsigned long   km_ss[3];
unsigned long   spotrebovane_palivo_ss[3];
unsigned long   doba_jazdy_ss[3];
unsigned char   status_ss[3];

unsigned long   km_pv[PV_POC_MERANI];
unsigned long 	spotrebovane_palivo_pv[PV_POC_MERANI];
unsigned int 		priemerna_spotreba_pv;

//--------------------hodiny----------------
unsigned int 		hodiny_ms;
unsigned char 	hodiny_s,hodiny_m,hodiny_h;
unsigned char 	hodiny_on;


//--------------------podsvietenie----------
unsigned char 	sv_odpocet;
unsigned char	 	sv_hodnota;
unsigned int 		sv_nap		;
unsigned int   	sv_nap_val[3];

//--------------------meranie paliva-------
/*
unsigned char 	n_status_1, n_status_2, n_timer;
int 						n_meranie1[N_POC_MERANI_1];
int 						n_meranie2[N_POC_MERANI_2];
*/
//unsigned char n_1_status_1, n_1_timer;
//int 					n_1_meranie1[N_1_POC_MERANI_1];
//int						n_1_hodnota;

unsigned int 		n_obsah_temp;
unsigned char		nadrz_timer;
//unsigned int 		nadrz_meranie[N_POC_MERANI];
unsigned int 		nadrz_status;

unsigned int		n_hodnota;
unsigned int  	n_adc;

unsigned int		n_posledna_hodnota;
unsigned long		n_spotrebovane_palivo;
unsigned int 		n_voltage;

unsigned char 	pal_tmp[POC_MERANI_PALIVA];
unsigned char 	pal_tmp_poc;
unsigned char 	pal_act;
unsigned char		posledna_kontrola;
unsigned char 	pal_stav;
unsigned char 	pal_s;
unsigned char		pal_doba;
unsigned char		pal_zapis;
unsigned char		pal_cak;
unsigned char		pal_hodnota;
char 						pal_korekcia;
//unsigned int		dojazd;

unsigned char		pal_start;

//------------------------------------------
unsigned int 		dlzka_vstreku;
unsigned char 	motor_on;
unsigned char 	stav;
unsigned int 		vstrek_start;
unsigned int		doba_vstreku;

int							teplota;		//vonkajšia teplota
int							teplota_motoru;		//teplota motoru
unsigned char 	teplota_motoru_cidlo;
unsigned char		cidlo_teploty_motoru; //
unsigned char  	sig_teploty_motoru;
unsigned int  	sig_namrazy;
unsigned int 		sig_nadrze;

unsigned int		napatie;		//napatie v palubnej sieti

//char						act_max_pretazenie_y;
//char						act_max_pretazenie_x;

//---------------Max menu-------------------
char 						max_pretazenie_y;
char						max_pretazenie_x;
unsigned char		max_zrychlenie;
unsigned char		min_spotreba_1;
unsigned char		min_spotreba_2;
unsigned char		min_spotreba_3;
unsigned int 		max_dojazd;

//---------------Farby-------------------
unsigned int M_COL_BCK;
unsigned int M_COL_TXT;

unsigned int RED, GREEN, BLUE, YELLOW, WHITE, BLACK, GREY;

unsigned int COL_TXT_LCD2;
unsigned int COL_TXT_LCD1;

//----------------kavicka---------------
unsigned int 	kavicka_s;
unsigned int	kavicka_o;


//---------------Motor-----------------
unsigned int 	otacky;
unsigned char	otacky_del;
int 					ot_cas, ot_cas_old;
unsigned char	ot_imp, ot_imp_old;
unsigned char ot_mer_imp;
unsigned char ot_status;
unsigned int 	otacky_max;

//-------------------------------------
unsigned char mnu_zrychlenie_on;
unsigned char mnu_pretazenie_on;
unsigned char mnu_motor_on;
unsigned char mnu_400m_on;
unsigned char mnu_stopky_on;
unsigned char mnu_develop_on;
unsigned char mnu_max;

unsigned int poc_stav;

unsigned int lambda;
unsigned int lambda_old;
unsigned int lambda_old1;
unsigned char lambda_meas;
unsigned char lambda_on;

//unsigned long wbl_ratio, wbl_plus, wbl_lambda, wbl_lambda1, wbl_afr;
//unsigned char	wbl_limitok, wbl_limitnok;

unsigned long wbl_afr_0V, wbl_afr_5V, wbl_afr;
unsigned long	wbl_ratio;
unsigned char	wbl_limitok, wbl_limitnok;

#endif
