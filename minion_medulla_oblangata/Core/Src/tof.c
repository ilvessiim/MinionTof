/*
 * tof.c
 *
 *  Created on: Dec 14, 2021
 *      Author: siim
 */

#include "tof.h"
#include "i2c.h"
#include "vl53l1_api.h"


uint8_t buff[50];  //DID
VL53L1_RangingMeasurementData_t RangingData;
VL53L1_Dev_t  vl53l1_c; // center module
VL53L1_DEV    Dev = &vl53l1_c; //DID

void tof_init(){
	Dev->I2cHandle = &hi2c1; //DID
	Dev->I2cDevAddr = 0x29;

	VL53L1_WaitDeviceBooted( Dev );
	VL53L1_DataInit( Dev );
	VL53L1_StaticInit( Dev );
	VL53L1_SetDistanceMode( Dev, VL53L1_DISTANCEMODE_LONG );
	VL53L1_SetMeasurementTimingBudgetMicroSeconds( Dev, 50000 );
	VL53L1_SetInterMeasurementPeriodMilliSeconds( Dev, 500 );
	VL53L1_StartMeasurement( Dev );
}
int16_t tof_t1(){

	VL53L1_WaitMeasurementDataReady( Dev );

	VL53L1_GetRangingMeasurementData( Dev, &RangingData );

	VL53L1_ClearInterruptAndStartMeasurement( Dev );

	return RangingData.RangeMilliMeter;
}
