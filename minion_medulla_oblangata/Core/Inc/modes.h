/*
 * modes.h
 *
 *  Created on: Apr 28, 2021
 *      Author: kristjan
 */

#ifndef INC_MODES_H_
#define INC_MODES_H_
#include <stdint.h>
typedef struct
{
  // motor speeds
  uint16_t v; //linear velocity
  uint16_t w; //angular velocity
}Speeds;

Speeds automatic(uint8_t *data_buf);

#endif /* INC_MODES_H_ */
