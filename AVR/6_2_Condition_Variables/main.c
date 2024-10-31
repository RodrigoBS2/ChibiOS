#include "ch.h"
#include "hal.h"

// Mutex e variáveis de condição
static mutex_t mutex;
static condition_variable_t cond1;
static condition_variable_t cond2;
static condition_variable_t cond3;
static bool b = true;

// Thread 1: Alterna o LED1 e sinaliza a Thread 2
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
    (void)arg;

    while (true) {
        chMtxLock(&mutex);

        msg_t result = chCondWait(&cond1);  // Espera sinal de Thread 3
        if (result == MSG_OK) {
            palTogglePad(IOPORT2, 5);  // Alterna LED1 (PORTB5)
            chThdSleepMilliseconds(500);  // Pequeno atraso para evitar bloqueio rápido
        }

        chCondSignal(&cond2);  // Sinaliza a Thread 2
        chMtxUnlock(&mutex);

        
    }
}

// Thread 2: Alterna o LED2 e sinaliza a Thread 3
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
    (void)arg;

    while (true) {
        chMtxLock(&mutex);

        msg_t result = chCondWait(&cond2);  // Espera sinal de Thread 1
        if (result == MSG_OK) {
            palTogglePad(IOPORT2, 4);  // Alterna LED2 (PORTB4)
            chThdSleepMilliseconds(500);  // Atraso para teste
        }

        chCondSignal(&cond3);  // Sinaliza a Thread 3
        chMtxUnlock(&mutex);

        
    }
}

// Thread 3: Alterna o LED3 e sinaliza a Thread 1
static THD_WORKING_AREA(waThread3, 128);
static THD_FUNCTION(Thread3, arg) {
    (void)arg;

    while (true) {
        if(b){
            b=false;
            // Inicia o ciclo sinalizando a Thread 1
            chMtxLock(&mutex);
            chCondSignal(&cond1);  // Sinaliza a Thread 1 para começar o ciclo
            chMtxUnlock(&mutex);   
             
            continue;  
        }
        chMtxLock(&mutex);

        msg_t result = chCondWait(&cond3);  // Espera sinal de Thread 2
        if (result == MSG_OK) {
            palTogglePad(IOPORT4, 7);  // Alterna LED3 (PORTD7)
            chThdSleepMilliseconds(500);  // Atraso para teste
        }

        chCondSignal(&cond1);  // Sinaliza a Thread 1 para reiniciar ciclo
        chMtxUnlock(&mutex);

        
    }
}

// Função principal (main)
int main(void) {
    halInit();
    chSysInit();

    // Configuração dos pinos como saída e inicialização em nível baixo
    palSetPadMode(IOPORT2, 5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(IOPORT2, 4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(IOPORT4, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(IOPORT2, 5);  // PORTB5 em nível baixo
    palClearPad(IOPORT2, 4);  // PORTB4 em nível baixo
    palClearPad(IOPORT4, 7);  // PORTD7 em nível baixo

    // Inicializa o mutex e as variáveis de condição
    chMtxObjectInit(&mutex);
    chCondObjectInit(&cond1);
    chCondObjectInit(&cond2);
    chCondObjectInit(&cond3);

    // Cria as threads
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
    chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
    chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);


    while (true) {
        chThdSleepMilliseconds(1000);  // Mantém o sistema ativo
    }
}

