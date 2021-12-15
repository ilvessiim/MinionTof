/*
 * modes.c
 *
 *  Created on: Apr 28, 2021
 *      Author: kristjan
 */

#include "modes.h"



Speeds automatic(uint8_t *data_buf)//takes serial buffer as argument
{

	Speeds speeds = {0};

	if (data_buf[0] == 'A' && data_buf[1] == 'A')
	{
		speeds.v = ((int)(*(data_buf+2)) - '0')*1000 + ((int)(*(data_buf+3)) - '0') * 100 +  ((int)(*(data_buf+4)) - '0') * 10 + (int)(*(data_buf+5)) - '0';
		speeds.w = ((int)(*(data_buf+6)) - '0')*1000 + ((int)(*(data_buf+7)) - '0') * 100 +  ((int)(*(data_buf+8)) - '0') * 10 + (int)(*(data_buf+9)) - '0';
	}
	else
	{
		speeds.v = 1500;
		speeds.w =1500;
	}
	return speeds;
}


