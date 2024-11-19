#include "utils.h"

//fonction ecriture de la temperature
void Print_temp_I2C (I2C *i2c, int addr8bit, char reg_addr, char *temp_data){
    i2c->write(addr8bit, &reg_addr, 1);

    i2c->read(addr8bit, temp_data, 2);

    uint16_t temp_raw = ((temp_data[0] << 8) | temp_data[1]) & 0xFFFC; // Ignore les bits 0 et 1
    int temp_scaled = -4685 + (17572 * temp_raw) / 65536; // Échelle 100

    printf("Temperature = %d.%02d C\n", temp_scaled / 100, temp_scaled % 100);

    ThisThread::sleep_for(500ms);
}

//fonction ecriture de l'humidité
void Print_humid_I2C (I2C *i2c, int addr8bit, char reg_addr, char *humid_data){
    i2c->write(addr8bit, &reg_addr, 1);

    i2c->read(addr8bit, humid_data, 2);

    uint16_t humid_raw = ((humid_data[0] << 8) | humid_data[1]) & 0xFFFC; // Ignore les bits de statut
    int humid_scaled = -600 + (12500 * humid_raw) / 65536; // Échelle 100

    printf("Humidite = %d.%02d %% HR\n", humid_scaled / 100, humid_scaled % 100);
    
    ThisThread::sleep_for(500ms);
}

//fonction ecriture de la pression
void Print_pressure_I2C (I2C *i2c, int rd_addr, char reg_addr, char *pressure_data){

    i2c->read(rd_addr, pressure_data, 3);

    printf("Raw data: %02X %02X %02X\n", pressure_data[0], pressure_data[1], pressure_data[2]);

    int pressure = (pressure_data[0] << 16) | (pressure_data[1] << 8) | (pressure_data[2]);

    printf("pression = %d\n", pressure);
    
    ThisThread::sleep_for(500ms);
}