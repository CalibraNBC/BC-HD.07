#ifndef accelerometer_lis3lv02dq_
#define accelerometer_lis3lv02dq_

#define LIS302DL_ADDRESS 0x38

void accelerometer_init(void);
void accelerometer_stby(void);
void accelerometer_read(void);
void zmeraj_pretazenie(void);

char accelerometer_z, accelerometer_x, accelerometer_y;

#endif
