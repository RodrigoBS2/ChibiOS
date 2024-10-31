#include "ch.h"
#include "hal.h"

// Mutex e variável de condição
static mutex_t mutex;
static condition_variable_t cond;

// Thread 1: Espera pela condição e alterna o LED
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
    (void)arg;
    msg_t result;  // Variável para armazenar o retorno

    while (true) {
        chMtxLock(&mutex);  // Trava o mutex

        // Aguardando até que Thread2 sinalize
        result = chCondWait(&cond);

        if (result == MSG_OK) {  // Se sinalizado corretamente
            palTogglePad(IOPORT4, 7);  // Alterna o LED
        }

        chMtxUnlock(&mutex);  // Libera o mutex
    }
}

// Thread 2: Sinaliza a condição após 1 segundo
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
    (void)arg;

    while (true) {
        chThdSleepMilliseconds(1000);  // Aguarda 1 segundo

        chMtxLock(&mutex);  // Trava o mutex
        chCondSignal(&cond);  // Sinaliza a condição para Thread1
        chMtxUnlock(&mutex);  // Libera o mutex
    }
}

// Função principal (main)
int main(void) {
    halInit();    // Inicializa o HAL (Hardware Abstraction Layer)
    chSysInit();  // Inicializa o sistema ChibiOS

    // Configuração dos pinos
    palSetPadMode(IOPORT4, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(IOPORT4, 7);

    // Inicializa o mutex e a variável de condição
    chMtxObjectInit(&mutex);
    chCondObjectInit(&cond);

    // Cria as threads
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
    chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

    while (true) {
        chThdSleepMilliseconds(1000);  // Mantém o sistema rodando
    }
}

