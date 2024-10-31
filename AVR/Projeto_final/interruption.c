#include "interruption.h"


void config_interruption(){
/*  Habilitando as interrupções da ambulância na principal (INT0) e ambulância na secundária (INT1) para borda de subida. */
    EICRA |=  (1 << ISC11) (1 << ISC10) | (1 << ISC01) | (1 << ISC00);      // Configurando as interrupções como borda de subida
    EIMSK |= (1 << INT1) | (1 << INT0);                                     // Habilitando as interrupções

/*  Habilitando as interrupções para os sinais de pedestre (PCINT20) e secundária (PCINT17) */
    PCICR |= (1 << PCIE2);   // Habilitar interrupção de PCINT para o grupo PCINT2 (PCINT16 a PCINT23)
    PCMSK2 |= (1 << PCINT20) | (1 << PCINT17); // Habilitar interrupções para PCINT20 a PCINT17 (pedestre e secundária)


    sei();  // Habilita interrupção global;
}




/*  Interrupção da ambulânica na principal */
ISR(INT0_vect) { 
    uint16_t n =0;
    if (EICRA & (1 << ISC00)) {             // Se configurado para borda de subida
        //set_event();                      // Atualiza o buffer;
        EIMSK &= ~(1 << INT0);              // Desabilita a interrupção
        while(n<5000){n++;}n=0;             // Delay
        EICRA &= ~(1 << ISC00);             // Configura para borda de descida
        EIMSK |= (1 << INT0);               // Habilita a interrupção
    } else {
        //set_event();                      // Atualiza o buffer;
        EIMSK &= ~(1 << INT0);              // Desabilita a interrupção
        while(n<5000){n++;}n=0;             // Delay
        EICRA |= (1 << ISC00);              // Configura para borda de subida
        EIMSK |= (1 << INT0);               // Habilita a interrupção       
    }
  
     
}

/*  Interrupção da ambulânica na secundária */
ISR(INT1_vect){
    uint16_t n =0;
    if (EICRA & (1 << ISC10)) {             // Se configurado para borda de subida
        //set_event();        
        EIMSK &= ~(1 << INT1);              // Desabilita a interrupção
        while(n<5000){n++;}n=0;             // Delay
        EICRA &= ~(1 << ISC10);             // Configura para borda de descida
        EIMSK |= (1 << INT1);               // Habilita a interrupção
    } else {
        //set_event();
        EIMSK &= ~(1 << INT1);              // Desabilita a interrupção
        while(n<5000){n++;}n=0;             // Delay
        EICRA |= (1 << ISC10);              // Configura para borda de subida
        EIMSK |= (1 << INT1);               // Habilita a interrupção       
    }
}

/*  Interrupção para os sinais de pedestres e carro na secundária   */
ISR(PCINT2_vect){
    uint16_t n = 0;
    // Os botões estão conectados aos pinos PD1 e PD4 (PCINT17 e PCINT20) que são PUSH_BUTTON_WALK e PUSH_BUTTON_SEC respectivamente
    // Captura o estado dos botões e armazena na variável button_states
    button_states = PIND & ((1 << PD1) | (1 << PD4));
    while(n<5000){n++;}n=0;
    // Atualiza o buffer (pedestre e secundário)
    if(!(button_state & PD1)){
        //set_event();        
    }
    if(!(button_state & PD4)){
        //set_event();
    }
    // A variável button_states vai conter 0 nas posições dos botões pressionados (porque há pull-up)
}

