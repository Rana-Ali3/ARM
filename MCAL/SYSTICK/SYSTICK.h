/*
 * SYSTICK.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Rana
 */

#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_

#include "../../LIB/STD_TYPES.h"

/****************************** Defines ******************************/

#define CLK_SOURCE_AHB    0X00000006
#define CLK_SOURCE_AHB_OVER8 0X00000002

/****************************** Types *******************************/
typedef(*systick_cbf_t)(void);

/************* enum to represent error ************************/
typedef enum{
	SYSTICK_NOT_OK,
	SYSTICK_OK
}SYSTICK_enu_Error_State;


/****************************** API *******************************/

/* This function is to start SYSTICk and choose its source is it AHB or AHB/8
 * it take input from this choice:
 * CLK_SOURCE_AHB
 * CLK_SOURCE_AHB_over8
 * and it return output SYSTICK_enu_Error_State is it ok or not*/

SYSTICK_enu_Error_State SYSTICK_start(u32 SYSTICK_Clk);

/* This function is to set the value of systick timer to start to count down from it
 * it take input from this choice:
 * timer wanted to count down in millisecond
 * and it return output SYSTICK_enu_Error_State is it ok or not*/

SYSTICK_enu_Error_State SYSTICK_setTimeMS(u32 SYSTICK_ticks);

/* This function is to stop the  systick timer
 * and it return output SYSTICK_enu_Error_State is it ok or not*/

SYSTICK_enu_Error_State SYSTICK_Stop();
/*
 * This function can be called by the user to assign a function to the Systick interrupt
 */
void Set_Callback(systick_cbf_t cbf);

#endif /* MCAL_SYSTICK_SYSTICK_H_ */
