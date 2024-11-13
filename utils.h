#ifndef UTILS_H
#define UTILS_H

#include <mbed.h>

void Print_temp_I2C (I2C *i2c, int addr8bit, char reg_addr, char *temp_data);

#endif // UTILS_H
