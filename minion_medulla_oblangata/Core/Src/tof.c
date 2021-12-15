/*
 * tof.c
 *
 *  Created on: Dec 14, 2021
 *      Author: siim
 */

#include "tof.h"
#include "i2c.h"


#define ARDUINO_PRO_MICRO_I2C_RECEIVE_ADDRESS 0x33<<1
unsigned char ArduinoProMicroI2CData[50];

int16_t tof_t1(){
	while( HAL_I2C_Master_Receive(&hi2c1, ARDUINO_PRO_MICRO_I2C_RECEIVE_ADDRESS , ArduinoProMicroI2CData, 50, 100) != HAL_OK )
	{ }
	HAL_Delay(1000);
}
