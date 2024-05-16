/*
 * EXTI_CFG.h
 *
 *  Created on: May 9, 2024
 *      Author: Rana
 */

#ifndef MCAL_EXTI_EXTI_CFG_H_
#define MCAL_EXTI_EXTI_CFG_H_

/*Put from LINE0 till LINE15*/
#define LINE0  0
#define LINE1  1
#define LINE2  2
#define LINE4  4
#define LINE5  5
#define LINE6  6
#define LINE7  7
#define LINE8  8
#define LINE9  9
#define LINE10 10
#define LINE11 11
#define LINE12 12
#define LINE13 13
#define LINE14 14
#define LINE15 15

/*CHOOSE FROM LINE0 ill LINE15*/
#define EXTI_LINE    LINE0

#define RISING_EDGE      0
#define FALLING_EDGE     1
#define ON_CHANGE_EDGE   2

#define EXTI_MODE    FALLING_EDGE


/****************/
#define PORTA_MAP  0
#define PORTB_MAP  1
#define PORTC_MAP  2
#define PORTD_MAP  3

#endif /* MCAL_EXTI_EXTI_CFG_H_ */
