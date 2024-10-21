#ifndef VTIMER_H
#define VTIMER_H

#include "signal.h"

// Periodo dos sinais de transito
#define MAIN_TIMEOUT 10000  // Semáforo principal
#define GREEN_TIMEOUT 3000  // Semáforo Secundário
#define YELLOW_TIMEOUT 2000 // Semáforo de pedestre

// Temporizadores
virtual_timer_t vt_main_green_t;
virtual_timer_t vt_main_yellow;
virtual_timer_t vt_sec_green;
virtual_timer_t vt_sec_yellow;
virtual_timer_t vt_walk_green;
virtual_timer_t vt_walk_yellow;


#endif
