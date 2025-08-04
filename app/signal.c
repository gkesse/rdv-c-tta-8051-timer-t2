#include "signal.h"

#define SIGNAL_ON (1)
#define SIGNAL_OFF (!SIGNAL_ON)
#define SIGNAL_PORT P1

sbit g_signal_pin = SIGNAL_PORT ^ 7;

static ubit g_signal_wave;
static ubit g_signal_modulation;

void signal_init()
{
	g_signal_modulation = SIGNAL_OFF;
	g_signal_wave = SIGNAL_OFF;
}

void signal_wave_on_update()
{
	g_signal_wave = SIGNAL_ON;
}

void signal_wave_off_update()
{
	g_signal_wave = SIGNAL_OFF;
}

void signal_modulation_update()
{
	g_signal_modulation = !g_signal_modulation;
	g_signal_pin = g_signal_wave & g_signal_modulation;
}
