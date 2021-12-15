/*
 * sonar.c
 *
 *  Created on: Apr 28, 2021
 *      Author: siim
 */

#include "sonar.h"
#include "i2c.h"

volatile uint32_t zero_time1 = 0;
volatile uint32_t zero_time2 = 0;
volatile uint32_t zero_time3 = 0;
int16_t sonar_s1(uint32_t range){

	HAL_StatusTypeDef ret;
	uint8_t buf[12];
	int16_t val_high;
	int16_t val_low;
	buf[0] = REG_ADDR;
	static uint8_t run_once = 0;
	if (run_once == 0)
	{
		ret = HAL_I2C_Master_Transmit(&hi2c2, Sonar_ADDR1, buf, 1, HAL_MAX_DELAY);
		run_once = 1;
	}
	if ((HAL_GetTick() - zero_time1) >= 80)
	{
		if ( ret != HAL_OK )
		{
			range = 707;
		}
		else
		{
			ret = HAL_I2C_Master_Receive(&hi2c2, Sonar_ADDR1, buf, 2, HAL_MAX_DELAY);
			if ( ret != HAL_OK )
			{
				range = 707;
			}
			else
			{
				val_high = ((int16_t)buf[0]);
				val_low = ((int16_t)buf[1]);
				range = (val_high * 256) + val_low;
			}
		}
		zero_time1 = HAL_GetTick();
		run_once = 0;
	}
	return range;
}

int16_t sonar_s2(uint32_t range){
	HAL_StatusTypeDef ret;
	uint8_t buf[12];
	int16_t val_high;
	int16_t val_low;
	buf[0] = REG_ADDR;
	//static uint32_t current_time2 = HAL_GetTick();
	static uint8_t run_once1 = 0;
	if (run_once1 == 0)
	{
		ret = HAL_I2C_Master_Transmit(&hi2c2, Sonar_ADDR2, buf, 1, HAL_MAX_DELAY);
		run_once1 = 1;
	}
	if ((HAL_GetTick() - zero_time2) >= 80)
	{
		if ( ret != HAL_OK )
		{
			range = 707;
		}
		else
		{
			ret = HAL_I2C_Master_Receive(&hi2c2, Sonar_ADDR2, buf, 2, HAL_MAX_DELAY);
			if ( ret != HAL_OK )
			{
				range = 707;
			}
			else
			{
				val_high = ((int16_t)buf[0]);
				val_low = ((int16_t)buf[1]);
				range = (val_high * 256) + val_low;
			}
		}
		zero_time2 = HAL_GetTick();
		run_once1 = 0;
	}


	return range;
}

int16_t sonar_s3(uint32_t range){
	HAL_StatusTypeDef ret;
	uint8_t buf[12];
	int16_t val_high;
	int16_t val_low;
	buf[0] = REG_ADDR;
	static uint8_t run_once2 = 0;
	if (run_once2 == 0)
	{
		ret = HAL_I2C_Master_Transmit(&hi2c2, Sonar_ADDR3, buf, 1, HAL_MAX_DELAY);
		run_once2 = 1;
	}
	if ((HAL_GetTick() - zero_time3) >= 80)
	{
		if ( ret != HAL_OK )
		{
			range = 707;
		}
		else
		{
			ret = HAL_I2C_Master_Receive(&hi2c2, Sonar_ADDR3, buf, 2, HAL_MAX_DELAY);
			if ( ret != HAL_OK )
			{
				range = 707;
			}
			else
			{
				val_high = ((int16_t)buf[0]);
				val_low = ((int16_t)buf[1]);
				range = (val_high * 256) + val_low;
			}
		}
		zero_time3 = HAL_GetTick();
		run_once2 = 0;
	}


	return range;
}
