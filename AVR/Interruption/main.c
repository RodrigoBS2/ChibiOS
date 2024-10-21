
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

#include <stdint.h>

#include "ch.h"
#include "hal.h"

#define LED_PORT IOPORT4
#define LED_PIN 7

uint32_t n = 0;

void config_interruption(){
    EICRA |=  (1 << ISC01) | (1 << ISC00); // Ativando a interrupção INT0 para borda de subida.    
    EIMSK |= (1 << INT0);                  // Habilitando a interrupção INT0
    sei();                                 // HAbilitaa interrupção de maniera geral

}


ISR(INT0_vect) { 

    if (EICRA & (1 << ISC00)) {             // Se configurado para borda de subida
        EIMSK &= ~(1 << INT0);              // Desabilita a interrupção
        palWritePad(LED_PORT, LED_PIN, 1);  // LED ON
        while(n<5000){n++;}n=0;
        EICRA &= ~(1 << ISC00);             // Configura para borda de descida
        EIMSK |= (1 << INT0);               // Habilita a interrupção
    } else {
        EIMSK &= ~(1 << INT0);              // Desabilita a interrupção
        palWritePad(LED_PORT, LED_PIN, 0);  // LED OFF
        while(n<5000){n++;}n=0;        
        EICRA |= (1 << ISC00);              // Configura para borda de subida
        EIMSK |= (1 << INT0);               // Habilita a interrupção       
    }
  
     
}

/*
 * Application main function.
 */
int main(void) {

    halInit();
    chSysInit();
    config_interruption();
    palSetPadMode(LED_PORT, 2, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(LED_PORT, LED_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(LED_PORT, LED_PIN); 
    

    while(1){
        chThdSleepMilliseconds(500);
    }
 
}


