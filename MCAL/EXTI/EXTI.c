/*
 * EXTI.c
 *
 *  Created on: May 9, 2024
 *      Author: Rana
 */


/******************************** Includes ************************************/

#include "EXTI.h"

/******************************** Defines ************************************/

#define EXTI_BASE_ADDRESS  0x40013C00
/******************************** Types ************************************/

/*Struct represent registers on EXTI */

typedef struct{
	volatile u32 EXTI_IMR_REG;
	volatile u32 EXTI_EMR_REG;
	volatile u32 EXTI_RTSR_REG;
	volatile u32 EXTI_FTSR_REG;
	volatile u32 EXTI_SWIER_REG;
	volatile u32 EXTI_PR_REG;
}EXTI_t;

/***************************** Variables **********************************/

/*pointer to refer to struct that represent register so I can use it to refer
 * to elements(registers) on the struct through -> operator*/

static EXTI_t*const P_EXTI_Reg=(EXTI_t*)EXTI_BASE_ADDRESS;
/*global variable that represent pointer to function*/
static void (*EXTI0_CallBack) (void)=NULL;
static void (*EXTI1_CallBack) (void)=NULL;
static void (*EXTI2_CallBack) (void)=NULL;

/**************************** Implementation ******************************/
void MEXTI_voidInit()
{
  #if EXTI_MODE==RISING_EDGE
	//P_EXTI_Reg->EXTI_RTSR_REG|=(1<<EXTI_LINE);
	P_EXTI_Reg->EXTI_RTSR_REG|=(1<<EXTI_LINE);
 #elif EXTI_MODE==FALLING_EDGE
	P_EXTI_Reg->EXTI_FTSR_REG|=(1<<EXTI_LINE);
 #elif EXTI_MODE==ON_CHANGE_EDGE
	P_EXTI_Reg->EXTI_RTSR_REG|=(1<<EXTI_LINE);
	P_EXTI_Reg->EXTI_FTSR_REG|=(1<<EXTI_LINE);
 #else
    #error "wrong mode and line choice"
 #endif

    /*Disable interrupt*/
	//P_EXTI_Reg->EXTI_IMR_REG&=~(1<<copy_u8Line);

}
void MEXTI_voidEnableEXTI(u8 copy_u8Line)
{
	P_EXTI_Reg->EXTI_IMR_REG|=(1<<copy_u8Line);
}
void MEXTI_voidDisableEXTI(u8 copy_u8Line)
{
	P_EXTI_Reg->EXTI_IMR_REG&=~(1<<copy_u8Line);
}
void MEXTI_voidSwTrigger(u8 copy_u8Line)
{
	P_EXTI_Reg->EXTI_SWIER_REG|=(1<<copy_u8Line);
}
void MEXTI_voidSetSignalLatch(u8 copy_u8Line,u8 copy_u8Mode)
{
	switch(copy_u8Mode)
	{
	case RISING_EDGE:
		P_EXTI_Reg->EXTI_RTSR_REG|=(1<<copy_u8Line);
		break;
	case FALLING_EDGE:
		P_EXTI_Reg->EXTI_FTSR_REG|=(1<<copy_u8Line);
		break;
	case ON_CHANGE_EDGE:
		P_EXTI_Reg->EXTI_RTSR_REG|=(1<<copy_u8Line);
		P_EXTI_Reg->EXTI_FTSR_REG|=(1<<copy_u8Line);
		break;
	}
	/*new add*/
	P_EXTI_Reg->EXTI_IMR_REG|=(1<<copy_u8Line);
}
/*For EXTI0*/
/*that is called on main and give it pointer to function
 * you want to give to ISR*/
void MEXTI_voidSetCallBack_EXTI0(void (*ptr)(void))
{
	EXTI0_CallBack=ptr;
}

/*name of periphral+_+IRQ+Handler*/
/*so compilar can understand that it is ISR that is called by HW*/
void EXTI0_IRQHandler(void)
{
	EXTI0_CallBack();
	/*clear pending bit*/
	P_EXTI_Reg->EXTI_PR_REG|=(1<<0);
}

/*For EXTI1*/
void MEXTI_voidSetCallBack_EXTI1(void (*ptr)(void))
{
	EXTI1_CallBack=ptr;
}

/*name of periphral+_+IRQ+Handler*/
/*so compilar can understand that it is ISR that is called by HW*/
void EXTI1_IRQHandler(void)
{
	EXTI1_CallBack();
	/*clear pending bit*/
	P_EXTI_Reg->EXTI_PR_REG|=(1<<1);
}

/*For EXTI2*/
void MEXTI_voidSetCallBack_EXTI2(void (*ptr)(void))
{
	EXTI2_CallBack=ptr;
}

/*name of periphral+_+IRQ+Handler*/
/*so compilar can understand that it is ISR that is called by HW*/
void EXTI2_IRQHandler(void)
{
	EXTI2_CallBack();
	/*clear pending bit*/
	P_EXTI_Reg->EXTI_PR_REG|=(1<<2);
}


/*****************************************/

#define ALTER_BASE_ADDRESS  0x40013800
/******************************** Types ************************************/

/*Struct represent registers on EXTI */

typedef struct{
	volatile u32 SYSCFG_MEMRMP_REG;
	volatile u32 SYSCFG_PMC_REG;
	volatile u32 SYSCFG_EXTICR_REG[4];
	/*volatile u32 SYSCFG_EXTICR2_REG;
	volatile u32 SYSCFG_EXTICR3_REG;
	volatile u32 SYSCFG_EXTICR4_REG;*/
	volatile u32 SYSCFG_CMPCR_REG;
}ALTER_t;

/***************************** Variables **********************************/

/*pointer to refer to struct that represent register so I can use it to refer
 * to elements(registers) on the struct through -> operator*/

static ALTER_t*const P_ALTER_Reg=(ALTER_t*)ALTER_BASE_ADDRESS;


/**************************** Implementation ******************************/

void MAFIO_voidSetEXTIConfig(u8 copy_u8Line,u8 copy_u8PortMap)
{
	u8 Loc_u8RegIndex=0;
	if(copy_u8Line<=3)
	{
		Loc_u8RegIndex=0;
	}
	else if(copy_u8Line<=7)
	{
		Loc_u8RegIndex=1;
		copy_u8Line-=4;
	}
	else if(copy_u8Line<=11)
	{
		Loc_u8RegIndex=2;
		copy_u8Line-=8;
	}
	else if(copy_u8Line<=15)
	{
		Loc_u8RegIndex=3;
		copy_u8Line-=12;
	}
	else
	{

	}

	//P_ALTER_Reg->SYSCFG_EXTICR_REG[Loc_u8RegIndex] &~=((0b1111)<<(copy_u8Line*4));
	P_ALTER_Reg->SYSCFG_EXTICR_REG[Loc_u8RegIndex]&=~((0b1111)<<(copy_u8Line*4));
	P_ALTER_Reg->SYSCFG_EXTICR_REG[Loc_u8RegIndex] |=((copy_u8PortMap)<<(copy_u8Line*4));
}
