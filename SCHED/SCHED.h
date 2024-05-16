/*
 * SCHED.h
 *
 *  Created on: Mar 31, 2024
 *      Author: Rana
 */

#ifndef SCHEDULAR_SCHED_H_
#define SCHEDULAR_SCHED_H_

#include "../LIB/STD_TYPES.h"

typedef void(*runnablecb_t)(void);

typedef struct{
	char*name;
	u32 periodicity;
	//u32 priority;
	runnablecb_t cb;
}runnable_t;

typedef enum{
	TASK_NOT_OK,
	TASK_OK
}SCHED_enu_Error_State;


//SCHED_enu_Error_State Sched_resistRunnable(runnable_t* r);
void sched_init(void);
void sched_start(void);
#endif /* SCHEDULAR_SCHED_H_ */
