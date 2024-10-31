#include "ch.h"
#include "hal.h"

// Declaração do mutex
static mutex_t myMutex;

// Função da thread 1
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
    (void)arg;
    chRegSetThreadName("Thread 1");

    while (true) {
        chMtxLock(&myMutex);  // Trava o mutex

        // Seção crítica - Acesso exclusivo
        palSetPad(IOPORT2, 5);  // Liga LED no pino PB5
        chThdSleepMilliseconds(200);
        palClearPad(IOPORT2, 5);  // Desliga LED
        chThdSleepMilliseconds(200);

        chMtxUnlock(&myMutex);  // Libera o mutex
        chThdSleepMilliseconds(100);  // Pausa antes da próxima iteração
    }
}

// Função da thread 2 
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
    (void)arg;
    chRegSetThreadName("Thread 2");

    while (true) {
        chMtxLock(&myMutex);  // Trava o mutex

        // Seção crítica - Acesso exclusivo
        palSetPad(IOPORT4, 7);  // Liga LED no pino PB4
        chThdSleepMilliseconds(1000);
        palClearPad(IOPORT4, 7);  // Desliga LED
        chThdSleepMilliseconds(1000);

        chMtxUnlock(&myMutex);  // Libera o mutex
        chThdSleepMilliseconds(100);  // Pausa antes da próxima iteração
    }
}

// Função da thread 2 - Usando chMtxTryLock(mutex_t *mp);
//static THD_WORKING_AREA(waThread2, 128);
//static THD_FUNCTION(Thread2, arg) {
//    (void)arg;
//    chRegSetThreadName("Thread 2");
//
//    while (true) {
//        if(chMtxTryLock(&myMutex)){
//            // Seção crítica - Acesso exclusivo
//            palSetPad(IOPORT4, 7);  // Liga LED no pino PB4
//            chThdSleepMilliseconds(1000);
//            palClearPad(IOPORT4, 7);  // Desliga LED
//            chThdSleepMilliseconds(1000);
//            chMtxUnlock(&myMutex);  // Libera o mutex
//        }
//        chThdSleepMilliseconds(100);  // Pausa antes da próxima iteração
//    }
//}

// Função principal (main)
int main(void) {
    // Inicializa o ChibiOS
    halInit();
    chSysInit();
    
    // Configuração dos pinos
    palSetPadMode(IOPORT4, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(IOPORT2, 5, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(IOPORT4, 7);
    palClearPad(IOPORT2, 5);

    // Inicializa o mutex
    chMtxObjectInit(&myMutex);

    // Cria as duas threads
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
    chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

    // Loop infinito para manter o sistema rodando
    while (true) {
        chThdSleepMilliseconds(1000);
    }
}


// Veja o primeiro exemplo (1_Blink_Led) para perceber a diferença em relação ao uso do mutex 
