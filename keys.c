#include "settings.h"
#include "keys.h"
#include "variables.h"


char tlacitka(void)
{
	if TLACITKO_START		return(1);
	if TLACITKO_STOP  	return(2);
	return(0);
}


char tlacitka_long(void)
{
	unsigned long start_time;
	
	start_time=hodiny_h*3600+hodiny_m*60+hodiny_s;
	while (tlacitka()) if (start_time+2<(hodiny_h*3600+hodiny_m*60+hodiny_s)) return(1);

	return(0);
}
