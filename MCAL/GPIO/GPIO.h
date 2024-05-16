/*
 * GPIO.h
 *
 *  Created on: Feb 24, 2024
 *      Author: Rana
 */

#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_

#include"../LIB/STD_TYPES.h"

/****************************** Defines ******************************/

/********* GPOI PORTS *********/
#define GPIO_POART_A 	(void*)0x40020000
#define GPIO_POART_B 	(void*)0x40020400
#define GPIO_POART_C 	(void*)0x40020800
#define GPIO_POART_D 	(void*)0x40020C00
#define GPIO_POART_E 	(void*)0x40021000

/******** GPIO_PINS **********/
#define MAX_NUM_OF_PIN 15

#define GPIO_PIN_0    0
#define GPIO_PIN_1    1
#define GPIO_PIN_2    2
#define GPIO_PIN_3    3
#define GPIO_PIN_4    4
#define GPIO_PIN_5    5
#define GPIO_PIN_6    6
#define GPIO_PIN_7    7
#define GPIO_PIN_8    8
#define GPIO_PIN_9    9
#define GPIO_PIN_10   10
#define GPIO_PIN_11   11
#define GPIO_PIN_12   12
#define GPIO_PIN_13   13
#define GPIO_PIN_14   14
#define GPIO_PIN_15   15

/******** speed values **********/
#define GPIO_LOW_SPEED           0X0
#define GPIO_MEDIUM_SPEED        0X1
#define GPIO_HIGH_SPEED          0X2
#define GPIO_VERY_HIGH_SPEED     0X3

/********* Modes of pins *********/
#define MODE_INPUT_FLOATING  									 0X0
#define MODE_INPUT_PULL_UP  									 0X1
#define MODE_INPUT_PULL_DOWN  									 0X2

#define MODE_OUTPUT_PUSH_PULL									 0X10
#define MODE_OUTPUT_PUSH_PULL_PULL_UP							 0X11
#define MODE_OUTPUT_PUSH_PULL_PULL_DOWN							 0X12

#define MODE_OUTPUT_OPEN_DRAIN									 0X20
#define MODE_OUTPUT_OPEN_DRAIN_PULL_UP							 0X21
#define MODE_OUTPUT_OPEN_DRAIN_PULL_DOWN				  		 0X22

#define MODE_ALTERNATIVE_FUNCTION_PUSH_PULL           			 0X30
#define MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_UP              0X31
#define MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_DOWN            0X32
#define MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN           			 0X40
#define MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_UP             0X41
#define MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_DOWN           0X42

#define MODE_ANALOG 				                  			 0X50

/********* States of pins *********/
#define ON_STATE      1
#define OFF_STATE     0

/****************************** Types *******************************/

/************* enum to represent error ************************/
typedef enum{
	GPIO_NOT_OK,
	GPIO_WRONG_PORT,
	GPIO_WRONG_PIN,
	GPIO_WRONG_SPEED_VALUE,
	GPIO_INVALID_MODE,
	GPIO_INVALID_VALUE,
	GPIO_OK
}GPIO_enu_Error_State;

typedef struct{
	void* port;
	u32 pin;
	u32 speed;
	u32 mode;

}GPIO_PIN_PARAM;


/****************************** API *******************************/

/*This function to init set the selected port ,pin ,speed and mode  Pin in GPIO
 *
 * It take input as pointer to GPIO_PIN_PARAM struct,you must define the struct element first
 * before passing it to the function,you must define its:
 * Port from this choice:(GPIO_POART_A,GPIO_POART_B,GPIO_POART_C,GPIO_POART_D,GPIO_POART_E)
 * Pin from this choice:(GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,...,GPIO_PIN_15)
 * Speed from this choice:(GPIO_LOW_SPEED, GPIO_MEDIUM_SPEED,GPIO_HIGH_SPEED,GPIO_VERY_HIGH_SPEED)
 * Mode from this choice:(MODE_INPUT_FLOATING,MODE_INPUT_PULL_UP,MODE_INPUT_PULL_DOWN,MODE_OUTPUT_PUSH_PULL,MODE_OUTPUT_PUSH_PULL_PULL_UP,MODE_ANALOG
 * MODE_OUTPUT_PUSH_PULL_PULL_DOWN,MODE_OUTPUT_OPEN_DRAIN, MODE_OUTPUT_OPEN_DRAIN_PULL_UP,MODE_OUTPUT_OPEN_DRAIN_PULL_DOWN
 * MODE_ALTERNATIVE_FUNCTION_PUSH_PULL,MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_UP,MODE_ALTERNATIVE_FUNCTION_PUSH_PULL_PULL_DOWN
 * MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN,MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_UP,MODE_ALTERNATIVE_FUNCTION_OPEN_DRAIN_PULL_DOWN)
 *
 * it return error status to represent if it is true parameter(GPIO_OK) or invalid parameter */

GPIO_enu_Error_State GPIO_init(GPIO_PIN_PARAM *GPIO_PIN);

/*This function to Get the value of a pin in GPIO is it ON (1) or OFF(0)
 *
 * It take input of pins wanted to get its status it take:
 * Port from this Choice:(GPIO_POART_A,GPIO_POART_B,GPIO_POART_C,GPIO_POART_D,GPIO_POART_E)
 * Pin from this choice:(GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,...,GPIO_PIN_15)
 * and the third input is pointer to represent value gitted from this pin you pass any variable want to
 * represent gitted value of pin on it
 *
 * It return error status to represent is it ok or not*/

GPIO_enu_Error_State GPIO_GetPinValue(void* GPIO_Port,u32 GPIO_Pin,u8* GPIO_PinValueGitted);

/*This function to set a value to a pin in GPIO is it ON_STATE (1) or OFF_STATE(0)
 *
 * It take input of pins wanted to set a value to it :
 * Port from this Choice:(GPIO_POART_A,GPIO_POART_B,GPIO_POART_C,GPIO_POART_D,GPIO_POART_E)
 * Pin from this choice:(GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,...,GPIO_PIN_15)
 * Value you want to set to this pin it take choice from:(ON_STATE,OFF_STATE)
 *
 * It return error status to represent is it ok or not*/

GPIO_enu_Error_State GPIO_SetPinValue(void* GPIO_Port,u32 GPIO_Pin,u8 GPIO_PinValue);


#endif /* MCAL_GPIO_H_ */
