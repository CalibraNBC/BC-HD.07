#include "settings.h"
#include "beep.h"
#include "definitions.h"
#include <util/delay.h>


void beep(unsigned char poc_opakovani, unsigned char dlz_pisk, unsigned char dlz_medz)
{
#ifdef BEEP_ON

	char a,aa;

	for (a=0;a<=poc_opakovani;a++)
	{
		BUZZER_ON;
		for (aa=0;aa<=dlz_pisk;aa++) _delay_ms(10);
		BUZZER_OFF;
		for (aa=0;aa<=dlz_medz;aa++) _delay_ms(10);
	}
 
#endif
}
