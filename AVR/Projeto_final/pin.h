#ifndef PIN_H
#define PIN_H

#include "AVRinlcudes.h"

//Sinais
    /* Principal */ 
        #define SEM_MAIN_GREEN    PB4 
        #define SEM_MAIN_YELLOW   PB3  
        #define SEM_MAIN_RED      PB2        
         

    /* Secundário */
        #define SEM_SEC_GREEN     PB1
        #define SEM_SEC_YELLOW    PB0  
        #define SEM_SEC_RED       PD7      
         

    /* Pedestre */
        #define SEM_WALK_GREEN    PD6 
        #define SEM_WALK_RED      PD5 

// Botões
        #define PUSH_BUTTON_SEC               PD4   //  Secundária
        #define PUSH_BUTTON_AMB_SEC           PD3   //  Ambulância na secundária
        #define PUSH_BUTTON_AMB_MAIN          PD2   //  Ambulância na primária
        #define PUSH_BUTTON_WALK              PD1   //  Pedestre


#endif
