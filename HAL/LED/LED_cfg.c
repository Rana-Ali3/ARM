/*
 * LED_cfg.c
 *
 *  Created on: Feb 27, 2024
 *      Author: Rana
 */

#include "../../MCAL/GPIO.h"
#include "LED.h"

const led_cfg_t leds[_Led_Num]={
		[Led_Red]={
				.Port=GPIO_POART_A,
				.Pin=GPIO_PIN_0,
				.Connection=LED_CONNECTION_FORWARD,
			    .InitialState=LED_STATE_OFF,
		},
		[Led_Green]={
				.Port=GPIO_POART_B,
				.Pin=GPIO_PIN_5,
				.Connection=LED_CONNECTION_FORWARD,
			    .InitialState=LED_STATE_OFF,
		},
		[Led_Yellow]={
				.Port=GPIO_POART_A,
				.Pin=GPIO_PIN_2,
				.Connection=LED_CONNECTION_FORWARD,
				.InitialState=LED_STATE_OFF,
				}

};
//5399(3,8)514118353 78
