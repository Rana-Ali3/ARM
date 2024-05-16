/*
 * APP1.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Rana
 */

#include "HAL/LED/LED.h"
#include "LIB/STD_TYPES.h"

#define PERIOD 1
typedef enum
{
	RED,
	YELLOW,
	GREEN
}state;
void Runnable_1(void)
{
	 state traffic_state;
	static u32 count=0;
	switch(traffic_state)
	{
	case RED:
		LED_SetStatus(Led_Red,LED_STATE_ON);
		LED_SetStatus(Led_Yellow,LED_STATE_OFF);
		LED_SetStatus(Led_Green,LED_STATE_OFF);
		if(count==5)
		{
			traffic_state=YELLOW;
			count=0;
		}
		break;
	}
}

