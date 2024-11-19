#ifndef UTILS_H
#define UTILS_H

#include <mbed.h>

void Print_temp_I2C (I2C *i2c, int addr8bit, char reg_addr, char *temp_data);
void Print_humid_I2C (I2C *i2c, int addr8bit, char reg_addr, char *humid_data);
void Print_pressure_I2C (I2C *i2c, int rd_addr, char reg_addr, char *pressure_data);

#endif // UTILS_H
