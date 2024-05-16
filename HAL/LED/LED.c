/*
 * LED.c
 *
 *  Created on: Feb 27, 2024
 *      Author: Rana
 */

#include "LED.h"
#include "../../MCAL/GPIO.h"

extern const led_cfg_t leds[_Led_Num];

#define INITIL_ON_STATE_MASK

void LED_Init(void)
{
	GPIO_PIN_PARAM led;
	led.mode=MODE_OUTPUT_PUSH_PULL;
	led.speed=GPIO_HIGH_SPEED;

	for (u32 i;i<_Led_Num;i++)
	{
		led.pin=leds[i].Pin;
		led.port=leds[i].Port;
		GPIO_init(&led);
		GPIO_SetPinValue(leds[i].Port,leds[i].Pin,leds[i].Connection^leds[i].InitialState);
	}
}
void LED_SetStatus(u32 led,u8 status)
{
	//leds[led].InitialState=status;
	GPIO_SetPinValue(leds[led].Port,leds[led].Pin,leds[led].Connection^status);
}
