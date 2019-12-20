#ifndef _I2C_INCLUDED_
#define _I2C_INCLUDED_

#define i2c_ready while(!ChckBit(TWCR,TWINT))
#define i2c_status (TWSR & 0xF8)

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_addr_w(char address);
void i2c_addr_r(char address);
void i2c_data_w(char data);
char i2c_data_r(void);
char i2c_data_rd(void);


#endif
