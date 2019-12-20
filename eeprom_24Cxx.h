#ifndef _eeprom_24Cxx_
#define _eeprom_24Cxx_

void serial_eeprom_write_byte(unsigned int addres, unsigned char data);
unsigned char serial_eeprom_read_byte(unsigned int addres);

#define SERIAL_EEPROM_ADDRESS 0xA0

#endif
