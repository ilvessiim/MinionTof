/*
 * minion_drive.h
 *
 *  Created on: May 5, 2021
 *      Author: kristjan
 */

#ifndef INC_MINION_DRIVE_H_
#define INC_MINION_DRIVE_H_
#include <stdint.h>

typedef struct
{
  // motor speeds
  uint16_t lv; //left speed percentage
  uint16_t rv; //right speed percentage
}SpeedPercentages;

SpeedPercentages setThrottle(uint16_t v, uint16_t w);

#endif /* INC_MINION_DRIVE_H_ */
