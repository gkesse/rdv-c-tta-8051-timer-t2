#include "tick_delay.h"

#define TICK_PORT		P1

sbit g_tick_pin = TICK_PORT^7;

void tick_delay_update()
{
	g_tick_pin = !g_tick_pin;
}
