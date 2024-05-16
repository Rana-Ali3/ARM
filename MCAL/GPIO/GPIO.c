/*
 * GPIO.c
 *
 *  Created on: Feb 24, 2024
 *      Author: Rana
 */

/******************************** Includes ************************************/

#include"GPIO.h"

/******************************** Defines ************************************/

/*Base address of GPIO */
/*
#define GPIOA_BASE_ADDRESS       0x40020000
#define GPIOB_BASE_ADDRESS       0x40020400
#define GPIOC_BASE_ADDRESS       0x40020800
#define GPIOD_BASE_ADDRESS       0x40020C00
#define GPIOE_BASE_ADDRESS       0x40021000
*/

#define Mask_PIN 0x00000003

#define INPUT_MODE			 		0x00000000
#define OUTPUT_MODE 				0x1
#define ALTERNATIVE_FUNCTION_MODE   0X2
#define ANALOG_MODE                 0X3

#define PUSH_PULL_MODE 0
#define OPEN_DRAIN_MODE 1

#define PUSH_PULL_MASK             0x10
#define OPEN_DRAIN_MASK            0X20
#define AF_PUSH_PULLL_MASK         0X30
#define AF_OPEN_DRAIN_MASK          0X40
#define ANALOG_MASK                0X50

#define OFF_STATE_MASK             1

#define SHIFTED_BITS_ON_BSRR_TO_RESET_ODR 16
/*#define PUSH_PULL_PULL_UP_MASK    0x01
#define PUSH_PULL_PULL_DOWN_MASK  0x02*/

/******************************** Types ************************************/

/*Struct represent registers on GPIO*/
typedef struct
{
	volatile u32 GPIO_MODER_REG;
	volatile u32 GPIO_OTYPER_REG;
	volatile u32 GPIO_OSPEEDR_REG;
	volatile u32 GPIO_PUPDR_REG;
	volatile u32 GPIO_IDR_REG;
	volatile u32 GPIO_ODR_REG;
	volatile u32 GPIO_BSRR_REG;
	volatile u32 GPIO_LCKR_REG;
	volatile u32 GPIO_AFRL_REG;
	volatile u32 GPIO_AFRH_REG;
}GPIO_REG;

/***************************** Variables **********************************/

/*pointer to refer to struct that represent register so I can use it to refer
 * to elements(registers) on the struct through -> operator*/
/*
static GPIO_REG*const P_GPIOA_Register=(GPIO_REG*)GPIOA_BASE_ADDRESS;
static GPIO_REG*const P_GPIOB_Register=(GPIO_REG*)GPIOB_BASE_ADDRESS;
static GPIO_REG*const P_GPIOC_Register=(GPIO_REG*)GPIOC_BASE_ADDRESS;
static GPIO_REG*const P_GPIOD_Register=(GPIO_REG*)GPIOD_BASE_ADDRESS;
static GPIO_REG*const P_GPIOE_Register=(GPIO_REG*)GPIOE_BASE_ADDRESS;
*/

/**************************** Implementation ******************************/

GPIO_enu_Error_State GPIO_init(GPIO_PIN_PARAM *GPIO_PIN)
{
	GPIO_enu_Error_State Ret_enuGPIOState = GPIO_OK;
	//if((GPIO_PIN->port!=GPIO_POART_A)||(GPIO_PIN->port!=GPIO_POART_B)||(GPIO_PIN->port!=GPIO_POART_C)||(GPIO_PIN->port!=GPIO_POART_D)||(GPIO_PIN->port!=GPIO_POART_E))
	if((GPIO_PIN->port!=GPIO_POART_A)&&(GPIO_PIN->port!=GPIO_POART_B)&&(GPIO_PIN->port!=GPIO_POART_C)&&(GPIO_PIN->port!=GPIO_POART_D)&&(GPIO_PIN->port!=GPIO_POART_E))
	{
		Ret_enuGPIOState =GPIO_WRONG_PORT;
	}
	else if(GPIO_PIN->pin>MAX_NUM_OF_PIN)
	{
		Ret_enuGPIOState =GPIO_WRONG_PIN;
	}
	else if((GPIO_PIN->speed!=GPIO_LOW_SPEED)&&(GPIO_PIN->speed!=GPIO_MEDIUM_SPEED)&&(GPIO_PIN->speed!=GPIO_HIGH_SPEED)&&(GPIO_PIN->speed!=GPIO_VERY_HIGH_SPEED))
	{
		Ret_enuGPIOState =GPIO_WRONG_SPEED_VALUE;
	}

	else
	{
		 Ret_enuGPIOState = GPIO_OK;
		 u32 loc_CheckStateMode=((GPIO_REG*)GPIO_PIN->port)->GPIO_MODER_REG;
		 u32 loc_CheckStateSpeed=((GPIO_REG*)GPIO_PIN->port)->GPIO_OSPEEDR_REG;
		 u32 loc_CheckState=((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG;

////////////////////////////////////////////////////////////////////////////////////
		 if((GPIO_PIN->mode==MODE_INPUT_FLOATING)||(GPIO_PIN->mode==MODE_INPUT_PULL_UP)||(GPIO_PIN->mode==MODE_INPUT_PULL_DOWN))
		 {

			 /*sets the value of bits on MODER_register that represent INPUT mode*/
			 loc_CheckStateMode&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckStateMode|=INPUT_MODE;
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_MODER_REG=loc_CheckStateMode;

			 /*set the value of bits on PUPDR register that represent floating mode or pull up mode or pull down mode*/
			 loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckState|=GPIO_PIN->mode<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;
		 }
		 else if((GPIO_PIN->mode==MODE_OUTPUT_OPEN_DRAIN)||(GPIO_PIN->mode==MODE_OUTPUT_OPEN_DRAIN_PULL_UP)||(GPIO_PIN->mode==MODE_OUTPUT_OPEN_DRAIN_PULL_DOWN)||(GPIO_PIN->mode==MODE_OUTPUT_PUSH_PULL)||(GPIO_PIN->mode==MODE_OUTPUT_PUSH_PULL_PULL_UP)||(GPIO_PIN->mode==MODE_OUTPUT_PUSH_PULL_PULL_DOWN))
		 {
			 /*sets the value of bits on MODER_register that represent OUTPUT mode*/
			 loc_CheckStateMode&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckStateMode|=OUTPUT_MODE<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_MODER_REG=loc_CheckStateMode;

			 /*set the value of bits on PUPDR register that represent output PULLDOWN mode or pull up mode or floating mode*/
			 /*loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckState|=(GPIO_PIN->mode&(~OPEN_DRAIN_MASK))<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;*/

			 /*set value of bits on OSPEED register that represent speed value*/
			 loc_CheckStateSpeed&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckStateSpeed|=(GPIO_PIN->speed)<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_OSPEEDR_REG=loc_CheckStateSpeed;

			 if((GPIO_PIN->mode==MODE_OUTPUT_OPEN_DRAIN_PULL_DOWN)||(GPIO_PIN->mode==MODE_OUTPUT_OPEN_DRAIN_PULL_UP)||(GPIO_PIN->mode==MODE_OUTPUT_OPEN_DRAIN))
			 {
				 /*set the value of bits on PUPDR register that represent output PULLDOWN mode or pull up mode or floating mode*/
				 loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
				 loc_CheckState|=(GPIO_PIN->mode&(~OPEN_DRAIN_MASK))<<((GPIO_PIN->pin)*2);
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;

				 /*set value of bits of OTYPER register that represent open drain mode */
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_OTYPER_REG|=OPEN_DRAIN_MODE<<(GPIO_PIN->pin);
			 }
			 else
			 {
				 /*set the value of bits on PUPDR register that represent floating mode or pull up mode or pull down mode*/
				 loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
				 loc_CheckState|=(GPIO_PIN->mode&(~PUSH_PULL_MASK))<<((GPIO_PIN->pin)*2);
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;
				 /*set value of bits of OTYPER register that represent PUSH_PULL mode */
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_OTYPER_REG&=PUSH_PULL_MODE<<(GPIO_PIN->pin);
			 }


		 }
		 else if((GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN)||(GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_UP)||(GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_DOWN)||(GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_PUSH_PULL)||(GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_UP)||(GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_DOWN))
		 {
			 /*sets the value of bits on MODER_register that represent ALTERNATIVE FUNCTION mode*/
			 loc_CheckStateMode&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckStateMode|=ALTERNATIVE_FUNCTION_MODE<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_MODER_REG=loc_CheckStateMode;

			 /*set the value of bits on PUPDR register that represent output PULLDOWN mode or pull up mode or floating mode*/
			/* loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckState|=GPIO_PIN->mode<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;*/

			 /*set value of bits on OSPEED register that represent speed value*/
			 loc_CheckStateSpeed&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckStateSpeed|=(GPIO_PIN->speed)<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_OSPEEDR_REG=loc_CheckStateSpeed;

			 if((GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN)||(GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_UP)||(GPIO_PIN->mode==MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_DOWN))
			 {
				 /*set the value of bits on PUPDR register that represent output PULLDOWN mode or pull up mode or floating mode*/
				 loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
				 loc_CheckState|=(GPIO_PIN->mode&(~AF_OPEN_DRAIN_MASK))<<((GPIO_PIN->pin)*2);
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;

				 /*set value of bits of OTYPER register that represent open drain mode */
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_OTYPER_REG&=OPEN_DRAIN_MODE<<(GPIO_PIN->pin);
			 }
			 else
			 {
				 /*set the value of bits on PUPDR register that represent output PULLDOWN mode or pull up mode or floating mode*/
				 loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
				 loc_CheckState|=(GPIO_PIN->mode&(~AF_PUSH_PULLL_MASK))<<((GPIO_PIN->pin)*2);
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;

				 /*set value of bits of OTYPER register that represent PUSH_PULL mode */
				 ((GPIO_REG*)GPIO_PIN->port)->GPIO_OTYPER_REG&=PUSH_PULL_MODE<<(GPIO_PIN->pin);
			 }

		 }
		 else if(GPIO_PIN->mode==MODE_ANALOG)
		 {
			 /*sets the value of bits on MODER_register that represent ANALOG mode*/
			 loc_CheckStateMode&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckStateMode|=ANALOG_MODE<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_MODER_REG=loc_CheckStateMode;

			 /*set the value of bits on PUPDR register that represent ANALOG mode*/
			 loc_CheckState&=~(Mask_PIN<<((GPIO_PIN->pin)*2));
			 loc_CheckState|=(GPIO_PIN->mode&(~ANALOG_MASK))<<((GPIO_PIN->pin)*2);
			 ((GPIO_REG*)GPIO_PIN->port)->GPIO_PUPDR_REG=loc_CheckState;

		 }
		 else
		 {
			 Ret_enuGPIOState = GPIO_INVALID_MODE;
		 }


	}

		return Ret_enuGPIOState;

}

GPIO_enu_Error_State GPIO_SetPinValue(void* GPIO_Port,u32 GPIO_Pin,u8 GPIO_PinValue)
{
	GPIO_enu_Error_State Ret_enuGPIOState = GPIO_OK;

	/*check on the error status of ports and pins and right state*/
	if((GPIO_Port!=GPIO_POART_A)&&(GPIO_Port!=GPIO_POART_B)&&(GPIO_Port!=GPIO_POART_C)&&(GPIO_Port!=GPIO_POART_D)&&(GPIO_Port!=GPIO_POART_E))
	//	if(GPIO_Port==NULL)
	    {
			Ret_enuGPIOState =GPIO_WRONG_PORT;
		}
		else if(GPIO_Pin>MAX_NUM_OF_PIN)
		{
			Ret_enuGPIOState =GPIO_WRONG_PIN;
		}
		else if((GPIO_PinValue!=ON_STATE)&&(GPIO_PinValue!=OFF_STATE))
		{
			Ret_enuGPIOState =GPIO_INVALID_VALUE;
		}
		else
		{
			Ret_enuGPIOState = GPIO_OK;
		}
		if(Ret_enuGPIOState== GPIO_OK)
		{
			Ret_enuGPIOState = GPIO_OK;
			/*switch on the state is it on state or off state*/
			switch(GPIO_PinValue)
			{
			case ON_STATE:
				 /*case on state set the value of BSRR register that
				 * represent set of ODR register that represent this pin*/
				((GPIO_REG*)GPIO_Port)->GPIO_BSRR_REG=ON_STATE<<(GPIO_Pin);
				break;
			case OFF_STATE:
				 /*case off state set the value of BSRR register that
				 * represent reset of ODR register that represent this pin*/
				((GPIO_REG*)GPIO_Port)->GPIO_BSRR_REG=OFF_STATE_MASK<<(GPIO_Pin+SHIFTED_BITS_ON_BSRR_TO_RESET_ODR);
				break;
			}
		}



	return Ret_enuGPIOState;

}

GPIO_enu_Error_State GPIO_GetPinValue(void* GPIO_Port,u32 GPIO_Pin,u8* GPIO_PinValueGitted)
{
	GPIO_enu_Error_State Ret_enuGPIOState = GPIO_OK;
	//if(((GPIO_REG*)GPIO_Port!=GPIO_POART_A)||((GPIO_REG*)GPIO_Port!=GPIO_POART_B)||((GPIO_REG*)GPIO_Port!=GPIO_POART_C)||((GPIO_REG*)GPIO_Port!=GPIO_POART_D)||((GPIO_REG*)GPIO_Port!=GPIO_POART_E))
	//if(GPIO_Port==NULL)
	if((GPIO_Port!=GPIO_POART_A)&&(GPIO_Port!=GPIO_POART_B)&&(GPIO_Port!=GPIO_POART_C)&&(GPIO_Port!=GPIO_POART_D)&&(GPIO_Port!=GPIO_POART_E))
	{
		Ret_enuGPIOState =GPIO_WRONG_PORT;
	}
	else if(GPIO_Pin>MAX_NUM_OF_PIN)
	{
		Ret_enuGPIOState =GPIO_WRONG_PIN;
	}
	else
	{
		/*set the value og the pin into GPIO_PinValueGitted variable by reference to store it on it*/
		Ret_enuGPIOState = GPIO_OK;
		*GPIO_PinValueGitted=(((GPIO_REG*)GPIO_Port)->GPIO_IDR_REG)&(1<<GPIO_Pin);
	}
	return Ret_enuGPIOState;
}
