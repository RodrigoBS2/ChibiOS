#ifndef MAIN_H
#define MAIN_H


#include "AVRincludes.h"
#include "pin.h"
#include "signal.h"
#include "state.h"
#include "vtimer.h"

/* Variáveis globais    */
    // Buffer - eventos
    extern volatile bool walker = false;
    extern volatile bool secondary = false;
    extern volatile bool amb_secondary = false;
    extern volatile bool amb_main = false;

    // Estado atual  
    extern volatile state_t current_state = main_st_main_green_t;



event_t get_event();

int main(void);




#endif
