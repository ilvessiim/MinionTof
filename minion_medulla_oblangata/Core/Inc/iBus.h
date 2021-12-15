/*
 * iBus.h
 *
 *  Created on: Apr 28, 2021
 *      Author: kristjan
 */

#ifndef INC_IBUS_H_
#define INC_IBUS_H_
#include <stdint.h>
#include "usart.h"

#define REC_SW_UP 1000
#define REC_SW_DOWN 2000
#define REC_SW_MID 1500

#define IBUS_HAS_2 (1 << 0)
#define IBUS_HAS_4 (1 << 1)
#define IBUS_HAS_MESSAGE (1 << 2)

UART_HandleTypeDef huart7;

extern volatile uint8_t ibus_rx_buffer[40];
extern volatile uint8_t ibus_rx_flags;

typedef enum
{
  ReceiverSwitchUp,
  ReceiverSwitchMiddle,
  ReceiverSwitchDown
} ReceiverSwitchState_e;

typedef struct
{
  // Joystick axes.
  uint16_t right_horizontal;
  uint16_t right_vertical;
  uint16_t left_vertical;
  uint16_t left_horizontal;

  // Receiver switches.
  ReceiverSwitchState_e switch_a;
  ReceiverSwitchState_e switch_b;
  ReceiverSwitchState_e switch_c;
  ReceiverSwitchState_e switch_d;
} ReceiverState_t;

//prototypes
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart);
ReceiverState_t DecodeReceiverState(uint8_t* buff);
ReceiverState_t HandleReceiverMessage();
void CheckUartInterruptStatus();

#endif /* INC_IBUS_H_ */
