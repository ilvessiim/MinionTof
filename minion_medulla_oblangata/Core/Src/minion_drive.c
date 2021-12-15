/*
 * minion_drive.c
 *
 *  Created on: May 5, 2021
 *      Author: kristjan
 */

#include "gpio.h"
#include <stdint.h>
#include "minion_drive.h"
#include <stdio.h>
#include <stdlib.h>

SpeedPercentages setThrottle(const uint16_t v, const uint16_t w)
{
	SpeedPercentages sp = {0};
	float lv;
	float rv;
	float k_w;
	float error = 0;
	float v_temp = (v - 1500.0)  / 5;
	float w_temp = (w - 1500.0)  / 5;
	k_w = 0.15;
	lv = (v_temp +  (k_w/(abs(v_temp/200) + 1) * w_temp));//turning coef 0.2 at high speeds 0.15 at low speeds
	rv = (v_temp -  (k_w/(abs(v_temp/200) + 1) * w_temp));

	if (lv < 0)
		{
		HAL_GPIO_WritePin(M1_dir_out_GPIO_Port, M1_dir_out_Pin, 1);
		}
	else
		{
		HAL_GPIO_WritePin(M1_dir_out_GPIO_Port, M1_dir_out_Pin, 0);
		}
	if (rv < 0)
		{
		HAL_GPIO_WritePin(M2_dir_out_GPIO_Port, M2_dir_out_Pin, 1);
		}
	else
		{
		HAL_GPIO_WritePin(M2_dir_out_GPIO_Port, M2_dir_out_Pin, 0);
		}

	lv = abs(lv);
	rv = abs(rv);

	if (rv > 100)
	{
		error = rv - 100;
		rv = 100;
		lv -= error;
	}
	if (lv > 100)
	{
		error = lv - 100;
		rv -= error;
		lv = 100;
	}
	sp.lv = (uint16_t)lv;
	sp.rv = (uint16_t)rv;
	return sp;

}
