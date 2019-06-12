#include <stddef.h>
#include <stdlib.h>

#include "adxl345.h"
#include "hardware.h"

#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))

void setup_adxl345(void)
{
  i2c_init();

  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_DATA_FORMAT);
  i2c_write(0x03); // +/- 16g range

  //power register
  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_POWER_CONTROL);
  i2c_write(0x00); //disable
  
  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_POWER_CONTROL);
  i2c_write(0x16); //stand by
  
  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_POWER_CONTROL);
  i2c_write(0x08); //enable

  _delay_ms(20);
  i2c_stop();
}

void read_from_adxl345(int16_t * raw_data) 
{
  int i = 0;

  if (raw_data != NULL) {
    for (; i < 100; i++) {
      raw_data[0] += read_x_axis();
      raw_data[1] += read_y_axis();
      raw_data[2] += read_z_axis();
    }
  
    raw_data[0] /= 100;
    raw_data[1] /= 100;
    raw_data[2] /= 100;  
  }
}

int16_t read_x_axis(void)
{
  int16_t raw_x = 0;
  	
  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_DATAX0_ADDRESS);
  i2c_rep_start(ADXL345_ADDRESS | I2C_READ);

  raw_x = i2c_readNak();

  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_DATAX0_ADDRESS + 1);
  i2c_rep_start(ADXL345_ADDRESS | I2C_READ);

  raw_x += (i2c_readNak() << 8);
	
  i2c_stop();

  return raw_x;
}

int16_t read_y_axis(void)
{
  int16_t raw_y = 0;
  
  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_DATAY0_ADDRESS);
  i2c_rep_start(ADXL345_ADDRESS | I2C_READ);
	
  raw_y = i2c_readNak();
	
  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_DATAY0_ADDRESS + 1);
  i2c_rep_start(ADXL345_ADDRESS | I2C_READ);
	
  raw_y += (i2c_readNak() << 8);
  i2c_stop();

  return raw_y;
}

int16_t read_z_axis(void)
{
  int16_t raw_z = 0;
  
  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_DATAZ0_ADDRESS);
  i2c_rep_start(ADXL345_ADDRESS | I2C_READ);

  raw_z = i2c_readNak();

  i2c_rep_start(ADXL345_ADDRESS | I2C_WRITE);
  i2c_write(ADXL345_DATAZ0_ADDRESS + 1);
  i2c_rep_start(ADXL345_ADDRESS | I2C_READ);

  raw_z += (i2c_readNak() << 8);	
  i2c_stop();
	
  return raw_z;
}

void get_xyz_angles(const int16_t * raw_data, float * xyz_angles)
{
  float x_acc = 0.0, y_acc = 0.0, z_acc = 0.0, module = 0.0;
  
  /* get the x-axis, y-axis and z-axis acceleration in function of g */
  x_acc = ((float)raw_data[0]/32); // TODO: check the maximum output value returned by sensor 
  y_acc = ((float)raw_data[1]/32); // TODO: check the maximum output value returned by sensor
  z_acc = ((float)raw_data[2]/32); // TODO: check the maximum output value returned by sensor
  
  x_acc = (x_acc < 0)?MAX(x_acc, -1):MIN(x_acc, 1);
  y_acc = (y_acc < 0)?MAX(y_acc, -1):MIN(y_acc, 1);
  z_acc = (z_acc < 0)?MAX(z_acc, -1):MIN(z_acc, 1);
  
  /* get the x, y and z angles */
  module = sqrt(pow(x_acc, 2) + pow(y_acc, 2) + pow(z_acc, 2));
  xyz_angles[0] = acos(x_acc/module)*(180.0/3.1415);
  xyz_angles[1] = acos(y_acc/module)*(180.0/3.1415);
  xyz_angles[2] = acos(z_acc/module)*(180.0/3.1415);

  /* get the x, y and z accelerations */
  //xyz_data[0] = x_acc;
  //xyz_data[1] = y_acc;
  //xyz_data[2] = z_acc;
}
