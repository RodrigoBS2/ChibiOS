#ifndef SIGNAL_H
#define SIGNAL_H

#include "AVRincludes.h"
#include "pin.h"

#define ON true
#define OFF false


// Configuração dos pinos dos sinais de transito
    void config_signals();

// Controle dos sinais de trânsito

    /* Semáforo principal */
        void Led_Green_Main(bool state);    
        void Led_Yellow_Main(bool state);
        void Led_Red_Main(bool state);

    /* Semáforo Secundário */
        void Led_Green_Secondary(bool state);
        void Led_Yellow_Secondary(bool state);
        void Led_Red_Secondary(bool state);        

    /* Semáforo de pedestre */
        void Led_Green_Walker(bool state);
        void Led_Blink_Walker(bool state);
        void Led_Red_Walker(bool state);


#endif
