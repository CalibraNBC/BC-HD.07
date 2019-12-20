#ifndef _delay_
#define _delay_

#include <util/delay.h>

//#define delay1s()        	for(char tmp=100; tmp!=0; tmp--){ _delay_ms(10); }
//#define delay100mS()        for(char tmp=10; tmp!=0; tmp--){ _delay_ms(10); }

void delay1s(void);
void delay100ms(void);
void delay_s(unsigned char s);


#endif
