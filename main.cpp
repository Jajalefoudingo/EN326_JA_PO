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


#define ADDR_7_BIT_TEMP   0x48
#define ADDR_8_BIT_TEMP   0x48 << 1
#define REG_ADDR_TEMP     0xE3
#define ADDR_7_BIT_HUMID  0x40
#define ADDR_8_BIT_HUMID  0x40 << 1
#define REG_ADDR_HUMID    0xE5
#define ADDR_READ_PRESSURE  0x70 << 1 | 1
#define REG_ADDR_PRESSURE    0xF7

using namespace std::chrono;

Ticker flipper;
Timer t;
int sig_timer = 0;


// void button_rise_handle();
// void button_fall_handle();
// void flip();

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

// PARTIE 3 : Com I2C ////

char temp_data[2] = {0};  
char humid_data[2] = {0};
char pressure_data[3] = {0};  

int main() {
    I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

    while(1) {
        // Print_temp_I2C(&i2c, ADDR_8_BIT_HUMID, REG_ADDR_TEMP, temp_data);
        // Print_humid_I2C(&i2c, ADDR_8_BIT_HUMID, REG_ADDR_HUMID, humid_data);
        Print_pressure_I2C(&i2c, ADDR_READ_PRESSURE, REG_ADDR_PRESSURE, pressure_data);
        // scan_I2C(&i2c);
    }
}


// PARTIE 4 : Ping Pong ////

// #define STOP_FLAG 1

// Thread thread_ping(osPriorityNormal, 1024); // Thread avec une pile de 1024
// Thread thread_pong(osPriorityNormal, 1024);

// Mutex mutex;
// int cpt = 0;

// void ping()
// {
//     while (!ThisThread::flags_wait_any_for(STOP_FLAG, 0s)) {
//         mutex.lock();
//         printf("Ping\n");
//         cpt++;
//         mutex.unlock();
//         ThisThread::sleep_for(100ms);
//     }
// }

// void pong()
// {
//     while (!ThisThread::flags_wait_any_for(STOP_FLAG, 0s)) {
//         mutex.lock();
//         printf("Pong\n");
//         cpt++;
//         mutex.unlock();
//         ThisThread::sleep_for(100ms);
//     }
// }


// int main()
// {
//     printf("Hello World\n");

//     thread_ping.start(callback(ping)); // Démarrer les threads
//     thread_pong.start(callback(pong));

//     if(cpt >= 200)
//     {
//         thread_ping.flags_set(STOP_FLAG); //arrêter les threads
//         thread_pong.flags_set(STOP_FLAG);

//     }
        

//     printf("Done\n");
//     return 0;
// }

