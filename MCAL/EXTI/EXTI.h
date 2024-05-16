/*
 * EXTI.h
 *
 *  Created on: May 9, 2024
 *      Author: Rana
 */

#ifndef MCAL_EXTI_EXTI_H_
#define MCAL_EXTI_EXTI_H_

#include "../../LIB/STD_TYPES.h"
#include "EXTI_CFG.h"


//void MEXTI_voidInit(u8 copy_u8Line,u8 copy_u8Mode);
void MEXTI_voidInit();
void MEXTI_voidEnableEXTI(u8 copy_u8Line);
void MEXTI_voidDisableEXTI(u8 copy_u8Line);
void MEXTI_voidSwTrigger(u8 copy_u8Line);
void MEXTI_voidSetSignalLatch(u8 copy_u8Line,u8 copy_u8Mode);
void MEXTI_voidSetCallBack_EXTI0(void (*ptr)(void));
void MEXTI_voidSetCallBack_EXTI1(void (*ptr)(void));
void MEXTI_voidSetCallBack_EXTI2(void (*ptr)(void));

/******************/
void MAFIO_voidSetEXTIConfig(u8 copy_u8Line,u8 copy_u8PortMap);
#endif /* MCAL_EXTI_EXTI_H_ */
