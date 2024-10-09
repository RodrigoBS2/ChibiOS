#include "Sinais.h"

/* Semáforo principal */

void Led_Green_Main(bool state){

    if(state == true){
        palWritePad(PORTB, SEM_MAIN_GREEN, 1);                
    }
    else{
        palWritePad(PORTB, SEM_MAIN_GREEN, 0);
    }

}


void Led_Yellow_Main(bool state){

    if(state == true){
        palWritePad(PORTB, SEM_MAIN_YELLOW, 1);                
    }
    else{
        palWritePad(PORTB, SEM_MAIN_YELLOW, 0);
    }

}

void Led_Red_Main(bool state){

    if(state == true){
        palWritePad(PORTB, SEM_MAIN_RED, 1);                
    }
    else{
        palWritePad(PORTB, SEM_MAIN_RED, 0);
    }

}
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

/* Semáforo Secundário */

void Led_Green_Secundary(bool state){

    if(state == true){
        palWritePad(PORTB, SEM_SEC_GREEN, 1);                
    }
    else{
        palWritePad(PORTB, SEM_SEC_GREEN, 0);
    }

}

void Led_Yellow_Secundary(bool state){

    if(state == true){
        palWritePad(PORTB, SEM_SEC_YELLOW, 1);                
    }
    else{
        palWritePad(PORTB, SEM_SEC_YELLOW, 0);
    }

}
void Led_Red_Secundary(bool state){

    if(state == true){
        palWritePad(PORTD, SEM_SEC_RED, 1);                
    }
    else{
        palWritePad(PORTD, SEM_SEC_RED, 0);
    }

}        
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

/* Semáforo de pedestre */
void Led_Green_Walker(bool state){

    if(state == true){
        palWritePad(PORTD, SEM_WALK_GREEN, 1);                
    }
    else{
        palWritePad(PORTD, SEM_WALK_GREEN, 0);
    }

} 
void Led_Red_Walker(bool state){

    if(state == true){
        palWritePad(PORTD, SEM_WALK_RED, 1);                
    }
    else{
        palWritePad(PORTD, SEM_WALK_RED, 0);
    }

} 


