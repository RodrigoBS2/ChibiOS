*****************************************************************************
**  Porjeto Final - Sinal de transito  **
*****************************************************************************

Microcontrolador ATmega328P

Objetos e seus pinos (Pinos.h):

    1) Principal:
        - Semáforo principal verde:       SEM_MAIN_GREEN    PB4 (Pino 12)
        - Semáforo principal amarelo:     SEM_MAIN_YELLOW   PB3 (Pino 11) 
        - Semáforo principal vermelho:    SEM_MAIN_RED      PB2 (Pino 10)        
        - Ambulância principal:           AMB_MAIN          PD2 (INT0)

    2) Secundário:
        - Semáforo secundário verde:       SEM_SEC_GREEN    PB1 (Pino 9)
        - Semáforo secundário amarelo:     SEM_SEC_YELLOW   PB0 (Pino 8) 
        - Semáforo secundário vermelho:    SEM_SEC_RED      PD7 (Pino 7)     
        - Ambulância secundário:           AMB_SEC          PD3 (INT1)

    3) Pedestre:
        - Semáforo pedestre verde:       SEM_WALKER_GREEN      PD6 (Pino 6)
        - Semáforo principal vermelho:    SEM_WALKER_RED       PD5 (Pino 5)

       
        
Funções para os semáforos (Sinais.h):

    1) Principal:
        - void Led_Green_Main(bool state);
        - void Led_Yellow_Main(bool state);
        - void Led_Red_Main(bool state);

    2) Secundário:
        - void Led_Green_Secundary(bool state);
        - void Led_Yellow_Secundary(bool state);
        - void Led_Red_Secundary(bool state);        

    3) Principal:
        - void Led_Green_Walker(bool state);
        - void Led_Yellow_Walker(bool state);
        - void Led_Red_Walker(bool state);
