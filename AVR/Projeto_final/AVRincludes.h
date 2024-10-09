#ifndef AVRINCLUDES_H
#define AVRINCLUDES_H

#include <avr/io.h>

/*  Os próximos dois includes são necessários quando se usa interrupções */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

/*  O include a seguir será necessário para fazer manipulação de bits nos registradores*/
#include <stdint.h>

/*  ChibiOS */
#include "ch.h"
#include "hal.h"

typdef struct{

    bool walker = false;
    bool secundary = false;
    bool ambulance_main = false;
    bool ambulance_secundary = false;

}BUFFER;

typdef enum{

    /* Principal */
    MAIN_STATE_MAIN_G_T = 0, MAIN_STATE_MAIN_G, 

    /* Secundário */    
    SEC_STATE_MAIN_Y_T, SEC_STATE_SEC_G_T, SEC_STATE_Y_T,

    /* Pedestres */
    

}STATE;

#endif
