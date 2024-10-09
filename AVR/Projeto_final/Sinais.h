#ifndef SINAIS_H
#define SINAIS_H

#include "AVRincludes.h"
#include "Pinos.h"

/* Semáforo principal */
void Led_Green_Main(bool state);    
void Led_Yellow_Main(bool state);
void Led_Red_Main(bool state);

/* Semáforo Secundário */
void Led_Green_Secundary(bool state);
void Led_Yellow_Secundary(bool state);
void Led_Red_Secundary(bool state);        

/* Semáforo de pedestre */
void Led_Green_Walker(bool state);
void Led_Red_Walker(bool state);


#endif
