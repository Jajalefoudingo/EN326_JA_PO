/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
// #include "mbed.h"
#include "utils.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif


#define ADDR_7_BIT 0x48
#define ADDR_8_BIT 0x48 << 1
#define REG_ADDR   0x00

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
//     float led_rate = 1.0;#include "utils.h"
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

char temp_data[2] = {0};  

int main() {
    I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

    while(1) {
        Print_temp_I2C(&i2c, ADDR_8_BIT, REG_ADDR, temp_data);
    }
}