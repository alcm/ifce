/**
 * @brief This file contains all implementations related to adxl345 accelerometer module.
 */
#ifndef ADXL345_H_
#define ADXL345_H_

#include <stdint.h>
#include <stdbool.h>

#include "i2c.h"

#define ADXL345_ADDRESS           0xa6  /* Device address for data read operation. */
#define ADXL345_DATA_FORMAT       0x31  /* Data format control. */
#define ADXL345_POWER_CONTROL     0x2d  /* Power-saving features control. */

#define ADXL345_DATAX0_ADDRESS    0x32  /* Base address for x-axis data register. */
#define ADXL345_DATAY0_ADDRESS    0x34  /* Base address for y-axis data register. */
#define ADXL345_DATAZ0_ADDRESS    0x36  /* Base address for z-axis data register. */

/**
 * @brief reads data from accelerometer module through SPI interface.
 *
 * @param raw_data pointer to a 3-position array that will be filled with the 3-axis
 * acceleration values.
 */
void read_from_adxl345(int16_t *raw_data);

/**
 * @brief reads the x-axis acceleration value from accelerometer module through SPI interface.
 *
 * @return x-axis acceleration value.
 */
int16_t read_x_axis(void);

/**
 * @brief reads the y-axis acceleration value from accelerometer module through SPI interface.
 *
 * @return y-axis acceleration value.
 */
int16_t read_y_axis(void);

/**
 * @brief reads the z-axis acceleration value from accelerometer module through SPI interface.
 *
 * @return z-axis acceleration value.
 */
int16_t read_z_axis(void);

/**
 * @brief converts the 3-axis acceleration values to 3-axis angles.
 * @param raw_data pointer to a 3-position that contains the x,y and z measured accelerations.
 * @param xyz_angles pointer to a 3-position array that will be filled with the angles
 * values.
 */
void get_xyz_angles(const int16_t *raw_data, float *xyz_angles);

/**
 * @brief configures the adxl345 module.
 */
void setup_adxl345(void);

#endif // ADXL345_H_
