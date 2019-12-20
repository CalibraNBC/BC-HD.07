//#ifndef _definitions_
//#define _definitions_

#ifndef SENZ_SKODA
	#define TXT_VERZIA "HD.07"
#endif


#ifdef SENZ_SKODA
	#define TXT_VERZIA "HD.s7"
#endif


#include "settings.h"
#include "language.h"



#define BAT_INVERS				1250		//Hodnota/100 pri ktorej sa zneguje zobrazenie batÈrie
#define NAMRAZA						40			//Hodnota/10 pri ktorej zneguje zobrazenie teploty
#define BAT_ND						70			//Napatie diody
#define TEMP_SENZOR				50			//odpor/100 Ëidla teploty pri 25∞C
#define BAT_BEEP					1190
#define BAT_BEEP_TIMER		30
#define REZERVA						8				//Pod t˙to hodnodu zobrazÌ palivo negovanÈ

#define	LAMBDA_LOW				25			//chud· zmes do napatie/100
#define LAMBDA_HIGH				75			//bohat· zmes od napatie/100

#ifdef MPH
	#define REZERVA_DOJAZD	  4				//Pod t˙to hodnodu *10 zobrazÌ dojazd negovan˝
#endif
#ifndef MPH
	#define REZERVA_DOJAZD	  6				//Pod t˙to hodnodu *10 zobrazÌ dojazd negovan˝
#endif

#define SIG_NADRZ					8				//Hodnota pri ktorej signalizuje n·drû

#define BEEP_ON										//Zapnutie akustickej signaliz·cie


#ifndef SENZ_SKODA
	#define TEMP_MOTOR_A					0.00157
	#define TEMP_MOTOR_B					0.00025
	#define TEMP_MOTOR_C					0.0000002
	#define TEMP_MOTOR_R					225//733
#endif

#ifdef SENZ_SKODA
	#define TEMP_MOTOR_A					0.00176
	#define TEMP_MOTOR_B					0.00024
	#define TEMP_MOTOR_C					0.0000001
	#define TEMP_MOTOR_R					450//733
#endif


#define TEMP_MOTOR_RD					14700
#define	TEPLOTA_MOTORU_MIN		60	
#define	TEPLOTA_MOTORU_MAX		140
#define TEPLOTA_SIG						110



//------------------------ChybovÈ hl·öky-------------------------
#define ERR_EE_HW							1		//Checksum pri ötarte
#define ERR_EE_DATA						3		//Checksum pri ötarte
#define ERR_EE_NAST_BC				4		//Checksum pri ötarte
#define ERR_EE_NAST_BC_UKL		5		//Ukladanie nastavenÌ BC
#define ERR_EE_DATA_BC				6		//Ukladanie d·t BC
#define ERR_EE_VER						7		//Nespr·vna verzia rozloûenia d·t v EE


//-----------------------Meranie paliva v n·drûi-----------------

#define N_PRETAZENIE_Y 		3
#define N_PRETAZENIE_X 		3
//#define N_ODCHYLKA				1
//#define N_POC_MERANI			3			
//#define N_MIN_TANKOVANIE	6
//#define N_MIN_STANIE			8			//doba v s po zastavenÌ po ktorej meria nadrz
//#define N_MER_PO_STARTU		3

#define F_MERANIA					6			//7=7,8x/s 6=15,6x/s 
#define POC_MERANI_PALIVA	30
//#define MER_PO_ZASTAVENI	3
//#define CAK_MIN						10
//#define CAK_OST						2
//#define POC_PRIEMER				3
#define CAS_SIG_PO_STARTE	20



#define N_MAX_ROZD_START	6
#define N_MIN_ROZD_START	5
#define N_MAX_ROZD_STOP		4
#define N_MIN_ROZD_STOP		3

#define N_CAK_START				3
#define N_CAK_STOP				10

#define N_MIN_ODCHYLKA		5

//-------------------Meranie priemernej spotreby za posledn˙ vzdialenosù----

#define PV_M		      		20000		//Vzdialenosù v metroch do ktorej meria priemern˙ spotrebu
#define PV_VYPOCET				10000		//Vzdialenosù v metroch od ktorej bere do ˙vahy priemern˙ spotrebu
#define PV_M_NEMERANE 		100			//Vzdialenosù od ötartu po kotr˙ nemeria priemern˙ spotrebu
#define PV_POC_MERANI 		2
//#define PV_RESET_ON_START					//Vynulovanie d·t poslednej vzdialenosti po ötarte


//------------------V˝poËet dojazdu - pomery spotrieb-----------------------

#define POMER_DOJAZD_C				60
#define POMER_DOJAZD_PV				40

//------------------Nastavenie Podsvietenia---------------------------------

#define SV_POMER_0						20
#define SV_POMER_1						20
#define SV_POMER_2						60

#define SV_MAX								1.01
#define SV_MIN								0.99



//---------------------------Obr·zky v I2C EE----------------------------

#define LOGO_CZ_S		0
#define LOGO_CZ_X		168
#define LOGO_CZ_Y		33

#define KAVA_S  	693
#define KAVA_X  	24
#define KAVA_Y  	21

#define OLEJ_S  	756
#define OLEJ_X  	40
#define OLEJ_Y  	11

#define VLOCKA_S  811
#define VLOCKA_X  40
#define VLOCKA_Y  33

#define NADRZ_S		976
#define	BATERKA_S	1024
#define HODINY_S	1072
#define TEPLOTA_S	1120
#define PRIEMER_S	1168
#define VLOC_M_S	2083

#define IKONA_X		16
#define IKONA_Y		24

#define T_OLEJ_S  1216
#define T_OLEJ_X  40
#define T_OLEJ_Y  17

#define LOGO_CONCEPT_S		1301
#define LOGO_CONCEPT_X		136
#define LOGO_CONCEPT_Y		46

#define LOGO_VA_S		2131
#define LOGO_VA_X		144
#define LOGO_VA_Y		44




//---------Rozloûenie d·t v eeprom rev.03-----------------------------
//-------------------------------HW nastavenia----------------------------------

#define EE_HW_DATA_START		0			//zaciatok d·t								(char)

#define EE_VHWMA						0			//Verzia HW	major							(char)
#define EE_VHWMI						1			//Verzia HW minor							(char)
#define EE_VEE							2			//Verzia eeprom								(char)
#define EE_SN								3			//Serial nr.									(int)
#define EE_NICK							5			//Nick												(10B)
//-----------------------------korekcia merania napatia----------------
#define EE_ODB							15		//Odp.deliË nap‰tia batÈrie		(float)
//#define EE_ND								19		//Nap‰tie diÛdy								(char)
//-----------------------------korekcia merania napatia podsvietenia---
#define EE_KBL							19		//Odp.deliË podsvietenia			(float)
//-----------------------------korekcia vonkajöej teploty--------------
#define EE_KVT							23		//Hodnota Odporu deliËa				(unint)
//#define EE_KVT_1						22		//Hodnota pri 25∞C						(unint)
//-----------------------------korekcia pre vstup 1--------------------
#define EE_KV1							30		//pr˙d merania								(float)
//#define EE_KV1_1						34		//linearita									(float)
//#define EE_KV1_2						38		//hodnota AD pri -30∞C			(int)
//-----------------------------korekcia pre vstup 2--------------------
#define EE_KV2							40		//pr˙d merania								(float)
//#define EE_KV2_1						44		//linearita									(float)
//#define EE_KV2_2						48		//hodnota AD pri -30∞C			(int)
//-----------------------------korekcia pre vstup 3--------------------
#define EE_KV3							50		//Odp.deliË										(float)
//#define EE_KV3_1						54		//													(float)
//#define EE_KV3_2						58		//													(int)
//-----------------------------korekcia merania paliva-----------------
#define EE_KP								60		//Odp.deliË										(float)
#define EE_KVP_1  					64		//offset  										(int)
#define EE_KVP_2  					66		//offset  										(int)
#define EE_DN								70		//Data n·drûe		(rezerv·cia)	(140B)
//-----------------voln· pamaù pre HW od 210 do chceck sumu------------


#define EE_HW_CHECKSUM			249		//checksum hw nastavenÌ				(char)


//-----------------------------Nastavenie BC-----------------------------------

#define EE_BC_DATA_START		EE_HW_CHECKSUM+1		//zaciatok d·t	(char)

#define EE_OFFSET_X					250		//Offset n·klonu v osy X			(char)
#define EE_OFFSET_Y					251		//Offset n·klonu v osy Y			(char)
#define EE_KOLESA						252		//Obvod kolesa								(int)
#define EE_ABS							254		//PoËet imp. na ot·Ëku kolesa	(char)
#define EE_VALCE						255		//PoËet v·lcov								(char)
#define EE_VSTREK						256		//VstrekovaË									(int)
#define EE_SIRKA_KOLESA			258		//äÌrka kolesa								(char)
#define EE_PROFIL_KOLESA		259		//Profil kolesa								(char)
#define EE_PRIEMER_KOLESA		260		//Priemer kolesa							(char)
#define EE_CENA							261		//Cena za liter paliva				(int
#define EE_SERVIS						263		//Servisn˝ interval						(int)
#define EE_SERVIS_KM				265		//km od posl. servisu					(long)
#define EE_SV_NAP_VAL				269		//Nastavenie podsvietenia			(3xint)
#define EE_CENAU						276		//Uni cena za liter paliva		(long)

//-----------------voln· pamaù pre BC od 281 do chceck sumu------------


#define EE_BC_CHECKSUM			349		//checksum BC nastavenÌ				(char)


//-------------------------------Data jazdy------------------------------------

#define EE_DJ_DATA_START		EE_BC_CHECKSUM+1		//zaciatok d·t	(char)


#define EE_VELKOST_DAT			14		//PoËet B*5 KM+SPOT_PALIVO+MAX_SPD+DOBA_JAZDY 

#define EE_TCNT1						350		//TCNT												(int)
#define EE_KM								352		//KM													(long)
#define EE_SPOT_PALIVO			356		//SpotrebovanÈ palivo					(long)
#define EE_MAX_SPD					360		//Maxim·lna r˝chlosù					(int)
#define EE_DOBA_JAZDY				362		//Doba jazdy									(long)



#define EE_VELKOST_DAT_SS		13		//PoËet B*3 funkcia start/stop (SS) 

#define EE_KM_SS						437		//KM START/STOP								(long)
#define EE_SPOT_PALIVO_SS	 	441		//SpotrebovanÈ p. START/STOP	(long)
#define EE_DOBA_JAZDY_SS		445		//Doba jazdy START/STOP				(long)
#define EE_STATUS_SS				449		//Status START/STOP						(char)



#define EE_MAX_PRETAZENIE_Y 476		//														(char)
#define EE_MAX_PRETAZENIE_X 477		//														(char)
#define EE_MAX_ZRYCHLENIE		478		//														(char)
#define EE_MIN_SPOTREBA_1		479		//1. Minim·lna spotreba				(char)
#define EE_MIN_SPOTREBA_2		480		//2. Minim·lna spotreba				(char)
#define EE_MIN_SPOTREBA_3		481		//3. Minim·lna spotreba				(char)
#define EE_MAX_DOJAZD				482		//														(int)

//-----------------voln· pamaù pre BC od 482 do chceck sumu--------

#define EE_DJ_CHECKSUM			500		//checksum D·t jazdy 					(char)


#define EE_DN1							501		//Data n·drûe orig						(140B)
#define EE_DN2							641		//Data n·drûe LCD orig				(140B)


//#endif
