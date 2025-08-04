#ifndef _tta_timer_t2_
#define _tta_timer_t2_

#include "header_reg52.h"

void tta_init();
void tta_start();
void tta_dispatch_tasks();
uchar tta_add_task(void (*pTask)(), const uint delay, const uint period);

#endif
