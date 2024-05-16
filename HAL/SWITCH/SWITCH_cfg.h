/*
 * SWITCH_cfg.h
 *
 *  Created on: Mar 2, 2024
 *      Author: Rana
 */

#ifndef HAL_SWITCH_SWITCH_CFG_H_
#define HAL_SWITCH_SWITCH_CFG_H_

/*enum to represent the number and name of switch you want
 * add wanted switch before _SWITCH_Num as it  represent always the last switch on the enum*/
typedef enum{
	SWITCH_1,
	SWITCH_2,
	SWITCH_3,

	_SWITCH_Num
}Switches_t;

#endif /* HAL_SWITCH_SWITCH_CFG_H_ */
