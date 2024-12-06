///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// PARTIE 1 TP : Led - Bouton ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include "utils.h"


// #define BLINKING_RATE     500ms  // Blinking rate in milliseconds

// #ifdef LED1
//     DigitalOut led(LED1);
// #else
//     bool led;
// #endif

// using namespace std::chrono;

// Ticker flipper;
// Timer t;
// int sig_timer = 0;


// void button_rise_handle();
// void button_fall_handle();
// void flip();

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
// }

// void button_fall_handle() {
//     t.stop();
//     sig_timer = 1;
// }

// void flip()
// {
//     led = !led;
// }









///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// PARTIE 2 TP : Com I2C ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include "utils.h"


// #define BLINKING_RATE     500ms  // Blinking rate in milliseconds

// #ifdef LED1
//     DigitalOut led(LED1);
// #else
//     bool led;
// #endif


// #define ADDR_7_BIT_TEMP   0x48
// #define ADDR_8_BIT_TEMP   0x48 << 1
// #define REG_ADDR_TEMP     0xE3
// #define ADDR_7_BIT_HUMID  0x40
// #define ADDR_8_BIT_HUMID  0x40 << 1
// #define REG_ADDR_HUMID    0xE5
// #define ADDR_READ_PRESSURE  0x70 << 1 | 1
// #define REG_ADDR_PRESSURE    0xF7

// using namespace std::chrono;


// char temp_data[2] = {0};  
// char humid_data[2] = {0};
// char pressure_data[3] = {0};  

// int main() {
//     I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

//     while(1) {
//         Print_temp_I2C(&i2c, ADDR_8_BIT_HUMID, REG_ADDR_TEMP, temp_data);
//         Print_humid_I2C(&i2c, ADDR_8_BIT_HUMID, REG_ADDR_HUMID, humid_data);
//         // Print_pressure_I2C(&i2c, ADDR_READ_PRESSURE, REG_ADDR_PRESSURE, pressure_data);
//     }
// }




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// PARTIE 3 TP : Ping Pong ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <mbed.h>


// #define BLINKING_RATE     500ms  // Blinking rate in milliseconds

// using namespace std::chrono;

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







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// PROJET ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <stdio.h>

// #include "mbed.h"

// #include "lorawan/LoRaWANInterface.h"
// #include "lorawan/system/lorawan_data_structures.h"
// #include "events/EventQueue.h"
// #include "2SMPB02E.h"

// using namespace sixtron;

// namespace {
// #define PERIOD 1s
// }

// static DigitalOut led1(LED1);

// O2SMPB02E smp(P1_I2C_SDA, P1_I2C_SCL);

// Application helpers

// #include "lora_radio_helper.h"

// using namespace events;

// Max payload size can be LORAMAC_PHY_MAXPAYLOAD.
// This example only communicates with much shorter messages (<30 bytes).
// If longer messages are used, these buffers must be changed accordingly.
// uint8_t tx_buffer[30];
// uint8_t rx_buffer[30];

// /*
//  * Sets up an application dependent transmission timer in ms. Used only when Duty Cycling is off for testing
//  */
// #define TX_TIMER                        10000

// /**
//  * Maximum number of events for the event queue.
//  * 10 is the safe number for the stack events, however, if application
//  * also uses the queue for whatever purposes, this number should be increased.
//  */
// #define MAX_NUMBER_OF_EVENTS            10

// /**
//  * Maximum number of retries for CONFIRMED messages before giving up
//  */
// #define CONFIRMED_MSG_RETRY_COUNTER     3



// /**
//  * Dummy sensor class object
//  */
// char payload[64];

// /**
// * This event queue is the global event queue for both the
// * application and stack. To conserve memory, the stack is designed to run
// * in the same thread as the application and the application is responsible for
// * providing an event queue to the stack that will be used for ISR deferment as
// * well as application information event queuing.
// */
// static EventQueue ev_queue(MAX_NUMBER_OF_EVENTS *EVENTS_EVENT_SIZE);

// /**
//  * Event handler.
//  *
//  * This will be passed to the LoRaWAN stack to queue events for the
//  * application which in turn drive the application.
//  */
// static void lora_event_handler(lorawan_event_t event);

// /**
//  * Constructing Mbed LoRaWANInterface and passing it the radio object from lora_radio_helper.
//  */
// static LoRaWANInterface lorawan(radio);

// /**
//  * Application specific callbacks
//  */
// static lorawan_app_callbacks_t callbacks;

// /**
//  * Entry point for application
//  */
// int main(void)
// {
//     stores the status of a call to LoRaWAN protocol
//     lorawan_status_t retcode;

//     if (!smp.init()) {
//         printf("Failed to init 2SMPB02E\n");
//     } else {
//         printf("Init 2SMPB02E OK\n");
//         smp.measure_single_shot();
//         snprintf(payload, sizeof(payload), "{\"temperature\":%.2f}", smp.temperature());
//         printf("%s", payload);
//     }

//     printf("\nHello World!\n");

//     ThisThread::sleep_for(100ms);

//     Initialize LoRaWAN stack
//     if (lorawan.initialize(&ev_queue) != LORAWAN_STATUS_OK) {
//         printf("\r\n LoRa initialization failed! \r\n");
//         return -1;
//     }

//     printf("\r\n Mbed LoRaWANStack initialized \r\n");

//     prepare application callbacks
//     callbacks.events = mbed::callback(lora_event_handler);
//     lorawan.add_app_callbacks(&callbacks);

//     Set number of retries in case of CONFIRMED messages
//     if (lorawan.set_confirmed_msg_retries(CONFIRMED_MSG_RETRY_COUNTER)
//             != LORAWAN_STATUS_OK) {
//         printf("\r\n set_confirmed_msg_retries failed! \r\n\r\n");
//         return -1;
//     }

//     printf("\r\n CONFIRMED message retries : %d \r\n",
//            CONFIRMED_MSG_RETRY_COUNTER);

//     Enable adaptive data rate
//     if (lorawan.enable_adaptive_datarate() != LORAWAN_STATUS_OK) {
//         printf("\r\n enable_adaptive_datarate failed! \r\n");
//         return -1;
//     }

//     printf("\r\n Adaptive data  rate (ADR) - Enabled \r\n");

//     retcode = lorawan.connect();

//     if (retcode == LORAWAN_STATUS_OK ||
//             retcode == LORAWAN_STATUS_CONNECT_IN_PROGRESS) {
//     } else {
//         printf("\r\n Connection error, code = %d \r\n", retcode);
//         return -1;
//     }

//     printf("\r\n Connection - In Progress ...\r\n");

//     make your event queue dispatching events forever
//     ev_queue.dispatch_forever();

//     return 0;
// }

// /**
//  * Sends a message to the Network Server
//  */
// static void send_message()
// {
//     uint16_t packet_len;
//     int16_t retcode;
//     int32_t sensor_value;

//     TODO: Read sensor data
//     smp.measure_single_shot();
    
//     Temperature
//     snprintf(payload, sizeof(payload), "{\"temperature\":%.2f}", smp.temperature() / 256);
//     printf("%s", payload);
    
//     memcpy(tx_buffer, payload, strlen(payload));
//     packet_len = strlen(payload);

//     retcode = lorawan.send(MBED_CONF_LORA_APP_PORT, tx_buffer, packet_len,
//                            MSG_UNCONFIRMED_FLAG);

//     if (retcode < 0) {
//         retcode == LORAWAN_STATUS_WOULD_BLOCK ? printf("send - WOULD BLOCK\r\n")
//         : printf("\r\n send() - Error code %d \r\n", retcode);

//         if (retcode == LORAWAN_STATUS_WOULD_BLOCK) {
//             retry in 3 seconds
//             if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
//                 ev_queue.call_in(3000, send_message);
//             }
//         }
//         return;
//     }

//     printf("\r\n %d bytes scheduled for transmission \r\n", retcode);
//     memset(tx_buffer, 0, sizeof(tx_buffer));

//     Pression
//     snprintf(payload, sizeof(payload), "{\"temperature\":%.2f, \"pressure\":%.2f}", 
//          smp.temperature() / 256, smp.pressure() / 100.0);
    
//     memcpy(tx_buffer, payload, strlen(payload));
//     packet_len = strlen(payload);

//     retcode = lorawan.send(MBED_CONF_LORA_APP_PORT, tx_buffer, packet_len,
//                            MSG_UNCONFIRMED_FLAG);

//     if (retcode < 0) {
//         retcode == LORAWAN_STATUS_WOULD_BLOCK ? printf("send - WOULD BLOCK\r\n")
//         : printf("\r\n send() - Error code %d \r\n", retcode);

//         if (retcode == LORAWAN_STATUS_WOULD_BLOCK) {
//             retry in 3 seconds
//             if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
//                 ev_queue.call_in(3000, send_message);
//             }
//         }
//         return;
//     }

//     printf("\r\n %d bytes scheduled for transmission \r\n", retcode);
//     memset(tx_buffer, 0, sizeof(tx_buffer));
// }

// /**
//  * Receive a message from the Network Server
//  */
// static void receive_message()
// {
//     uint8_t port;
//     int flags;
//     int16_t retcode = lorawan.receive(rx_buffer, sizeof(rx_buffer), port, flags);

//     if (retcode < 0) {
//         printf("\r\n receive() - Error code %d \r\n", retcode);
//         return;
//     }

//     printf(" RX Data on port %u (%d bytes): ", port, retcode);
//     for (uint8_t i = 0; i < retcode; i++) {
//         printf("%02x ", rx_buffer[i]);
//     }
//     printf("\r\n");
    
//     memset(rx_buffer, 0, sizeof(rx_buffer));
// }

// /**
//  * Event handler
//  */
// static void lora_event_handler(lorawan_event_t event)
// {
//     switch (event) {
//         case CONNECTED:
//             printf("\r\n Connection - Successful \r\n");
//             if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
//                 send_message();
//             } else {
//                 ev_queue.call_every(TX_TIMER, send_message);
//             }

//             break;
//         case DISCONNECTED:
//             ev_queue.break_dispatch();
//             printf("\r\n Disconnected Successfully \r\n");
//             break;
//         case TX_DONE:
//             printf("\r\n Message Sent to Network Server \r\n");
//             if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
//                 send_message();
//             }
//             break;
//         case TX_TIMEOUT:
//         case TX_ERROR:
//         case TX_CRYPTO_ERROR:
//         case TX_SCHEDULING_ERROR:
//             printf("\r\n Transmission Error - EventCode = %d \r\n", event);
//             try again
//             if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
//                 send_message();
//             }
//             break;
//         case RX_DONE:
//             printf("\r\n Received message from Network Server \r\n");
//             receive_message();
//             break;
//         case RX_TIMEOUT:
//         case RX_ERROR:
//             printf("\r\n Error in reception - Code = %d \r\n", event);
//             break;
//         case JOIN_FAILURE:
//             printf("\r\n OTAA Failed - Check Keys \r\n");
//             break;
//         case UPLINK_REQUIRED:
//             printf("\r\n Uplink required by NS \r\n");
//             if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
//                 send_message();
//             }
//             break;
//         default:
//             MBED_ASSERT("Unknown Event");
//     }
// }



