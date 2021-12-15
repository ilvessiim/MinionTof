/*
 * sonar.h
 *
 *  Created on: Apr 28, 2021
 *      Author: siim
 */

#ifndef INC_SONAR_H_
#define INC_SONAR_H_

#include <stdint.h>
#include "gpio.h"
static const uint8_t Sonar_ADDR1 = 0x29;
static const uint8_t Sonar_ADDR2 = 0x72 << 1;
static const uint8_t Sonar_ADDR3 = 0x71 << 1;
static const uint8_t REG_ADDR = 0x51;
extern volatile uint32_t zero_time1;
extern volatile uint32_t zero_time2;
extern volatile uint32_t zero_time3;
int16_t sonar_s1(uint32_t range);
int16_t sonar_s2(uint32_t range);
int16_t sonar_s3(uint32_t range);

#endif /* INC_SONAR_H_ */
