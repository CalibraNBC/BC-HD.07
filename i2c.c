#include "i2c.h"
#include <util/twi.h>
#include "bit_operations.h"

void i2c_init(void)
{
	ClrBit(DDRC,0);
	ClrBit(DDRC,1);
	SetBit(PORTC,0);
	SetBit(PORTC,1);
	TWSR=0;
	TWBR=10; //16Mhz=72, 4Mhz=12, 8Mhz=32
}


void i2c_start(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	i2c_ready;
}
	

void i2c_stop(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(ChckBit(TWCR,TWSTO));
}


void i2c_addr_w(char address)
{
	TWDR=address;
	TWCR=(1<<TWINT)|(1<<TWEN);
	i2c_ready;
}


void i2c_addr_r(char address)
{
	i2c_addr_w(++address);
}


void i2c_data_w(char data)
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	i2c_ready;
}

char i2c_data_r(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);
	i2c_ready;
	return TWDR;
} 

char i2c_data_rd(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	i2c_ready;
	return TWDR;
}
