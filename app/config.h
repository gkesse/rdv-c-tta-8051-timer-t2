#ifndef _config_
#define _config_

#include "header_reg52.h"

// oscillator
#define config_osc_freq (11059200) // Hz
#define config_osc_per_inst (12)

// tta
#define config_tta_tick_ms (1) // ms
#define config_tta_period_min_ms (2 * config_tta_tick_ms) // ms
#define config_tta_tick_pin_on (true)
#define config_tta_index_error (255)

// uart
#define config_uart_update_period_ms (50) //ms
#define config_uart_update_period (config_uart_update_period_ms / config_tta_tick_ms)

// signal
#define config_signal_wave_ms (1000)    // ms
#define config_signal_modulation_on_period_ms (50) // ticks
#define config_signal_wave_period (config_signal_wave_ms / config_tta_tick_ms)
#define config_signal_wave_on_per_period (0.5)
#define config_signal_wave_on_period (config_signal_wave_on_per_period * config_signal_wave_period)
#define config_signal_modulation_on_period ((config_signal_modulation_on_period_ms / config_tta_tick_ms) - 1)

#endif
