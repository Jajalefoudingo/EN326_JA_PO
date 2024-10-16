/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
//#define I2C_SDA P73
//#define I2C_SCL P75

//I2C i2c(I2C_SDA, I2C_SCL);
//const int addr7bit = 0x48;      // 7 bit I2C address
//const int addr8bit = 0x48 << 1; // 8bit I2C address, 0x90

int main()
{
    // Initialise the digital pin LED1 as an output

    gpio_t sw;
    gpio_init(&sw, BUTTON1);

#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif
    char cmd = 0;

    while (true) {
        //i2c.read(addr8bit, &cmd, 2);
        //printf ("%d\n", cmd);
        // printf("Hello\n"); Test de communication carte lors de la première compile
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);

        int sw_value = gpio_read(&sw);
        printf("Button: %d\n", sw_value);
    }
}


/*
I2C i2c(I2C_SDA, I2C_SCL);

const int addr7bit = 0x48;      // 7 bit I2C address
const int addr8bit = 0x48 << 1; // 8bit I2C address, 0x90

int main()
{
    char cmd[2];
    while (1) {
        cmd[0] = 0x01;
        cmd[1] = 0x00;
        i2c.write(addr8bit, cmd, 2);

        ThisThread::sleep_for(500);

        cmd[0] = 0x00;
        i2c.write(addr8bit, cmd, 1);
        i2c.read(addr8bit, cmd, 2);

        float tmp = (float((cmd[0] << 8) | cmd[1]) / 256.0);
        printf("Temp = %.2f\n", tmp);
    }
}
*/