#include "signal.h"

// Configuração dos pinos dos sinais de transito e botões da Ambulância (principal e secundária), carro na secundária e pedestre
void config_signals(){

 // Sinais - Pinos de saída
    /*  Semáforo principal  */
        palSetPadMode(IOPORT2, SEM_MAIN_GREEN,         PAL_MODE_OUTPUT_PUSHPULL);     //  Verde
        palSetPadMode(IOPORT2, SEM_MAIN_YELLOW,        PAL_MODE_OUTPUT_PUSHPULL);     //  Amarelo
        palSetPadMode(IOPORT2, SEM_MAIN_RED,           PAL_MODE_OUTPUT_PUSHPULL);     //  Vermelho
        /*  Saída LOW   */
        palClearPad(IOPORT2, SEM_MAIN_GREEN);
        palClearPad(IOPORT2, SEM_MAIN_YELLOW);
        palClearPad(IOPORT2, SEM_MAIN_RED);

    /*  Semáforo secundário  */
        palSetPadMode(IOPORT2, SEM_SEC_GREEN,          PAL_MODE_OUTPUT_PUSHPULL);     //  Verde
        palSetPadMode(IOPORT2, SEM_SEC_YELLOW,         PAL_MODE_OUTPUT_PUSHPULL);     //  Amarelo
        palSetPadMode(IOPORT4, SEM_SEC_RED,            PAL_MODE_OUTPUT_PUSHPULL);     //  Vermelho
        /*  Saída LOW   */
        palClearPad(IOPORT2, SEM_SEC_GREEN);
        palClearPad(IOPORT2, SEM_SEC_YELLOW);
        palClearPad(IOPORT4, SEM_SEC_RED);
    
    /*  Semáforo pedestre */
        palSetPadMode(IOPORT4, SEM_WALK_GREEN,         PAL_MODE_OUTPUT_PUSHPULL);     //  Verde
        palSetPadMode(IOPORT4, SEM_WALK_RED,           PAL_MODE_OUTPUT_PUSHPULL);     //  Vermelho
        /*  Saída LOW   */
        palClearPad(IOPORT4, SEM_WALK_GREEN);
        palClearPad(IOPORT4, SEM_WALK_RED);
        
 
 // Botões - Pinos de entrada
        palSetPadMode(IOPORT4, PUSH_BUTTON_AMB_MAIN, PAL_MODE_INPUT_PULLDOWN); //  Ambulância na principal
        palSetPadMode(IOPORT4, PUSH_BUTTON_AMB_SEC, PAL_MODE_INPUT_PULLDOWN);  //  Ambulância na secundária
        palSetPadMode(IOPORT4, PUSH_BUTTON_SEC, PAL_MODE_INPUT_PULLUP);      //  Carro na secundária
        palSetPadMode(IOPORT4, PUSH_BUTTON_WALK, PAL_MODE_INPUT_PULLUP);     //  Pedestre

}

// Controle dos sinais de trânsito

    /* Semáforo principal */
        void Led_Green_Main(bool state){
            if(state == true){
                palWritePad(IOPORT2, SEM_MAIN_GREEN, 1);                
            }
            else{
                palWritePad(IOPORT2, SEM_MAIN_GREEN, 0);
            }
        }


        void Led_Yellow_Main(bool state){
            if(state == true){
                palWritePad(IOPORT2, SEM_MAIN_YELLOW, 1);                
            }
            else{
                palWritePad(IOPORT2, SEM_MAIN_YELLOW, 0);
            }
        }

        void Led_Red_Main(bool state){
            if(state == true){
                palWritePad(IOPORT2, SEM_MAIN_RED, 1);                
            }
            else{
                palWritePad(IOPORT2, SEM_MAIN_RED, 0);
            }
        }

    /* Semáforo Secundário */
        void Led_Green_Secondary(bool state){
            if(state == true){
                palWritePad(IOPORT2, SEM_SEC_GREEN, 1);                
            }
            else{
                palWritePad(IOPORT2, SEM_SEC_GREEN, 0);
            }
        }

        void Led_Yellow_Secondary(bool state){
            if(state == true){
                palWritePad(IOPORT2, SEM_SEC_YELLOW, 1);                
            }
            else{
                palWritePad(IOPORT2, SEM_SEC_YELLOW, 0);
            }
        }

        void Led_Red_Secondary(bool state){
            if(state == true){
                palWritePad(IOPORT4, SEM_SEC_RED, 1);                
            }
            else{
                palWritePad(IOPORT4, SEM_SEC_RED, 0);
            }
        }        

    /* Semáforo de pedestre */
        void Led_Green_Walker(bool state){
            if(state == true){
                palWritePad(IOPORT4, SEM_WALK_GREEN, 1);                
            }
            else{
                palWritePad(IOPORT4, SEM_WALK_GREEN, 0);
            }
        } 

        void Led_Blink_Walker(bool state){
            
        }

        void Led_Red_Walker(bool state){
            if(state == true){
                palWritePad(IOPORT4, SEM_WALK_RED, 1);                
            }
            else{
                palWritePad(IOPORT4, SEM_WALK_RED, 0);
            }
        } 


