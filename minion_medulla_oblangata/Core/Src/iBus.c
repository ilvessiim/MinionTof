/*
 * iBus.c
 *
 *  Created on: Apr 28, 2021
 *      Stolen by: kristjan
 */

#include "iBus.h"
#include "usart.h"
#include "gpio.h"
#include <stdint.h>

volatile uint8_t ibus_rx_buffer[40] = { 0 };
volatile uint8_t ibus_rx_flags = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart)
{
  // In this example, we use huart2 for iBus. Since this complete callback function
  // is shared between the all of the huarts, we first check which huart is invoking it.
  if (uart == &huart7)
  {
	  // iBus message format: 0x20 0x40 dd * 28 chk chk
	  // where the 0x20 0x40 are header bytes,
	  // dd are data bytes (28 of them, for 14 channels; each channel is 2 bytes)
	  // chk are checksum bytes.
	  // 32 bytes in total.

	  // Blog posts about reversing this protocol: https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
	  // http://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/
	  if (!ibus_rx_flags)
	  {
		if (ibus_rx_buffer[0] == 0x20)
		{
		  // have header's first byte, queue the second byte.
		  ibus_rx_flags = IBUS_HAS_2;
		  HAL_UART_Receive_IT(uart, ibus_rx_buffer + 1, 1);
		}
		else
		{
		  HAL_UART_Receive_IT(uart, ibus_rx_buffer, 1);
		}
	  }
	  else if (ibus_rx_flags == IBUS_HAS_2)
	  {
		if (ibus_rx_buffer[1] != 0x40)
		{
          // header's second byte doesn't match, reset and go back to stage 1.
		  ibus_rx_flags = 0;
		  HAL_UART_Receive_IT(uart, ibus_rx_buffer, 1);
		}
		else
		{
          // have header's second byte, queue the rest of the message (30 bytes).
		  ibus_rx_flags = IBUS_HAS_4;
		  HAL_UART_Receive_IT(uart, ibus_rx_buffer + 2, 30);
		}
	  }
	  else
	  {
        // the remainder of the message arrived, set the flag and don't listen to anything
		// else until main() has read it.
		// Raw message is in the ibus_rx_buffer variable.
		ibus_rx_flags = IBUS_HAS_MESSAGE;
	  }
  }
}

#define JOIN_TO_WORD(arr) ((*(arr)) | (*((arr) + 1) << 8))

ReceiverState_t DecodeReceiverState(uint8_t* buff)
{
  ReceiverState_t rec = { 0 };

  uint16_t ch1 = JOIN_TO_WORD(buff + 2);
  uint16_t ch2 = JOIN_TO_WORD(buff + 4);
  uint16_t ch3 = JOIN_TO_WORD(buff + 6);
  uint16_t ch4 = JOIN_TO_WORD(buff + 8);
  uint16_t ch5 = JOIN_TO_WORD(buff + 10);
  uint16_t ch6 = JOIN_TO_WORD(buff + 12);
  uint16_t ch7 = JOIN_TO_WORD(buff + 14);
  uint16_t ch8 = JOIN_TO_WORD(buff + 16);

  rec.right_horizontal = ch1;
  rec.right_vertical = ch2;
  rec.left_vertical = ch3;
  rec.left_horizontal = ch4;

  if (ch5 == REC_SW_UP)
    rec.switch_a = ReceiverSwitchUp;
  else
    rec.switch_a = ReceiverSwitchDown;

  if (ch7 == REC_SW_UP)
    rec.switch_b = ReceiverSwitchUp;
  else
    rec.switch_b = ReceiverSwitchDown;

  if (ch6 > 0 && ch6 <= 1200)
    rec.switch_c = ReceiverSwitchUp;
  else if (ch6 > 1200 && ch6 <= 1700)
    rec.switch_c = ReceiverSwitchMiddle;
  else
    rec.switch_c = ReceiverSwitchDown;

  if (ch8 == REC_SW_UP)
    rec.switch_d = ReceiverSwitchUp;
  else
    rec.switch_d = ReceiverSwitchDown;

  return rec;
}

#undef JOIN_TO_WORD

ReceiverState_t HandleReceiverMessage()
{
  // Decode the message.
  ReceiverState_t rec = DecodeReceiverState(ibus_rx_buffer);

  // Reset the RX ISR flags.
  ibus_rx_flags = 0;

  for (uint8_t i = 0; i < 40; i++)
  {
	// Zero fill the buffer.
    ibus_rx_buffer[i] = 0;
  }

  // Start receiving again.
  HAL_UART_Receive_IT(&huart7, ibus_rx_buffer, 1);

  return rec;
}

void CheckUartInterruptStatus()
{
  uint8_t uart_status = HAL_UART_GetState(&huart7);

  if (uart_status == 32)
  {
	// Weird ISR error. Reset state and try again.
	ibus_rx_flags = 0;
	HAL_UART_Receive_IT(&huart7, ibus_rx_buffer, 1);
  }
}
