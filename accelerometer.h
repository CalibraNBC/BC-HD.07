#ifndef accelerometer_
#define accelerometer_

#define LIS3LV02DQ_ADDRESS 0x3A

#define LIS302DL_ADDRESS 0x38

void accelerometer_init(void);
void accelerometer_stby(void);
void accelerometer_read(void);
void zmeraj_pretazenie(void);

char accelerometer_z, accelerometer_x, accelerometer_y;

#endif
