/*
 * SWITCH.c
 *
 *  Created on: Mar 2, 2024
 *      Author: Rana
 */

#include "SWITCH.h"
#include "../../MCAL/GPIO.h"

extern const switch_cfg_t switches[_SWITCH_Num];

void SWITCH_Init(void)
{
	/*make an element of the pin of the GPIO and this pin will help to pass switch onto GPIO through this pin*/
	GPIO_PIN_PARAM switch_pin;
	/*set the speed of this pin to be at high speed */
	switch_pin.speed=GPIO_HIGH_SPEED;

	/*loop on the number of switches to pass them to a actual GPIO pin */
	for (int i;i<_SWITCH_Num;i++)
	{
		/*Give the created GPIO pin above the reminder of its parameter:port,pin,mode*/

		/*Give the GPIO_pin its value through switches[i].Pin selected in SWITCH_cfg.c*/
		switch_pin.pin=switches[i].Pin;
		/*Give the GPIO_pin its port value through switches[i].Port selected in SWITCH_cfg.c*/
		switch_pin.port=switches[i].Port;
		/*Give the GPIO_pin its mode value through switches[i].Connection selected in SWITCH_cfg.c*/
		switch_pin.mode=switches[i].Connection;
		/*pass this GPIO_pin after selected its parameter to GPIO_init function to init it*/
		GPIO_init(&switch_pin);
		/*select initial state of the switch to be unpressed whether it is pull up or pull down*/
		if(switches[i].Connection==MODE_INPUT_PULL_UP)
		{
		GPIO_SetPinValue(switches[i].Port,switches[i].Pin,switches[i].State);
		}
		else if(switches[i].Connection==MODE_INPUT_PULL_DOWN)
		{
			GPIO_SetPinValue(switches[i].Port,switches[i].Pin,~(switches[i].State));
		}
	}

}

void SWITCH_isPressed(switch_cfg_t *pressed_switch)
{
	u8 var=0;
	/*Get the value of the switch you want to be stored on var variable*/

	GPIO_GetPinValue(pressed_switch->Port,pressed_switch->Pin,&var);

	/*then making xor between the value getted in var and connection of the switch is it pull up or pull down
	 * first shift pressed_switch->Connection which represent mode on gpio pin with 1 value so that
	 * Pull up become represent 0 and pull down represent 1 then making xor with the value getted from
	 * the pin */

	/*the new value getted from xor will be stored on pressed_switch->State and we pass the the switch
	 * by reference so that the value will be saved on it*/

	pressed_switch->State=var^(pressed_switch->Connection>>1);


}
