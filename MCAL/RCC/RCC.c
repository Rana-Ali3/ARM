/*
 * RCC.c
 *
 *  Created on: Feb 13, 2024
 *      Author: Rana
 */

/******************************** Includes ************************************/

#include"RCC.h"

/******************************** Defines ************************************/

/*Base address of RCC */

#define RCC_BASE_ADDRESS       0x40023800
/*=================================================================================*/
/*Masks to check on the bits of ready of the HSI,HSE,PLL*/

#define HSI_READY_MASK         0x00000002
#define HSE_READY_MASK         0x00020000
#define PLL_READY_MASK         0x02000000
/*==================================================================================*/
/*Masks to check on the bits that represent state of (HSI,HSE,PLL) that
 *is set by hardware when one of these clocks is selected as system clock*/

#define SYS_CLK_STATE_HSI_MASK 0x00000000
#define SYS_CLK_STATE_HSE_MASK 0x00000004
#define SYS_CLK_STATE_PLL_MASK 0x00000008
/*===================================================================================*/
/*This is mask to set bits that represent state of (HSI,HSE,PLL)
 * whether it is selected by hardware as system clock or not
 * (mask for set this bit only on the register) */

#define SYS_CLK_STATE_MASK        0X0000000C

/*This is mask to set bits that represent selected clock from (HSI,HSE,PLL)
 * this is selected by software as system clock
 * (mask for set this bit only on the register) */

#define SYS_CLK_SELECTED_MASK     0X00000003
/*====================================================================================*/
/*Mask to set bits that represent Q only on the register
 * (mask for set this bit only on the register)*/

#define PLL_Q_BITS_MASK         0x0F000000

/*Mask to set bits that represent P only on the register
 * (mask for set this bit only on the register)*/

#define PLL_P_BITS_MASK         0x00030000

/*Mask to set bits that represent N only on the register
 * (mask for set this bit only on the register)*/

#define PLL_N_BITS_MASK         0x00007FC0

/*Mask to set bits that represent M only on the register
 * (mask for set this bit only on the register)*/

#define PLL_M_BITS_MASK         0x0000003F

/*=================================================================================*/

/*Mask to set bits that represent pre_scaler on AHB bus  represent
 * (mask for set this bit only on the register)*/

#define AHB_PRESCALER_MASK       0x000000F0

/*Mask to set bits that represent pre_scaler on APB1 bus  represent
 * (mask for set this bit only on the register)*/

#define APB1_PRESCALER_MASK      0x00001C00

/*Mask to set bits that represent pre_scaler on APB2 bus  represent
 * (mask for set this bit only on the register)*/

#define APB2_PRESCALER_MASK      0x0000E000

/******************************** Types ************************************/

/*Struct represent registers on RCC*/
typedef struct
{
	volatile u32 RCC_CR_REG;
	volatile u32 RCC_PLLCFGR_REG;
	volatile u32 RCC_CFGR_REG;
	volatile u32 RCC_CIR_REG;
	volatile u32 RCC_AHB1RSTR_REG;
	volatile u32 RCC_AHB2RSTR_REG;
	volatile u32 RESERVED;//To represent reserved register
	volatile u32 RESERVED2;
	volatile u32 RCC_APB1RSTR_REG;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RESERVED3;
	volatile u32 RESERVED4;
	volatile u32 RCC_AHB1ENR_REG;
	volatile u32 RCC_AHB2ENR_REG;
	volatile u32 RESERVED5;
	volatile u32 RESERVED6;
	volatile u32 RCC_APB1ENR_REG;
	volatile u32 RCC_APB2ENR_REG;
	volatile u32 RESERVED7;
	volatile u32 RESERVED8;
	volatile u32 RCC_AHB1LPENR_REG;
	volatile u32 RCC_AHB2LPENR_REG;
	volatile u32 RESERVED9;
	volatile u32 RESERVED10;
	volatile u32 RCC_APB1LPENR_REG;
	volatile u32 RCC_APB2LPENR_REG;
	volatile u32 RESERVED11;
	volatile u32 RESERVED12;
	volatile u32 RCC_BDCR_REG;
	volatile u32 RCC_CSR_REG;
	volatile u32 RESERVED13;
	volatile u32 RESERVED14;
	volatile u32 RCC_SSCGR_REG;
	volatile u32 RCC_PLLI2SCFGR_REG;
	volatile u32 RCC_DCKCFGR_REG;
}RCC_REG;

/***************************** Variables **********************************/

/*pointer to refer to struct that represent register so I can use it to refer
 * to elements(registers) on the struct through -> operator*/

static RCC_REG*const P_RCC_Register=(RCC_REG*)RCC_BASE_ADDRESS;

/**************************** Implementation ******************************/
RCC_enu_Error_State  RCC_ControlClk(u32 Copy_ClockSystem,u8 Copy_ClkStatus)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;
	u32 loc_TimeOut=600;

	/*check that input parameters is one of the right choice(SYS_CLK_HSI,SYS_CLK_HSE,SYS_CLK_PLL)*/

	if((Copy_ClockSystem!=SYS_CLK_HSE)&&(Copy_ClockSystem!=SYS_CLK_HSI)&&(Copy_ClockSystem!=SYS_CLK_PLL))
	{
		Ret_enuSystemCLOCK = SYS_CLK_NOT_OK;
	}
	else
	{
		Ret_enuSystemCLOCK = SYS_CLK_OK;
	}


	switch(Copy_ClockSystem)
	{
	   case SYS_CLK_HSI:
		   /*if((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)!=SYS_CLK_STATE_HSI_MASK)
		   {
			   Ret_enuSystemCLOCK=SYS_CLK_ERROR_WRONG_STATE;
		   }
		   else
		   {*/
			   Ret_enuSystemCLOCK = SYS_CLK_OK;

		   switch(Copy_ClkStatus)
		   {
		   case ON_STATE:

			   /*If the choice is HSI and its chosen to be on*/
			   /*set bit HSION on CR register*/

		   P_RCC_Register->RCC_CR_REG|=SYS_CLK_HSI;

		   /*wait until bits of HSIREADY is on or time is out*/

		   while(((P_RCC_Register->RCC_CR_REG&HSI_READY_MASK)==0)&&(loc_TimeOut!=0))
		   {
			   loc_TimeOut--;

		   }
		   /*check the reason for exit from the loop whether it is because HSIREADY is set
		    * or it is reached time out(if it is reached time out this is a problem and error*/

		   if((P_RCC_Register->RCC_CR_REG&HSI_READY_MASK)!=0)
		   {
			   Ret_enuSystemCLOCK = SYS_CLK_OK;
		   }
		   else
		   {
			   Ret_enuSystemCLOCK = SYS_CLK_ERROR_TIME_OUT;
		   }
		   break;
		   case OFF_STATE:

			   /*if its chosen to be on OFF state then clear the bits that represent HSION*/

			   P_RCC_Register->RCC_CR_REG&=(~SYS_CLK_HSI);
		   break;

		   }
		break;
		/*same steps for HSE and PLL*/

	   case SYS_CLK_HSE:
	   		  /* if((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)!=SYS_CLK_STATE_HSE_MASK)
	   		   {
	   			   Ret_enuSystemCLOCK=SYS_CLK_ERROR_WRONG_STATE;
	   		   }
	   		   else
	   		   {*/
	   			   Ret_enuSystemCLOCK = SYS_CLK_OK;

	   		   switch(Copy_ClkStatus)
	   		   {
	   		   case ON_STATE:
	   		   P_RCC_Register->RCC_CR_REG|=SYS_CLK_HSE;
	   		   while(((P_RCC_Register->RCC_CR_REG&HSE_READY_MASK)==0)&&(loc_TimeOut!=0))
	   		   {
	   			   loc_TimeOut--;

	   		   }
	   		   if((P_RCC_Register->RCC_CR_REG&HSE_READY_MASK)!=0)
	   		   {
	   			   Ret_enuSystemCLOCK = SYS_CLK_OK;
	   		   }
	   		   else
	   		   {
	   			   Ret_enuSystemCLOCK = SYS_CLK_ERROR_TIME_OUT;
	   		   }
	   		   break;
	   		   case OFF_STATE:

	   			   P_RCC_Register->RCC_CR_REG&=(~SYS_CLK_HSE);
	   		   break;
	   		   }


	   		break;

	   case SYS_CLK_PLL:
	   	   		  /* if((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)!=SYS_CLK_STATE_PLL_MASK)
	   	   		   {
	   	   			   Ret_enuSystemCLOCK=SYS_CLK_ERROR_WRONG_STATE;
	   	   		   }
	   	   		   else
	   	   		   {
	   	   			   Ret_enuSystemCLOCK = SYS_CLK_OK;
*/
	   	   		   switch(Copy_ClkStatus)
	   	   		   {
	   	   		   case ON_STATE:
	   	   		   P_RCC_Register->RCC_CR_REG|=SYS_CLK_PLL;
	   	   		   while(((P_RCC_Register->RCC_CR_REG&PLL_READY_MASK)==0)&&(loc_TimeOut!=0))
	   	   		   {
	   	   			   loc_TimeOut--;

	   	   		   }
	   	   		   if((P_RCC_Register->RCC_CR_REG&PLL_READY_MASK)!=0)
	   	   		   {
	   	   			   Ret_enuSystemCLOCK = SYS_CLK_OK;
	   	   		   }
	   	   		   else
	   	   		   {
	   	   			   Ret_enuSystemCLOCK = SYS_CLK_ERROR_TIME_OUT;
	   	   		   }
	   	   		   break;
	   	   		   case OFF_STATE:

	   	   			   P_RCC_Register->RCC_CR_REG&=(~SYS_CLK_PLL);
	   	   		   break;
	   	   		   }

	   	   		break;
	}



	return Ret_enuSystemCLOCK;
}

RCC_enu_Error_State  RCC_SelectClk (u32 Copy_ClockSystem)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;
	u32 loc_TimeOut=1000;
	if((Copy_ClockSystem!=SYS_CLK_HSE)&&(Copy_ClockSystem!=SYS_CLK_HSI)&&(Copy_ClockSystem!=SYS_CLK_PLL))
		{
			Ret_enuSystemCLOCK = SYS_CLK_NOT_OK;
		}
		else
		{
			Ret_enuSystemCLOCK = SYS_CLK_OK;
		}
	switch(Copy_ClockSystem)
	{
	   case SYS_CLK_HSI:
		   /*If the clock selected to be the system clock is HSI*/
		   /*Then check first that HSION is set and HSIREADY also is set on CR register*/
		if(((P_RCC_Register->RCC_CR_REG&SYS_CLK_HSI)==SYS_CLK_HSI)&&((P_RCC_Register->RCC_CR_REG&HSI_READY_MASK)==HSI_READY_MASK))
		{
			/*If they are set then make this algorithm to sets the value of SW bits(00)
			 * that represent that HSI is selected as system clock on CFGR register*/

			Ret_enuSystemCLOCK = SYS_CLK_OK;

			/*first store the value of the register on variable called loc_CheckState */

			u32 loc_CheckState=P_RCC_Register->RCC_CFGR_REG;

			/*then clear the bits that represents SW bits on CFGR register only this bits
			 * through using mask that is used to set this bit we not it to use it in clear operation*/

			loc_CheckState&=~SYS_CLK_SELECTED_MASK;

			/*Then put the wanted value on SW bits on CFGR register to represent
				 * HSI as a system clock*/

			loc_CheckState|=SYS_CLK_STATE_HSI_CHOSEN;
				/*then put return the value of loc_CheckState to CFGR register again after modified it*/

			P_RCC_Register->RCC_CFGR_REG=loc_CheckState;

                /*check whether SWS bits that is set by hardware to represent selected clock
                 * is set with value that represent that HSI is selected as system clock or not*/

			while(((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)!=SYS_CLK_STATE_HSI_MASK)&&(loc_TimeOut!=0))
			   {
				   loc_TimeOut--;

			   }
				/*check the reason for exit from the loop whether it is because SWS is set with the
			     * value that represent HSI as selected system clock or it is reached time out
			     * (if it is reached time out this is a problem and error*/

			if((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)==SYS_CLK_STATE_HSI_MASK)
				   {
					   Ret_enuSystemCLOCK = SYS_CLK_OK;
				   }
				   else
				   {
					   Ret_enuSystemCLOCK = SYS_CLK_ERROR_TIME_OUT;
				   }
		}
		else
		{
			Ret_enuSystemCLOCK=SYS_CLK_NOT_ON;
		}

	   break;

	   case SYS_CLK_HSE:

		   if(((P_RCC_Register->RCC_CR_REG&SYS_CLK_HSE)==SYS_CLK_HSE)&&((P_RCC_Register->RCC_CR_REG&HSE_READY_MASK)==HSE_READY_MASK))
		   		{
		   			Ret_enuSystemCLOCK = SYS_CLK_OK;
		   			u32 loc_CheckState=P_RCC_Register->RCC_CFGR_REG;
		   				loc_CheckState&=~SYS_CLK_SELECTED_MASK;
		   				loc_CheckState|=SYS_CLK_STATE_HSE_CHOSEN;
		   				P_RCC_Register->RCC_CFGR_REG=loc_CheckState;


		   				while(((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)!=SYS_CLK_STATE_HSE_MASK)&&(loc_TimeOut!=0))
		   			   {
		   				   loc_TimeOut--;

		   			   }
		   				 if((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)==SYS_CLK_STATE_HSE_MASK)
		   				   {
		   					   Ret_enuSystemCLOCK = SYS_CLK_OK;
		   				   }
		   				   else
		   				   {
		   					   Ret_enuSystemCLOCK = SYS_CLK_ERROR_TIME_OUT;
		   				   }
		   		}
		   		else
		   		{
		   			Ret_enuSystemCLOCK=SYS_CLK_NOT_ON;
		   		}



		    break;

	   case SYS_CLK_PLL:
		   if(((P_RCC_Register->RCC_CR_REG&SYS_CLK_PLL)==SYS_CLK_PLL)&&((P_RCC_Register->RCC_CR_REG&PLL_READY_MASK)==PLL_READY_MASK))
		   		{
		   			Ret_enuSystemCLOCK = SYS_CLK_OK;
		   			u32 loc_CheckState=P_RCC_Register->RCC_CFGR_REG;
		   				loc_CheckState&=~SYS_CLK_SELECTED_MASK;
		   				loc_CheckState|=SYS_CLK_STATE_PLL_CHOSEN;
		   				P_RCC_Register->RCC_CFGR_REG=loc_CheckState;


		   				while(((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)!=SYS_CLK_STATE_PLL_MASK)&&(loc_TimeOut!=0))
		   			   {
		   				   loc_TimeOut--;

		   			   }
		   				 if((P_RCC_Register->RCC_CFGR_REG&SYS_CLK_STATE_MASK)==SYS_CLK_STATE_PLL_MASK)
		   				   {
		   					   Ret_enuSystemCLOCK = SYS_CLK_OK;
		   				   }
		   				   else
		   				   {
		   					   Ret_enuSystemCLOCK = SYS_CLK_ERROR_TIME_OUT;
		   				   }
		   		}
		   		else
		   		{
		   			Ret_enuSystemCLOCK=SYS_CLK_NOT_ON;
		   		}


		   break;
	}

	return Ret_enuSystemCLOCK;

}

RCC_enu_Error_State  RCC_ConfigPLL(u32 PLL_PARAM_M,u32 PLL_PARAM_N,u32 PLL_PARAM_P,u32 PLL_PARAM_Q,u32 PLL_SOURCE)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;
   /*check that the value of M,N,P,Q on right range or not if one is not then error */
	if((PLL_PARAM_M>=2)&&(PLL_PARAM_M<=63))
	{
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		if((PLL_PARAM_N>=192)&&(PLL_PARAM_N<=432))
		{
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			if((PLL_PARAM_Q>=2)&&(PLL_PARAM_Q<=15))
			{
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				if((PLL_PARAM_P==2)||(PLL_PARAM_P==4)||(PLL_PARAM_P==6)||(PLL_PARAM_P==8))
				{
					Ret_enuSystemCLOCK = SYS_CLK_OK;
					if((PLL_SOURCE==PLL_INPUT_HSI)||(PLL_SOURCE==PLL_INPUT_HSE))
					{
						Ret_enuSystemCLOCK = SYS_CLK_OK;
					}
					else
					{
						Ret_enuSystemCLOCK = SYS_CLK_NOT_OK;
					}
				}
				else
				{
					Ret_enuSystemCLOCK = PLL_PARAM_P_OUT_RANGE;
				}
			}
			else
			{
				Ret_enuSystemCLOCK = PLL_PARAM_Q_OUT_RANGE;
			}
		}
		else
		{
			Ret_enuSystemCLOCK = PLL_PARAM_N_OUT_RANGE;
		}
	}
	else
	{
		Ret_enuSystemCLOCK = PLL_PARAM_M_OUT_RANGE;
	}

	/*check on the source of PLL clock whether it is HSI or HSE*/
	switch(PLL_SOURCE)
	{
	/*if it is HSE then set the bit on PLLCFGR register that represent source of PLL*/
	case PLL_INPUT_HSE:
	P_RCC_Register->RCC_PLLCFGR_REG|=PLL_INPUT_HSE;
	break;
	/*if it is HSI then set the bit on PLLCFGR register that represent source of PLL*/
	case PLL_INPUT_HSI:
	P_RCC_Register->RCC_PLLCFGR_REG&=~PLL_INPUT_HSE;
	break;
	}
	/************ check if PLL is on or not **********************/
	/************* if PLL is ON so we can`t configure PLL *************/
	if((P_RCC_Register->RCC_CR_REG&SYS_CLK_PLL)==SYS_CLK_PLL)
	{
		Ret_enuSystemCLOCK =PLL_NOT_DISABLE;
	}
	else
	{
	/******** set Q value on PLLCFGR register to configure it ********/
	u32 loc_CheckState_Q=P_RCC_Register->RCC_PLLCFGR_REG;
		loc_CheckState_Q&=~PLL_Q_BITS_MASK;
		/*shift the value 24 to be on the position of Q on PLLCFGR register as we can't make mask*/
		loc_CheckState_Q|=(PLL_PARAM_Q<<24);
		P_RCC_Register->RCC_PLLCFGR_REG=loc_CheckState_Q;
	/******** set P value on PLLCFGR register to configure it ********/
	u32 loc_CheckState_P=P_RCC_Register->RCC_PLLCFGR_REG;
		loc_CheckState_P&=~PLL_P_BITS_MASK;
		loc_CheckState_P|=(PLL_PARAM_P<<16);
		/*shift the value 16 to be on the position of P on PLLCFGR register as we can't make mask*/
		P_RCC_Register->RCC_PLLCFGR_REG=loc_CheckState_P;
	/******** set N value on PLLCFGR register to configure it ********/
	u32 loc_CheckState_N=P_RCC_Register->RCC_PLLCFGR_REG;
		loc_CheckState_N&=~PLL_N_BITS_MASK;
		loc_CheckState_N|=(PLL_PARAM_N<<6);
		/*shift the value 6 to be on the position of N on PLLCFGR register as we can't make mask*/
		P_RCC_Register->RCC_PLLCFGR_REG=loc_CheckState_N;
	/******** set M value on PLLCFGR register to configure it ********/
	u32 loc_CheckState_M=P_RCC_Register->RCC_PLLCFGR_REG;
		loc_CheckState_M&=~PLL_M_BITS_MASK;
		loc_CheckState_M|=(PLL_PARAM_M<<0);
		/*shift the value 0 to be on the position of M on PLLCFGR register as we can't make mask*/
		P_RCC_Register->RCC_PLLCFGR_REG=loc_CheckState_M;

	}


	return Ret_enuSystemCLOCK;

}

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_AHB1 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;

    /*switch on the chosen peripheral if it is on the list of peripheral of AHB bus
     * then make required operation else(default) return error status*/

	switch(Copy_Peripheral)
	{
	/*if the chosen peripheral is DMA2*/
	case DMA2_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		/*And if the status is ON this peripheral*/
		case ON_STATE:
			/*Then set the bits that represent DMA2 in AHB1ENR register*/
			P_RCC_Register->RCC_AHB1ENR_REG|=DMA2_PERIPHERAL;
		break;
		/*else if it is OFF*/
		case OFF_STATE:
			/*Then clear the bits that represent DMA2 in AHB1ENR register*/
			P_RCC_Register->RCC_AHB1ENR_REG&=~DMA2_PERIPHERAL;
		break;
		}
	break;

	case DMA1_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=DMA1_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~DMA1_PERIPHERAL;
		break;
		}
	break;
	case CRC_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=CRC_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~CRC_PERIPHERAL;
		break;
		}
	break;

	case GPIOH_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=GPIOH_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~GPIOH_PERIPHERAL;
		break;
		}
	break;

	case GPIOE_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=GPIOE_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~GPIOE_PERIPHERAL;
		break;
		}
	break;

	case GPIOD_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=GPIOD_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~GPIOD_PERIPHERAL;
		break;
		}
	break;

	case GPIOC_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=GPIOC_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~GPIOC_PERIPHERAL;
		break;
		}
	break;
	case GPIOB_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=GPIOB_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~GPIOB_PERIPHERAL;
		break;
		}
	break;
	case GPIOA_PERIPHERAL:
		Ret_enuSystemCLOCK = SYS_CLK_OK;
		switch(Copy_PeripheralStatus)
		{
		case ON_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG|=GPIOA_PERIPHERAL;
		break;
		case OFF_STATE:
			P_RCC_Register->RCC_AHB1ENR_REG&=~GPIOA_PERIPHERAL;
		break;
		}
	break;
	default:
		Ret_enuSystemCLOCK = AHB1_WRONG_PERIPHERAL;
	break;

	}

	return Ret_enuSystemCLOCK;
}

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_AHB2 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;

	switch(Copy_Peripheral)
		{
		case OTG_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_AHB2ENR_REG|=OTG_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_AHB2ENR_REG&=~OTG_PERIPHERAL;
			break;
			}
		break;
		default:
			Ret_enuSystemCLOCK = AHB2_WRONG_PERIPHERAL;
		break;
		}

	return Ret_enuSystemCLOCK;

}

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_APB1 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;

	switch(Copy_Peripheral)
		{
		case PWR_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=PWR_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~PWR_PERIPHERAL;
			break;
			}
		break;

		case I2C3_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=I2C3_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~I2C3_PERIPHERAL;
			break;
			}
		break;

		case I2C2_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=I2C2_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~I2C2_PERIPHERAL;
			break;
			}
		break;

		case I2C1_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=I2C1_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~I2C1_PERIPHERAL;
			break;
			}
		break;
		case UART2_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=UART2_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~UART2_PERIPHERAL;
			break;
			}
		break;

		case SPI3_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=SPI3_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~SPI3_PERIPHERAL;
			break;
			}
		break;

		case SPI2_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=SPI2_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~SPI2_PERIPHERAL;
			break;
			}
		break;

		case WWDG_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=WWDG_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~WWDG_PERIPHERAL;
			break;
			}
		break;

		case TIM5_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=TIM5_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~TIM5_PERIPHERAL;
			break;
			}
		break;

		case TIM4_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=TIM4_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~TIM4_PERIPHERAL;
			break;
			}
		break;

		case TIM3_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=TIM3_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~TIM3_PERIPHERAL;
			break;
			}
		break;

		case TIM2_PERIPHERAL:
			Ret_enuSystemCLOCK = SYS_CLK_OK;
			switch(Copy_PeripheralStatus)
			{
			case ON_STATE:
				P_RCC_Register->RCC_APB1ENR_REG|=TIM2_PERIPHERAL;
			break;
			case OFF_STATE:
				P_RCC_Register->RCC_APB1ENR_REG&=~TIM2_PERIPHERAL;
			break;
			}
		break;

		default:
			Ret_enuSystemCLOCK = APB1_WRONG_PERIPHERAL;
		break;
		}

	return Ret_enuSystemCLOCK;

}

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_APB2 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;

	switch(Copy_Peripheral)
			{
			case TIM11_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=TIM11_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~TIM11_PERIPHERAL;
				break;
				}
			break;

			case TIM10_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=TIM10_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~TIM10_PERIPHERAL;
				break;
				}
			break;
			case TIM9_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=TIM9_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~TIM9_PERIPHERAL;
				break;
				}
			break;

			case SYSCFG_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=SYSCFG_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~SYSCFG_PERIPHERAL;
				break;
				}
			break;

			case SPI4_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=SPI4_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~SPI4_PERIPHERAL;
				break;
				}
			break;

			case SPI1_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=SPI1_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~SPI1_PERIPHERAL;
				break;
				}
			break;

			case SDIO_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=SDIO_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~SDIO_PERIPHERAL;
				break;
				}
			break;

			case ADC1_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=ADC1_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~ADC1_PERIPHERAL;
				break;
				}
			break;

			case UART6_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=UART6_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~UART6_PERIPHERAL;
				break;
				}
			break;

			case UART1_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=UART1_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~UART1_PERIPHERAL;
				break;
				}
			break;

			case TIM1_PERIPHERAL:
				Ret_enuSystemCLOCK = SYS_CLK_OK;
				switch(Copy_PeripheralStatus)
				{
				case ON_STATE:
					P_RCC_Register->RCC_APB2ENR_REG|=TIM1_PERIPHERAL;
				break;
				case OFF_STATE:
					P_RCC_Register->RCC_APB2ENR_REG&=~TIM1_PERIPHERAL;
				break;
				}
			break;

			default:
				Ret_enuSystemCLOCK = AHB1_WRONG_PERIPHERAL;
			break;

			}


	return Ret_enuSystemCLOCK;
}

RCC_enu_Error_State  RCC_enuControlPrescalerAHB   (u32 Copy_u32AHBPrescaler)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;
	u32 loc_CheckState_AHB;
	/*switch on the chosen pre_scaler if it is out of the right choices then return error status*/
	switch(Copy_u32AHBPrescaler)
	{
	case AHB_PRESCALER_NOT_DIVIDED:
		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_NOT_DIVIDED;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;
	/*if the chosen pre_scaler id Divide it by 2 then:*/
	case AHB_PRESCALER_CLOCK_DIVIDED_BY_2:

		/*put the right value on the bits that represent pre_scaler of AHB bus with the same way we explain*/
		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_2;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;

	case AHB_PRESCALER_CLOCK_DIVIDED_BY_4:

		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_4;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;

	case AHB_PRESCALER_CLOCK_DIVIDED_BY_8:

		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_8;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;

	case AHB_PRESCALER_CLOCK_DIVIDED_BY_16:

		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_16;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;

	case AHB_PRESCALER_CLOCK_DIVIDED_BY_64:

		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_64;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;

	case AHB_PRESCALER_CLOCK_DIVIDED_BY_128:

		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_128;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;

	case AHB_PRESCALER_CLOCK_DIVIDED_BY_256:

		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_256;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;

	case AHB_PRESCALER_CLOCK_DIVIDED_BY_512:

		loc_CheckState_AHB=P_RCC_Register->RCC_CFGR_REG;
		loc_CheckState_AHB&=~AHB_PRESCALER_MASK;
		loc_CheckState_AHB|=AHB_PRESCALER_CLOCK_DIVIDED_BY_512;
		P_RCC_Register->RCC_CFGR_REG=loc_CheckState_AHB;

	break;
	default:
		Ret_enuSystemCLOCK = SYS_CLK_NOT_OK;
	break;
	}
	return Ret_enuSystemCLOCK;
}

RCC_enu_Error_State  RCC_enuControlPrescalerAPB1  (u32 Copy_u32APB1Prescaler)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;
	u32 loc_CheckState_APB1;
	switch(Copy_u32APB1Prescaler)
		{

		case APB1_PRESCALER_NOT_DIVIDED:

			loc_CheckState_APB1=P_RCC_Register->RCC_CFGR_REG;
			loc_CheckState_APB1&=~APB1_PRESCALER_MASK;
			loc_CheckState_APB1|=APB1_PRESCALER_NOT_DIVIDED;
			P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB1;
		break;

		case APB1_PRESCALER_CLOCK_DIVIDED_BY_2:

			loc_CheckState_APB1=P_RCC_Register->RCC_CFGR_REG;
			loc_CheckState_APB1&=~APB1_PRESCALER_MASK;
			loc_CheckState_APB1|=APB1_PRESCALER_CLOCK_DIVIDED_BY_2;
			P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB1;
		break;

		case APB1_PRESCALER_CLOCK_DIVIDED_BY_4:

			loc_CheckState_APB1=P_RCC_Register->RCC_CFGR_REG;
			loc_CheckState_APB1&=~APB1_PRESCALER_MASK;
			loc_CheckState_APB1|=APB1_PRESCALER_CLOCK_DIVIDED_BY_4;
			P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB1;
		break;

		case APB1_PRESCALER_CLOCK_DIVIDED_BY_8:

			loc_CheckState_APB1=P_RCC_Register->RCC_CFGR_REG;
			loc_CheckState_APB1&=~APB1_PRESCALER_MASK;
			loc_CheckState_APB1|=APB1_PRESCALER_CLOCK_DIVIDED_BY_8;
			P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB1;
		break;

		case APB1_PRESCALER_CLOCK_DIVIDED_BY_16:

			loc_CheckState_APB1=P_RCC_Register->RCC_CFGR_REG;
			loc_CheckState_APB1&=~APB1_PRESCALER_MASK;
			loc_CheckState_APB1|=APB1_PRESCALER_CLOCK_DIVIDED_BY_16;
			P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB1;
		break;

		default:
			Ret_enuSystemCLOCK = SYS_CLK_NOT_OK;
		break;

		}
	return Ret_enuSystemCLOCK;
}

RCC_enu_Error_State  RCC_enuControlPrescalerAPB2  (u32 Copy_u32APB2Prescaler)
{
	RCC_enu_Error_State Ret_enuSystemCLOCK = SYS_CLK_OK;
	u32 loc_CheckState_APB2;
	switch(Copy_u32APB2Prescaler)
			{

			case APB2_PRESCALER_NOT_DIVIDED:

				loc_CheckState_APB2=P_RCC_Register->RCC_CFGR_REG;
				loc_CheckState_APB2&=~APB2_PRESCALER_MASK;
				loc_CheckState_APB2|=APB2_PRESCALER_NOT_DIVIDED;
				P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB2;
			break;

			case APB2_PRESCALER_CLOCK_DIVIDED_BY_2:

				loc_CheckState_APB2=P_RCC_Register->RCC_CFGR_REG;
				loc_CheckState_APB2&=~APB2_PRESCALER_MASK;
				loc_CheckState_APB2|=APB2_PRESCALER_CLOCK_DIVIDED_BY_2;
				P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB2;
			break;

			case APB2_PRESCALER_CLOCK_DIVIDED_BY_4:

				loc_CheckState_APB2=P_RCC_Register->RCC_CFGR_REG;
				loc_CheckState_APB2&=~APB2_PRESCALER_MASK;
				loc_CheckState_APB2|=APB2_PRESCALER_CLOCK_DIVIDED_BY_4;
				P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB2;
			break;

			case APB2_PRESCALER_CLOCK_DIVIDED_BY_8:

				loc_CheckState_APB2=P_RCC_Register->RCC_CFGR_REG;
				loc_CheckState_APB2&=~APB2_PRESCALER_MASK;
				loc_CheckState_APB2|=APB2_PRESCALER_CLOCK_DIVIDED_BY_8;
				P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB2;
			break;

			case APB2_PRESCALER_CLOCK_DIVIDED_BY_16:

				loc_CheckState_APB2=P_RCC_Register->RCC_CFGR_REG;
				loc_CheckState_APB2&=~APB2_PRESCALER_MASK;
				loc_CheckState_APB2|=APB2_PRESCALER_CLOCK_DIVIDED_BY_16;
				P_RCC_Register->RCC_CFGR_REG=loc_CheckState_APB2;
			break;

			default:
				Ret_enuSystemCLOCK = SYS_CLK_NOT_OK;
			break;

			}

	return Ret_enuSystemCLOCK;
}
