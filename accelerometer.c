#include "accelerometer.h"
#include "i2c.h"
#include "variables.h"



void accelerometer_init(void)
{
#ifdef LIS302DL
//------------------SW ON---------------
	i2c_start();
	i2c_addr_w(LIS302DL_ADDRESS);
	i2c_data_w(160);
	i2c_data_w(71);
	i2c_stop();
#endif

#ifndef LIS302DL
//------------------Offset---------------
	i2c_start();
	i2c_addr_w(LIS3LV02DQ_ADDRESS);
	i2c_data_w(150);									
	i2c_data_w(20);		//Ofset	Z 
	i2c_data_w(10);		//			Y 
	i2c_data_w(20); 	//			X 							
	i2c_data_w(73);		//Gain	Z
	i2c_data_w(185);	//			Y	
	i2c_data_w(183 ); //			X	
	i2c_stop();
//------------------SW ON---------------
	i2c_start();
	i2c_addr_w(LIS3LV02DQ_ADDRESS);
	i2c_data_w(160);
	i2c_data_w(199);
	i2c_data_w(1);
	i2c_stop();
#endif
}


void accelerometer_stby(void)
{
	i2c_start();
#ifdef LIS302DL
	i2c_addr_w(LIS302DL_ADDRESS);
#endif
#ifndef LIS302DL
	i2c_addr_w(LIS3LV02DQ_ADDRESS);
#endif
	i2c_data_w(160);
	i2c_data_w(0);
	i2c_stop();
}


void accelerometer_read(void)
{

#ifndef LIS302DL
	i2c_start();
	i2c_addr_w(LIS3LV02DQ_ADDRESS);
	i2c_data_w(168);
	i2c_stop();
	i2c_start();
	i2c_addr_r(LIS3LV02DQ_ADDRESS);
	i2c_data_rd();

#ifdef HW08S65
	accelerometer_z=i2c_data_rd();
	i2c_data_rd();
	accelerometer_x=i2c_data_rd();
	i2c_data_rd();
	accelerometer_y=i2c_data_r();
	i2c_stop();
#endif

#ifdef HW09
	accelerometer_x=i2c_data_rd();
	i2c_data_rd();
	accelerometer_z=i2c_data_rd();
	i2c_data_rd();
	accelerometer_y=i2c_data_r();
	i2c_stop();
#endif
#endif

#ifdef LIS302DL
	i2c_start();
	i2c_addr_w(LIS302DL_ADDRESS);
	i2c_data_w(168);
	i2c_stop();
	i2c_start();
	i2c_addr_r(LIS302DL_ADDRESS);
	i2c_data_rd();

	accelerometer_z=i2c_data_rd();
	i2c_data_rd();
	accelerometer_x=i2c_data_rd();
	i2c_data_rd();
	accelerometer_y=i2c_data_r();
	i2c_stop();
#endif
}


void zmeraj_pretazenie(void)
{
	char tmpx, tmpy;

	accelerometer_read();
	accelerometer_x=accelerometer_x-offset_x;
	accelerometer_y=accelerometer_y-offset_y;

	tmpx=accelerometer_x;
	tmpy=accelerometer_y;

	if (tmpx<0) tmpx=256-tmpx;
	if (tmpy<0) tmpy=256-tmpy;
	
	if (tmpx>max_pretazenie_x) max_pretazenie_x=tmpx;
	if (tmpy>max_pretazenie_y) max_pretazenie_y=tmpy;
}
