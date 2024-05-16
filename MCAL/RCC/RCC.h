/*
 * RCC.h
 *
 *  Created on: Feb 13, 2024
 *      Author: Rana
 */

#include"../LIB/STD_TYPES.h"

#ifndef MCAL_RCC_H_
#define MCAL_RCC_H_


/****************************** Defines ******************************/

/************** choose system clock you want ******************/
#define SYS_CLK_HSI 0x00000001
#define SYS_CLK_HSE 0x00010000
#define SYS_CLK_PLL 0x01000000
/************** Masks to select clock ******************/
#define SYS_CLK_STATE_HSI_CHOSEN 0x00000000
#define SYS_CLK_STATE_HSE_CHOSEN 0x00000001
#define SYS_CLK_STATE_PLL_CHOSEN 0x00000002
/************* Choose source for PLL ******************/
#define PLL_INPUT_HSI 0x00000000
#define PLL_INPUT_HSE 0x00400000

/************** choose your clock state whether it is ON or OFF ******************/
#define ON_STATE  1
#define OFF_STATE 0

/*************** Peripherals for AHP1 **********************/
#define DMA2_PERIPHERAL  0x00400000
#define DMA1_PERIPHERAL  0x00200000
#define CRC_PERIPHERAL   0x00001000
#define GPIOH_PERIPHERAL 0x00000080
#define GPIOE_PERIPHERAL 0x00000010
#define GPIOD_PERIPHERAL 0x00000008
#define GPIOC_PERIPHERAL 0x00000004
#define GPIOB_PERIPHERAL 0x00000002
#define GPIOA_PERIPHERAL 0x00000001
/*************** Peripherals for AHP2 **********************/
#define OTG_PERIPHERAL   0x00000080
/*************** Peripherals for APB1 **********************/
#define PWR_PERIPHERAL    0x10000000
#define I2C3_PERIPHERAL   0x00800000
#define I2C2_PERIPHERAL   0x00400000
#define I2C1_PERIPHERAL   0x00200000
#define UART2_PERIPHERAL  0x00020000
#define SPI3_PERIPHERAL   0x00008000
#define SPI2_PERIPHERAL   0x00004000
#define WWDG_PERIPHERAL   0x00000800
#define TIM5_PERIPHERAL   0x00000008
#define TIM4_PERIPHERAL   0x00000004
#define TIM3_PERIPHERAL   0x00000002
#define TIM2_PERIPHERAL   0x00000001
/*************** Peripherals for APB2 **********************/
#define TIM11_PERIPHERAL     0x00040000
#define TIM10_PERIPHERAL     0x00020000
#define TIM9_PERIPHERAL      0x00010000
#define SYSCFG_PERIPHERAL    0x00004000
#define SPI4_PERIPHERAL      0x00002000
#define SPI1_PERIPHERAL      0x00001000
#define SDIO_PERIPHERAL      0x00000800
#define ADC1_PERIPHERAL      0x00000100
#define UART6_PERIPHERAL     0x00000020
#define UART1_PERIPHERAL     0x00000010
#define TIM1_PERIPHERAL      0x00000001

/**************** Prescaler for AHB *************************/
#define AHB_PRESCALER_NOT_DIVIDED            0x00000000
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_2     0x00000080
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_4     0x00000090
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_8     0x000000A0
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_16    0x000000B0
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_64    0x000000C0
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_128   0x000000D0
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_256   0x000000E0
#define AHB_PRESCALER_CLOCK_DIVIDED_BY_512   0x000000F0

/**************** Prescaler for APB1 *************************/
#define APB1_PRESCALER_NOT_DIVIDED             0x00000000
#define APB1_PRESCALER_CLOCK_DIVIDED_BY_2      0x00001000
#define APB1_PRESCALER_CLOCK_DIVIDED_BY_4      0x00001400
#define APB1_PRESCALER_CLOCK_DIVIDED_BY_8      0x00001800
#define APB1_PRESCALER_CLOCK_DIVIDED_BY_16     0x00001C00

/**************** Prescaler for APB2 *************************/
#define APB2_PRESCALER_NOT_DIVIDED             0x00000000
#define APB2_PRESCALER_CLOCK_DIVIDED_BY_2      0x00008000
#define APB2_PRESCALER_CLOCK_DIVIDED_BY_4      0x0000A000
#define APB2_PRESCALER_CLOCK_DIVIDED_BY_8      0x0000C000
#define APB2_PRESCALER_CLOCK_DIVIDED_BY_16     0x0000E000





/****************************** Types *******************************/

/************* enum to represent error ************************/
typedef enum{
	SYS_CLK_NOT_OK,
	SYS_CLK_ERROR_TIME_OUT,
	SYS_CLK_ERROR_WRONG_STATE,
	SYS_CLK_NOT_ON,
	SYS_CLK_NOT_READY,
	PLL_PARAM_M_OUT_RANGE,
	PLL_PARAM_N_OUT_RANGE,
	PLL_PARAM_P_OUT_RANGE,
	PLL_PARAM_Q_OUT_RANGE,
	PLL_NOT_DISABLE,
	AHB1_WRONG_PERIPHERAL,
	AHB2_WRONG_PERIPHERAL,
	APB1_WRONG_PERIPHERAL,
	APB2_WRONG_PERIPHERAL,
	SYS_CLK_OK
}RCC_enu_Error_State;


/****************************** API *******************************/
/* this function is to select your Clock
 *
 * input parameter: it take input from this list:
 * SYS_CLK_HSI
 * SYS_CLK_HSE
 * SYS_CLK_PLL
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */
RCC_enu_Error_State  RCC_SelectClk (u32 Copy_ClockSystem);

/* this function is to make your clock source on or off
 *
 * input parameter: it take input from this list:
 * SYS_CLK_HSI
 * SYS_CLK_HSE
 * SYS_CLK_PLL
 *
 * and the other input represent the state of the clock whether it is ON or OFF
 *  it take input from this list:
 *  ON_STATE
 *  OFF_STATE
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */
RCC_enu_Error_State  RCC_ControlClk(u32 Copy_ClockSystem,u8 Copy_ClkStatus);
/*
 * This function is to select configuration of PLL (N,M,P,Q) and its source (HSI,HSE)
 *
 * This function take parameter as:
 * PLL_PARAM_M--> it take values from range 2:63
 * PLL_PARAM_N--> it take values from range 192:432
 * PLL_PARAM_P--> it take values from this list [2,4,6,8]
 * PLL_PARAM_Q--> it take values from range 2:15
 * PLL_SOURCE--> it take one choice from this choise:PLL_INPUT_HSI,PLL_INPUT_HSE
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */
RCC_enu_Error_State  RCC_ConfigPLL(u32 PLL_PARAM_M,u32 PLL_PARAM_N,u32 PLL_PARAM_P,u32 PLL_PARAM_Q,u32 PLL_SOURCE);

/* this function is to enable or disable peripherals on AHB1 bus
 *
 * input parameter: it take input from this list:
 * DMA2_PERIPHERAL
 * DMA1_PERIPHERAL
 * CRC_PERIPHERAL
 * GPIOH_PERIPHERAL
 * GPIOE_PERIPHERAL
 * GPIOD_PERIPHERAL
 * GPIOC_PERIPHERAL
 * GPIOB_PERIPHERAL
 * GPIOA_PERIPHERAL
 *
 * and the other input represent the state of the clock whether it is ON or OFF
 *  it take input from this list:
 *  ON_STATE
 *  OFF_STATE
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_AHB1 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus);

/* this function is to enable or disable peripherals on AHB2 bus
 *
 * input parameter: it take input from this list:
 * OTG_PERIPHERAL
 *
 * and the other input represent the state of the clock whether it is ON or OFF
 *  it take input from this list:
 *  ON_STATE
 *  OFF_STATE
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_AHB2 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus);

/* this function is to enable or disable peripherals on APB1 bus
 *
 * input parameter: it take input from this list:
 * PWR_PERIPHERAL
 * I2C3_PERIPHERAL
 * I2C2_PERIPHERAL
 * I2C1_PERIPHERAL
 * UART2_PERIPHERAL
 * SPI3_PERIPHERAL
 * SPI2_PERIPHERAL
 * WWDG_PERIPHERAL
 * TIM5_PERIPHERAL
 * TIM4_PERIPHERAL
 * TIM3_PERIPHERAL
 * TIM2_PERIPHERAL
 *
 * and the other input represent the state of the clock whether it is ON or OFF
 *  it take input from this list:
 *  ON_STATE
 *  OFF_STATE
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_APB1 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus);

/* this function is to enable or disable peripherals on APB2 bus
 *
 * input parameter: it take input from this list:
 * TIM11_PERIPHERAL
 * TIM10_PERIPHERAL
 * TIM9_PERIPHERAL
 * SYSCFG_PERIPHERAL
 * SPI4_PERIPHERAL
 * SPI1_PERIPHERAL
 * SDIO_PERIPHERAL
 * ADC1_PERIPHERAL
 * UART6_PERIPHERAL
 * UART1_PERIPHERAL
 * TIM1_PERIPHERAL
 *
 * and the other input represent the state of the clock whether it is ON or OFF
 *  it take input from this list:
 *  ON_STATE
 *  OFF_STATE
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */

RCC_enu_Error_State  RCC_Enable_Disable_Periphral_APB2 (u32 Copy_Peripheral,u8 Copy_PeripheralStatus);

/* this function is to select your prescaler on AHB bus
 *
 * input parameter: it take input from this list:
 * AHB_PRESCALER_NOT_DIVIDED
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_2
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_4
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_8
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_16
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_64
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_128
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_256
 * AHB_PRESCALER_CLOCK_DIVIDED_BY_512
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */
RCC_enu_Error_State  RCC_enuControlPrescalerAHB   (u32 Copy_u32AHBPrescaler);

/* this function is to select your prescaler on APB1 bus
 *
 * input parameter: it take input from this list:
 * APB1_PRESCALER_NOT_DIVIDED
 * APB1_PRESCALER_CLOCK_DIVIDED_BY_2
 * APB1_PRESCALER_CLOCK_DIVIDED_BY_4
 * APB1_PRESCALER_CLOCK_DIVIDED_BY_8
 * APB1_PRESCALER_CLOCK_DIVIDED_BY_16
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */

RCC_enu_Error_State  RCC_enuControlPrescalerAPB1  (u32 Copy_u32APB1Prescaler);

/* this function is to select your prescaler on APB2 bus
 *
 * input parameter: it take input from this list:
 * APB2_PRESCALER_NOT_DIVIDED
 * APB2_PRESCALER_CLOCK_DIVIDED_BY_2
 * APB2_PRESCALER_CLOCK_DIVIDED_BY_4
 * APB2_PRESCALER_CLOCK_DIVIDED_BY_8
 * APB2_PRESCALER_CLOCK_DIVIDED_BY_16
 *
 * it return error status whether its ok it return SYS_CLK_OK others is not ok
 */

RCC_enu_Error_State  RCC_enuControlPrescalerAPB2  (u32 Copy_u32APB2Prescaler);

#endif /* MCAL_RCC_H_ */
