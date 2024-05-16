/*
 * NVIC.c
 *
 *  Created on: Mar 9, 2024
 *      Author: Rana
 */



/******************************** Includes ************************************/

#include "NVIC.h"

/******************************** Defines ************************************/

#define NVIC_BASE_ADDRESS  0xE000E100
#define NVIC_PRIORITY_MASK   0x00
/******************************** Types ************************************/

/*Struct represent registers on NVIC*/

typedef struct{
	volatile u32 NVIC_ISE_REG[8];
	volatile u32 Reserved[24];
	volatile u32 NVIC_ICE_REG[8];
	volatile u32 Reserved2[24];
	volatile u32 NVIC_ISP_REG[8];
	volatile u32 Reserved3[24];
	volatile u32 NVIC_ICP_REG[8];
	volatile u32 Reserved4[24];
	volatile u32 NVIC_IAB_REG[8];
	volatile u32 Reserved5[56];
	volatile u32 NVIC_IP_REG[60];
	volatile u32 Reserved6[644];
	volatile u32 NVIC_STIR_REG;
}NVIC_REG;

/***************************** Variables **********************************/

/*pointer to refer to struct that represent register so I can use it to refer
 * to elements(registers) on the struct through -> operator*/

static NVIC_REG*const P_NVIC_Reg=(NVIC_REG*)NVIC_BASE_ADDRESS;

/**************************** Implementation ******************************/

NVIC_enu_Error_State NVIC_Enable(IRQ_NUM IRQ_N)
{
	NVIC_enu_Error_State NVIC_error_status=NVIC_OK;
	if(IRQ_N>_IRQ_MAX_NUM)
	{
		NVIC_error_status=NVIC_NOT_OK;
	}
	else
	{
		NVIC_error_status=NVIC_OK;
	}
	/*get the index of chosen array from 0 to 7 by divide IRQ_N over 32*/
	u8 reg_index=IRQ_N/32;
	/*get the value of bit must be set by take the IRQ_N%32 */
	P_NVIC_Reg->NVIC_ISE_REG[reg_index]|=(1<<(IRQ_N%32));
	return NVIC_error_status;
}
NVIC_enu_Error_State NVIC_Disable(IRQ_NUM IRQ_N)
{
	NVIC_enu_Error_State NVIC_error_status=NVIC_OK;
		if(IRQ_N>_IRQ_MAX_NUM)
		{
			NVIC_error_status=NVIC_NOT_OK;
		}
		else
		{
			NVIC_error_status=NVIC_OK;
		}
		/*get the index of chosen array from 0 to 7 by divide IRQ_N over 32*/
		u8 reg_index=IRQ_N/32;
		/*get the value of bit must be set by take the IRQ_N%32 */
		P_NVIC_Reg->NVIC_ICE_REG[reg_index]|=(1<<(IRQ_N%32));
		return NVIC_error_status;
}
NVIC_enu_Error_State NVIC_SetPending(IRQ_NUM IRQ_N)
{
	NVIC_enu_Error_State NVIC_error_status=NVIC_OK;
		if(IRQ_N>_IRQ_MAX_NUM)
		{
			NVIC_error_status=NVIC_NOT_OK;
		}
		else
		{
			NVIC_error_status=NVIC_OK;
		}
		/*get the index of chosen array from 0 to 7 by divide IRQ_N over 32*/
		u8 reg_index=IRQ_N/32;
		/*get the value of bit must be set by take the IRQ_N%32 */
		P_NVIC_Reg->NVIC_ISP_REG[reg_index]|=(1<<(IRQ_N%32));
		return NVIC_error_status;
}
NVIC_enu_Error_State NVIC_ClearPending(IRQ_NUM IRQ_N)
{
	NVIC_enu_Error_State NVIC_error_status=NVIC_OK;
		if(IRQ_N>_IRQ_MAX_NUM)
		{
			NVIC_error_status=NVIC_NOT_OK;
		}
		else
		{
			NVIC_error_status=NVIC_OK;
		}
		/*get the index of chosen array from 0 to 7 by divide IRQ_N over 32*/
		u8 reg_index=IRQ_N/32;
		/*get the value of bit must be set by take the IRQ_N%32 */
		P_NVIC_Reg->NVIC_ICP_REG[reg_index]|=(1<<(IRQ_N%32));
		return NVIC_error_status;
}
NVIC_enu_Error_State NVIC_GetStatus(IRQ_NUM IRQ_N,u32*Status)
{
	NVIC_enu_Error_State NVIC_error_status=NVIC_OK;
			if(IRQ_N>_IRQ_MAX_NUM)
			{
				NVIC_error_status=NVIC_NOT_OK;
			}
			else
			{
				NVIC_error_status=NVIC_OK;
			}
			/*get the index of chosen array from 0 to 7 by divide IRQ_N over 32*/
			u8 reg_index=IRQ_N/32;
			*Status=(P_NVIC_Reg->NVIC_IAB_REG[reg_index])&(1<<(IRQ_N%32));
			return NVIC_error_status;
}
NVIC_enu_Error_State NVIC_SetPriority(IRQ_NUM IRQ_N,u32 Priority)
{
	NVIC_enu_Error_State NVIC_error_status=NVIC_OK;
			if(IRQ_N>_IRQ_MAX_NUM)
			{
				NVIC_error_status=NVIC_NOT_OK;
			}
			else
			{
				NVIC_error_status=NVIC_OK;
			}
			u8 reg_index=IRQ_N/4;
			P_NVIC_Reg->NVIC_IP_REG[reg_index]|=(Priority<<(IRQ_N%4));

			u32 loc_CheckState=P_NVIC_Reg->NVIC_IP_REG[reg_index];
				loc_CheckState&=(NVIC_PRIORITY_MASK<<(IRQ_N%4));
				loc_CheckState|=(Priority<<(IRQ_N%4));
				P_NVIC_Reg->NVIC_IP_REG[reg_index]=loc_CheckState;
			return NVIC_error_status;
}
/*NVIC_enu_Error_State NVIC_GetPriority(IRQ_NUM IRQ_N,u32*Priority_Status);

NVIC_enu_Error_State NVIC_SetSubGroupNum(IRQ_NUM IRQ_N,u32 Num);*/

NVIC_enu_Error_State NVIC_SW_Interrupt(IRQ_NUM IRQ_N)
{

	NVIC_enu_Error_State NVIC_error_status=NVIC_OK;
			if(IRQ_N>_IRQ_MAX_NUM)
			{
				NVIC_error_status=NVIC_NOT_OK;
			}
			else
			{
				NVIC_error_status=NVIC_OK;
			}
			P_NVIC_Reg->NVIC_STIR_REG=IRQ_N;
			return NVIC_error_status;

}
