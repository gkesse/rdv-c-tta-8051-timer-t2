#include "tta_timer_t2.h"
#include "signal.h"
#include "config.h"

void main()
{
	tta_init();
	signal_init();
	tta_add_task(signal_wave_on_update, 0, config_signal_wave_period);
	tta_add_task(signal_wave_off_update, config_signal_wave_on_period, config_signal_wave_period);
	tta_add_task(signal_modulation_update, 0, config_signal_modulation_on_period);
	tta_start();

	while (true)
	{
		tta_dispatch_tasks();
	}
}
