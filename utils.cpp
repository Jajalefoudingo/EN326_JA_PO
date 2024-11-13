#include "utils.h"

//fonction ecriture de la temperature
void Print_temp_I2C (I2C *i2c, int addr8bit, char reg_addr, char *temp_data){
    i2c->write(addr8bit, &reg_addr, 1);

    i2c->read(addr8bit, temp_data, 2);

    int16_t temp_raw = (temp_data[0] << 8) | temp_data[1]; //Concatenation
    int temperature_C = temp_raw / 128;  // conversion

    printf("Temperature = %d C\n", temperature_C);
    
    ThisThread::sleep_for(500ms);
}

//fonction ecriture de l'humidité
void Print_humid_I2C (I2C *i2c, int addr8bit, char reg_addr, char *humid_data){
    i2c->write(addr8bit, &reg_addr, 1);

    i2c->read(addr8bit, humid_data, 2);

    int16_t humid_raw = (humid_data[0] << 8) | humid_data[1]; // Concatenation
    int humidite = -600 + (12500 * humid_raw)/65536;  

    printf("Humidite = %d.%02d %% HR\n", humidite / 100, humidite%100); // conversion en valeur %HR
    
    ThisThread::sleep_for(500ms);
}