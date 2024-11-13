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

Ticker flipper;
Timer t;
int sig_timer = 0;


void button_rise_handle();
void button_fall_handle();
void flip();

//// PARTIE 2 TP : Led - Bouton ////

// int main()
// {
//     InterruptIn button(BUTTON1);
//     button.rise(&button_rise_handle);
//     button.fall(&button_fall_handle);

//     led = 1;
//     float led_rate = 1.0;
//     flipper.attach(&flip, led_rate);

//     while (true) {
//         ThisThread::sleep_for(BLINKING_RATE);
//         if(sig_timer) {
//             printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
//             t.reset();
//             sig_timer = 0;

//             led_rate += 0.5;                    // Lorsque le bouton se relache on réduit la fréquence
//             flipper.attach(&flip, led_rate);    // On repasse ici la nouvelle frequence
//         }
//     }
// }

// void button_rise_handle() {
//     t.start();
//     //led = 1;
// }

// void button_fall_handle() {
//     t.stop();
//     //led = 0;
//     sig_timer = 1;
// }

// void flip()
// {
//     led = !led;
// }

//// PARTIE 3 : Com I2C ////

const int addr7bit = 0x48;      
const int addr8bit = 0x48 << 1;

int main() {
    I2C i2c(P1_I2C_SDA, P1_I2C_SCL);
    char reg_addr = 0x00;       
    char temp_data[2] = {0};  

    while (1) {
        i2c.write(addr8bit, &reg_addr, 1);

        i2c.read(addr8bit, temp_data, 2);

        int16_t temp_raw = (temp_data[0] << 8) | temp_data[1];
        int temperature_C = temp_raw / 128;  

        printf("Temperature = %d C\n", temperature_C);

        ThisThread::sleep_for(500ms);
    }
}