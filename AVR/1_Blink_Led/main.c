#include "ch.h"
#include "hal.h"

// Função da thread 1
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
    (void)arg;
    chRegSetThreadName("Thread 1");

    while (true) {
        palSetPad(IOPORT2, 5);  // Liga LED no pino PB5
        chThdSleepMilliseconds(200);
        palClearPad(IOPORT2, 5);  // Desliga LED
        chThdSleepMilliseconds(200);
    }
}

// Função da thread 2
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
    (void)arg;
    chRegSetThreadName("Thread 2");

    while (true) {
        palSetPad(IOPORT4, 7);  // Liga LED no pino PD7
        chThdSleepMilliseconds(1000);
        palClearPad(IOPORT4, 7);  // Desliga LED
        chThdSleepMilliseconds(1000);
    }
}

// Função principal (main)
int main(void) {

    // Inicializa o ChibiOS
    halInit();
    chSysInit();
    
    // Configuração dos pinos
    palSetPadMode(IOPORT4, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(IOPORT2, 5, PAL_MODE_OUTPUT_PUSHPULL);

    // Cria as duas threads
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
    chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

    // Loop infinito para manter o sistema rodando
    while (true) {
        chThdSleepMilliseconds(1000);
    }
}


/*
     O "chThdSleepMilliseconds(1000);" no loop while (true), dentro do "int main(void)" uma prática comum em sistemas embarcados 
     para garantir que a aplicação seja eficiente em termos de energia, e para permitir que o RTOS 
     gerencie o tempo de execução das threads de forma eficaz.
*/
