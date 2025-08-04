#include "tta_timer_t2.h"
#include "config.h"

#define TTA_TASK_MAX 						(8)
#define TTA_INTERRUPT_TIMER_T2	5
#define TTA_TICK_PORT						P2

#define TTA_PRELOAD_TIME_MS(time_ms) \
				(65536 - ((config_osc_freq * time_ms) / (config_osc_per_inst * 1000)))

typedef struct _sTask
{
    void (*pTask)();
    uint delay;
    uint period;
    uchar run_me;
} sTask;

sbit g_tta_tick_pin = TTA_TICK_PORT^7;
static sTask g_tta_task_queue[TTA_TASK_MAX];

static void tta_go_to_sleep();
static void tta_delete_task(const uchar index);

static void tta_go_to_sleep()
{
	PCON |= 0x01;
}

static void tta_delete_task(const uchar index)
{
	g_tta_task_queue[index].pTask 	= 0x0000;
	g_tta_task_queue[index].delay 	= 0;
	g_tta_task_queue[index].period 	= 0;
	g_tta_task_queue[index].run_me 	= 0;
}

void on_tta_update_tasks() interrupt TTA_INTERRUPT_TIMER_T2 
{
	uchar index;
	TF2 = 0;

	for(index = 0; index < TTA_TASK_MAX; index++)
	{
		if(g_tta_task_queue[index].pTask != 0)
		{
			if(g_tta_task_queue[index].delay == 0)
			{
				g_tta_task_queue[index].run_me += 1;
				if(g_tta_task_queue[index].period != 0)
				{
					g_tta_task_queue[index].delay = g_tta_task_queue[index].period;
				}
			}
			else
			{
				g_tta_task_queue[index].delay -= 1;
			}
		}
	}
	
  if(config_tta_tick_pin_on)
	{
		g_tta_tick_pin = !g_tta_tick_pin;
	}
}

void tta_init()
{
	uchar index;
	volatile uint PRELOAD = TTA_PRELOAD_TIME_MS(config_tta_tick_ms);

	for(index = 0; index < TTA_TASK_MAX; index++)
	{
			tta_delete_task(index);
	}
	
	T2CON = 0x00; 
	TH2 = PRELOAD >> 8; 
	RCAP2H = PRELOAD >> 8; 
	TL2 = PRELOAD; 
	RCAP2L = PRELOAD;
	ET2 = 1;
	TR2 = 1;
}

void tta_start()
{
	EA = 1;
}

void tta_dispatch_tasks()
{
	uchar index;
		
	for(index = 0; index < TTA_TASK_MAX; index++)
	{
		if(g_tta_task_queue[index].run_me > 0)
		{
			(*g_tta_task_queue[index].pTask)();
			g_tta_task_queue[index].run_me -= 1;
			
			if(g_tta_task_queue[index].period == 0)
			{
				tta_delete_task(index);
			}
		}
	}
	tta_go_to_sleep();
}

uchar tta_add_task(void (*pTask)(), const uint delay, const uint period)
{
	uchar index = 0;
	while((g_tta_task_queue[index].pTask != 0) && (index < TTA_TASK_MAX)) index++;
	if(index == TTA_TASK_MAX) return config_tta_index_error;
	g_tta_task_queue[index].pTask = pTask;
	g_tta_task_queue[index].delay = delay;
	g_tta_task_queue[index].period = period;
	g_tta_task_queue[index].run_me = 0;
	return index;
}
