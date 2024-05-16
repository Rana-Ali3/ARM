/*
 * SWITCH.h
 *
 *  Created on: Mar 2, 2024
 *      Author: Rana
 */

#ifndef HAL_SWITCH_SWITCH_H_
#define HAL_SWITCH_SWITCH_H_

#include "SWITCH_cfg.h"
#include "../../LIB/STD_TYPES.h"


/****************************** Defines ******************************/
/******* states of the switch *******/
#define SWITCH_STATE_PRESSED        0
#define SWITCH_STATE_NOT_PRESSED    1

/****** types of connection of the switch ******/
/*
#define SWITCH_CONNECTION_PULL_UP    1
#define SWITCH_CONNECTION_PULL_DOWN  0
*/
/****************************** Types *******************************/
/*struct to represent each switch*/
typedef struct{
	void* Port;
	u32 Pin;
	u32 Connection;
	u32 State;
}switch_cfg_t;

/****************************** API *******************************/

/*function to init switches through accessing the port and pin and mode and speed of
 * each switch to a gpio pin and also accessing init value of the switch to be un pressed*/

void SWITCH_Init(void);

/*Function to get the state of the switch is it PRESSED or NOT_PRESSED
 * It take the input is element of the struct of the switch
 * and it take it by reference to return the state of the switch on State variable on the struct*/

void SWITCH_isPressed(switch_cfg_t *pressed_switch);

#endif /* HAL_SWITCH_SWITCH_H_ */
