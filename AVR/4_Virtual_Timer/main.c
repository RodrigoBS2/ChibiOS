#include <avr/io.h>
#include "ch.h"
#include "hal.h"

#define LED_PORT IOPORT4
#define LED_PIN 7

/*  O código a baixo mostra um exemplo de usar o timer virtual para fazer o led piscar durante alguns segundos. */

char n = 0;

static virtual_timer_t led_vt;
                 
/*
 * LED timer callback.
 */
static void led_cb(void *arg) {
 
    palTogglePad(LED_PORT, LED_PIN);    //  Muda o estado lógico do LED 
    n++;                                //  Soma mais um na variável n
    
    /* Processo para redefinir o temporizador */
    chSysLockFromISR();                                 // Desabilita interrupções temporariamente, protegendo o código crítico de concorrência.
    chVTSetI(&led_vt, TIME_MS2I(1000), led_cb, NULL);   // Redefine o temporizador para chamar a função led_cb após 1 segundo.
    chSysUnlockFromISR();                               // Reabilita interrupções
}
 
/*
 * Application main function.
 */
int main(void) {

    halInit();
    chSysInit();

    palSetPadMode(LED_PORT, LED_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(LED_PORT, LED_PIN);

     /* LED timer initialization.*/
    chVTObjectInit(&led_vt);    // Inicializa o temporizador virtual.
 
    /* Starting blinker.*/
    chVTSet(&led_vt, TIME_MS2I(1000), led_cb, NULL);    // Define o temporizador para chamar a função led_cb após 1 segundo.
    
    while(1){
        if(n>3){
            /* Stopping blinker.*/
            chVTReset(&led_vt);
            palClearPad(LED_PORT, LED_PIN);
            break;
        }
    chThdSleepMilliseconds(500);
    
    }

    
 
}


