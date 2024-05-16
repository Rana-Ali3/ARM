/*
 * NVIC.h
 *
 *  Created on: Mar 9, 2024
 *      Author: Rana
 */

#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_

#include "../../LIB/STD_TYPES.h"
#include "Interrupt_Num.h"

/****************************** Defines ******************************/



/****************************** Types *******************************/

/************* enum to represent error ************************/
typedef enum{
	NVIC_NOT_OK,
	NVIC_OK
}NVIC_enu_Error_State;


/****************************** API *******************************/
NVIC_enu_Error_State NVIC_Enable(IRQ_NUM IRQ_N);
NVIC_enu_Error_State NVIC_Disable(IRQ_NUM IRQ_N);
NVIC_enu_Error_State NVIC_SetPending(IRQ_NUM IRQ_N);
NVIC_enu_Error_State NVIC_ClearPending(IRQ_NUM IRQ_N);
NVIC_enu_Error_State NVIC_GetPendingIRQ(IRQ_NUM IRQ_N,u32*Pinding_Status);
NVIC_enu_Error_State NVIC_SetPriority(IRQ_NUM IRQ_N,u32 Priority);
NVIC_enu_Error_State NVIC_GetPriority(IRQ_NUM IRQ_N,u32*Priority_Status);
NVIC_enu_Error_State NVIC_GetStatus(IRQ_NUM IRQ_N,u32*Status);
NVIC_enu_Error_State NVIC_SetSubGroupNum(IRQ_NUM IRQ_N,u32 Num);
//NVIC_enu_Error_State NVIC_SetPriorityGrouping();
NVIC_enu_Error_State NVIC_SW_Interrupt(IRQ_NUM IRQ_N);
#endif /* MCAL_NVIC_NVIC_H_ */
