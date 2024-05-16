/*
 * SCHED.c
 *
 *  Created on: Mar 31, 2024
 *      Author: Rana
 */

#include "SCHED.h"
#include "../MCAL/SYSTICK/SYSTICK.h"
#include "Runnables.h"

//#define MAX 2
#define TICK_TIME_MS  10


extern runnable_t Runnables_List[ _Runnables_Num];
static u32 Pending_ticks=0;

typedef struct{
	runnable_t*runnable;
   // u32 remainTimeMs;
}runnableInfo;

//static runnableInfo rInfo[MAX];

void tick_cb(void)
{
	Pending_ticks++;
}
static void Sched_Call_Back(void){
   u32 i;
   static u32 time=0;
   for(i=0;i<_Runnables_Num;i++)
   {
	   if(time%Runnables_List[i].periodicity==0)
	   //if(rInfo[i].remainTimeMs==0)
	   {
		   if(Runnables_List[i].cb)
		   {
			   Runnables_List[i].cb;
		   }
		  // rInfo[i].remainTimeMs=rInfo[i].runnable->periodicity;
	   }
	  // rInfo[i].remainTimeMs--;
   }
   time+=TICK_TIME_MS;
}

void sched_init(void)
{
	SYSTICK_setTimeMS(TICK_TIME_MS);
	Set_Callback(tick_cb);

}

void sched_start(void)
{
	SYSTICK_start(CLK_SOURCE_AHB);
	while(1)
	{
		if(Pending_ticks)
		{
			Pending_ticks--;
			Sched_Call_Back();
		}
	}
}

/*SCHED_enu_Error_State Sched_resistRunnable(runnable_t* r)
{
	SCHED_enu_Error_State sched_ret_error_state=TASK_OK;
	if(r&&(rInfo[r->priority].runnable==NULL))
	{
		rInfo[r->priority].runnable=r;
		rInfo[r->priority].remainTimeMs=r->delay_ms;
	}
	else
	{
		sched_ret_error_state=TASK_NOT_OK;
	}
	return sched_ret_error_state;
}*/

