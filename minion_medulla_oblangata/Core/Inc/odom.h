/*
 * odom.h
 *
 *  Created on: Apr 28, 2021
 *      Author: sven
 */

#ifndef INC_ODOM_H_
#define INC_ODOM_H_

#include <stdint.h>
#include "gpio.h"

int32_t odometry_m1(long step_counter);
int32_t odometry_m2(long step_counter);

#endif /* INC_ODOM_H_ */
