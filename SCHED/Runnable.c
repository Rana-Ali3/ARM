/*
 * Runnable.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Rana
 */

#include "Runnables.h"
#include "SCHED.h"

extern void app1(void);
extern void app2(void);

runnable_t Runnables_List[ _Runnables_Num]={
		[App1]={.name="App1",
		        .periodicity=1000,
				.cb=&app1},
		[App2]={.name="App2",
				.periodicity=500,
				.cb=&app2},

};
