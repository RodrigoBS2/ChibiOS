#ifndef SIGNAL_H
#define SIGNAL_H

#include "AVRincludes.h"
#include "Pinos.h"

#define ON true
#define OFF false

// Periodo dos sinais de transito
#define MAIN_TIMEOUT 10000  // Semáforo principal
#define GREEN_TIMEOUT 3000  // Semáforo Secundário
#define YELLOW_TIMEOUT 2000 // Semáforo de pedestre

// Configuração dos pinos dos sinais de transito
    void config_signals();

// Controle dos sinais de trânsito

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
