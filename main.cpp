/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif


using namespace std::chrono;

Timer t;
int sig_timer = 0;

void button_rise_handle();
void button_fall_handle();

int main()
{
    InterruptIn button(BUTTON1);
    button.rise(&button_rise_handle);
    button.fall(&button_fall_handle);

    while (true) {
        ThisThread::sleep_for(BLINKING_RATE);
        if(sig_timer) {
            printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            t.reset();
            sig_timer = 0;
        }
    }
}

void button_rise_handle() {
    t.start();
    led = 1;
}

void button_fall_handle() {
    t.stop();
    led = 0;
    sig_timer = 1;
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