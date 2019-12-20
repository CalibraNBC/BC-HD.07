#include "delay.h"


void delay1s(void)
{
	char tmp;
	for(tmp=100; tmp!=0;tmp--) _delay_ms(10);
}

void delay100ms(void)
{
	char tmp;
	for(tmp=10; tmp!=0;tmp--) _delay_ms(10);
}


void delay_s(unsigned char s)
{
	unsigned char a;
	for (a=0;a<s;a++) delay1s();
}
