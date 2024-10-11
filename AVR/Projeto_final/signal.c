#include "Sinais.h"

// Configuração dos pinos dos sinais de transito e botões da Ambulância (principal e secundária), carro na secundária e pedestre
void config_signals(){

 // Sinais - Pinos de saída
    /*  Semáforo principal  */
        palSetPadMode(PORTB, SEM_MAIN_GREEN,         PAL_MODE_OUTPUT_PUSHPULL);     //  Verde
        palSetPadMode(PORTB, SEM_MAIN_YELLOW,        PAL_MODE_OUTPUT_PUSHPULL);     //  Amarelo
        palSetPadMode(PORTB, SEM_MAIN_RED,           PAL_MODE_OUTPUT_PUSHPULL);     //  Vermelho
        /*  Saída LOW   */
        palClearPad(PORTB, SEM_MAIN_GREEN);
        palClearPad(PORTB, SEM_MAIN_YELLOW);
        palClearPad(PORTB, SEM_MAIN_RED);

    /*  Semáforo secundário  */
        palSetPadMode(PORTB, SEM_SEC_GREEN,          PAL_MODE_OUTPUT_PUSHPULL);     //  Verde
        palSetPadMode(PORTB, SEM_SEC_YELLOW,         PAL_MODE_OUTPUT_PUSHPULL);     //  Amarelo
        palSetPadMode(PORTD, SEM_SEC_RED,            PAL_MODE_OUTPUT_PUSHPULL);     //  Vermelho
        /*  Saída LOW   */
        palClearPad(PORTB, SEM_SEC_GREEN);
        palClearPad(PORTB, SEM_SEC_YELLOW);
        palClearPad(PORTD, SEM_SEC_RED);
    
    /*  Semáforo pedestre */
        palSetPadMode(PORTD, SEM_WALK_GREEN,         PAL_MODE_OUTPUT_PUSHPULL);     //  Verde
        palSetPadMode(PORTD, SEM_WALK_RED,           PAL_MODE_OUTPUT_PUSHPULL);     //  Vermelho
        /*  Saída LOW   */
        palClearPad(PORTD, SEM_WALK_GREEN);
        palClearPad(PORTD, SEM_WALK_RED);
        
 
 // Botões - Pinos de entrada
        palSetPadMode(PORTD, PUSH_BUTTON_AMB_MAIN, PAL_MODE_INPUT); //  Ambulância na principal
        palSetPadMode(PORTD, PUSH_BUTTON_AMB_SEC, PAL_MODE_INPUT);  //  Ambulância na secundária
        palSetPadMode(PORTD, PUSH_BUTTON_SEC, PAL_MODE_INPUT);      //  Carro na secundária
        palSetPadMode(PORTD, PUSH_BUTTON_WALK, PAL_MODE_INPUT);     //  Pedestre

}

// Controle dos sinais de trânsito

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


