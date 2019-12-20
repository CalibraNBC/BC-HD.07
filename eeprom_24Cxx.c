#include "i2c.h"
#include "eeprom_24Cxx.h"



void serial_eeprom_write_byte(unsigned int addres, unsigned char data)
{
	i2c_start();
	i2c_addr_w(SERIAL_EEPROM_ADDRESS);
	i2c_data_w((addres>>8)&0xFF);
	i2c_data_w(addres&0xFF);
	i2c_data_w(data);
	i2c_stop();
}


unsigned char serial_eeprom_read_byte(unsigned int addres)
{
	unsigned char a;
	i2c_start();
	i2c_addr_w(SERIAL_EEPROM_ADDRESS);
	i2c_data_w((addres>>8)&0xFF);
	i2c_data_w(addres&0xFF);
	i2c_start();
	i2c_addr_r(0xA0);
	a=i2c_data_r();
	i2c_stop();
	return(a);
}


