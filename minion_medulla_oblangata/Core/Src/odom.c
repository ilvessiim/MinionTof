/*
 * odom.c
 *
 *  Created on: Apr 28, 2021
 *      Author: sven
 */

#include "odom.h"

uint8_t HSU_Val, HSV_Val, HSW_Val;
uint8_t encoder_pos;
int8_t encoder_pos_delta = 0;
uint8_t encoder_pos_sum = 0;
int8_t dir = 0;
int8_t motor_flip_m1 = 1;  // if dir does not match
int8_t motor_flip_m2 = 1;


int32_t odometry_m1(int32_t step_counter){
	static uint8_t encoder_pos_previous_m1 = 0;

	//Read 3 hall sensors
	HSU_Val = HAL_GPIO_ReadPin(ODO1_U_GPIO_Port, ODO1_U_Pin);
	HSV_Val = HAL_GPIO_ReadPin(ODO1_V_GPIO_Port, ODO1_V_Pin);
	HSW_Val = HAL_GPIO_ReadPin(ODO1_W_GPIO_Port, ODO1_W_Pin);
	encoder_pos = 4 * HSU_Val + 2 * HSV_Val + 1 * HSW_Val;

	encoder_pos_delta = encoder_pos - encoder_pos_previous_m1;
	encoder_pos_sum = encoder_pos + encoder_pos_previous_m1;

	if (encoder_pos_delta != 0){
		// Find motor direction
		if (encoder_pos_delta > 0){
			if (encoder_pos_sum == 8 || encoder_pos_sum == 4 || encoder_pos_sum == 9){
				dir = 1;
			}
			else {
				dir = -1;
			}
		}
		else{
			if (encoder_pos_sum == 8 || encoder_pos_sum == 4 || encoder_pos_sum == 9){
				dir = -1;
			}
			else {
				dir = 1;
			}
		}
		encoder_pos_previous_m1 = encoder_pos;
		step_counter += dir * motor_flip_m1;
	}
	return step_counter;
}


int32_t odometry_m2(int32_t step_counter){
	static uint8_t encoder_pos_previous_m2 = 0;

	//Read 3 hall sensors
	HSU_Val = HAL_GPIO_ReadPin(ODO2_U_GPIO_Port, ODO2_U_Pin);
	HSV_Val = HAL_GPIO_ReadPin(ODO2_V_GPIO_Port, ODO2_V_Pin);
	HSW_Val = HAL_GPIO_ReadPin(ODO2_W_GPIO_Port, ODO2_W_Pin);
	encoder_pos = 4 * HSU_Val + 2 * HSV_Val + 1 * HSW_Val;

	encoder_pos_delta = encoder_pos - encoder_pos_previous_m2;
	encoder_pos_sum = encoder_pos + encoder_pos_previous_m2;

	if (encoder_pos_delta != 0){
		// Find motor direction
		if (encoder_pos_delta > 0){
			if (encoder_pos_sum == 8 || encoder_pos_sum == 4 || encoder_pos_sum == 9){
				dir = 1;
			}
			else {
				dir = -1;
			}
		}
		else{
			if (encoder_pos_sum == 8 || encoder_pos_sum == 4 || encoder_pos_sum == 9){
				dir = -1;
			}
			else {
				dir = 1;
			}
		}
		encoder_pos_previous_m2 = encoder_pos;
		step_counter += dir * motor_flip_m2;
	}
	return step_counter;
}
