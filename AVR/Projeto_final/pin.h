#ifndef PIN_H
#define PIN_H


#include "AVRincludes.h"

//Sinais
    /* Principal */ 
        #define SEM_MAIN_GREEN    4 
        #define SEM_MAIN_YELLOW   3  
        #define SEM_MAIN_RED      2        
         

    /* Secundário */
        #define SEM_SEC_GREEN     1
        #define SEM_SEC_YELLOW    0  
        #define SEM_SEC_RED       7      
         

    /* Pedestre */
        #define SEM_WALK_GREEN    6 
        #define SEM_WALK_RED      5 

// Botões
        #define PUSH_BUTTON_SEC               4   //  Secundária
        #define PUSH_BUTTON_AMB_SEC           3   //  Ambulância na secundária
        #define PUSH_BUTTON_AMB_MAIN          2   //  Ambulância na primária
        #define PUSH_BUTTON_WALK              1   //  Pedestre


#endif
