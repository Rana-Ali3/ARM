/*
 * SWITCH_cfg.c
 *
 *  Created on: Mar 2, 2024
 *      Author: Rana
 */

#include "../../MCAL/GPIO.h"
#include "SWITCH.h"


/*Array of switches configuration
 * Array with number of element equal to last number in the enum represent switches in SWITCH_cfg.h
 * For each switch we access its:
 *
 * Port from this choice:(GPIO_POART_A,GPIO_POART_B,GPIO_POART_C,GPIO_POART_D,GPIO_POART_E)
 *
 * Pin from this choice:(GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,...,GPIO_PIN_15)
 *
 * Mode from this choice:(MODE_INPUT_FLOATING,MODE_INPUT_PULL_UP,MODE_INPUT_PULL_DOWN,MODE_OUTPUT_PUSH_PULL,MODE_OUTPUT_PUSH_PULL_PULL_UP,MODE_ANALOG
 * MODE_OUTPUT_PUSH_PULL_PULL_DOWN,MODE_OUTPUT_OPEN_DRAIN, MODE_OUTPUT_OPEN_DRAIN_PULL_UP,MODE_OUTPUT_OPEN_DRAIN_PULL_DOWN
 * MODE_ALTERNATIVE_FUNCTION_PUSH_PULL,MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_UP,MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_DOWN
 * MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN,MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_UP,MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_DOWN)
 *
 * State from this choice:(SWITCH_STATE_PRESSED,SWITCH_STATE_NOT_PRESSED)*/
 switch_cfg_t switches[_SWITCH_Num]={
		[SWITCH_1]={
				.Port=GPIO_POART_A,
				.Pin=GPIO_PIN_0,
				.Connection=MODE_INPUT_PULL_UP,
			    .State=SWITCH_STATE_NOT_PRESSED,
		},
		[SWITCH_2]={
				.Port=GPIO_POART_A,
				.Pin=GPIO_PIN_1,
				.Connection=MODE_INPUT_PULL_UP,
			    .State=SWITCH_STATE_NOT_PRESSED,
		},
		[SWITCH_3]={
				.Port=GPIO_POART_A,
				.Pin=GPIO_PIN_2,
				.Connection=MODE_INPUT_PULL_UP,
				.State=SWITCH_STATE_NOT_PRESSED,
				}

};
