/*
 * LED.h
 *
 *  Created on: Feb 27, 2024
 *      Author: Rana
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_

#include "LED_cfg.h"
#include "../../LIB/STD_TYPES.h"

/****************************** Defines ******************************/
/******* states of the led *******/
#define LED_STATE_ON     1
#define LED_STATE_OFF    0

/****** types of connection of the leds ******/
#define LED_CONNECTION_REVERSE  1
#define LED_CONNECTION_FORWARD  0

/****************************** Types *******************************/
typedef struct{
	void* Port;
	u32 Pin;
	u32 Connection;
	u32 InitialState;
}led_cfg_t;

/****************************** API *******************************/
void LED_Init(void);
void LED_SetStatus(u32 led,u8 status);

#endif /* HAL_LED_H_ */
