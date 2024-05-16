/*
 * SYSTICK.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Rana
 */

/******************************** Includes ************************************/
#include "SYSTICK.h"

/******************************** Defines ************************************/

#define SYSTICK_BASE_ADDRESS  0xE000E010

#define SYSTICK_CLK_VALUE	16000000UL

#define SYSTICK_ENABLE_MASK   0X00000001

#define SYSTICK_MAX_LOAD    0X00FFFFFF
/******************************** Types ************************************/

/*Struct represent registers on SYSTICK*/
typedef struct{
	volatile u32 STK_CTRL_REG;
	volatile u32 STK_LOAD_REG;
	volatile u32 STK_VAL_REG;
	volatile u32 STK_CALIB_REG;
}SYSTICK_REG;

/***************************** Variables **********************************/

/*pointer to refer to struct that represent register so I can use it to refer
 * to elements(registers) on the struct through -> operator*/

static SYSTICK_REG*const P_SYSTICK_Reg=(SYSTICK_REG*)SYSTICK_BASE_ADDRESS;

static systick_cbf_t APP_cbf;

/**************************** Implementation ******************************/

SYSTICK_enu_Error_State SYSTICK_start(u32 SYSTICK_Clk)
{
	SYSTICK_enu_Error_State SystickErrorStatus=SYSTICK_OK;
	if((SYSTICK_Clk!=CLK_SOURCE_AHB)&&(SYSTICK_Clk!=CLK_SOURCE_AHB_OVER8))
	{
		SystickErrorStatus=SYSTICK_NOT_OK;
	}
	else
	{
		SystickErrorStatus=SYSTICK_OK;

			u32 loc_CheckState=P_SYSTICK_Reg->STK_CTRL_REG;
				loc_CheckState&=~CLK_SOURCE_AHB;
				loc_CheckState|=SYSTICK_Clk;
				P_SYSTICK_Reg->STK_CTRL_REG=loc_CheckState;


	P_SYSTICK_Reg->STK_CTRL_REG|=SYSTICK_ENABLE_MASK;
	}
	return SystickErrorStatus;
}
SYSTICK_enu_Error_State SYSTICK_setTimeMS(u32 SYSTICK_ticks)
{
	SYSTICK_enu_Error_State SystickErrorStatus=SYSTICK_OK;
	u32 SYSTICK_LoadValue=(((SYSTICK_ticks*SYSTICK_CLK_VALUE)/1000)-1);
	if((SYSTICK_LoadValue<1)||(SYSTICK_LoadValue>SYSTICK_MAX_LOAD))
	{
		SystickErrorStatus=SYSTICK_NOT_OK;
	}
	else
	{
		SystickErrorStatus=SYSTICK_OK;
		P_SYSTICK_Reg->STK_LOAD_REG=SYSTICK_LoadValue;
	}

	return SystickErrorStatus;
}
SYSTICK_enu_Error_State SYSTICK_Stop()
{
	SYSTICK_enu_Error_State SystickErrorStatus=SYSTICK_OK;
	P_SYSTICK_Reg->STK_CTRL_REG&=(~SYSTICK_ENABLE_MASK);
	return SystickErrorStatus;
}
void Set_Callback(systick_cbf_t cbf)
{
	if(cbf){
		APP_cbf=cbf;
	}
}

void SYSTICK_Handler(void)
{
	if(APP_cbf){
		APP_cbf();
	}
}
