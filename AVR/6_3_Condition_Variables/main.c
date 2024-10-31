#include "ch.h"
#include "hal.h"

#define BUFFER_SIZE 5  // Tamanho do buffer circular

// Buffer circular e variáveis de controle
static uint8_t buffer[BUFFER_SIZE];
static uint8_t *write_ptr = buffer;  // Ponteiro de escrita
static uint8_t *read_ptr = buffer;   // Ponteiro de leitura
static uint8_t buffer_count = 0;     // Contador de elementos no buffer

// Mutex e variáveis de condição
static mutex_t buffer_mutex;
static condition_variable_t buffer_not_empty;
static condition_variable_t buffer_not_full;

// Função da thread Produtora
static THD_WORKING_AREA(waProducer, 128);
static THD_FUNCTION(Producer, arg) {
    (void)arg;
    uint8_t data = 0;  // Dados a serem produzidos
    msg_t result;      // Variável para armazenar o retorno de chCondWait

    while (true) {
        chMtxLock(&buffer_mutex);  // Trava o mutex

        // Espera enquanto o buffer está cheio
        while (buffer_count == BUFFER_SIZE) {
            result = chCondWait(&buffer_not_full);  // Aguarda espaço disponível
            if (result != MSG_OK) {
                // Tratar erros se necessário (por exemplo, interrupção)
                chMtxUnlock(&buffer_mutex);  // Libera o mutex em caso de erro
                continue;
            }
        }

        // Adiciona o dado ao buffer
        *write_ptr = data++;
        if (++write_ptr >= buffer + BUFFER_SIZE){
            write_ptr = buffer;  // Volta para o início do buffer
        }
        buffer_count++;

        // Sinaliza que o buffer não está mais vazio
        chCondSignal(&buffer_not_empty);

        chMtxUnlock(&buffer_mutex);  // Libera o mutex

        // Simula algum tempo de produção
        chThdSleepMilliseconds(500);
    }
}

// Função da thread Consumidora
static THD_WORKING_AREA(waConsumer, 128);
static THD_FUNCTION(Consumer, arg) {
    (void)arg;
    uint8_t received_data;
    msg_t result;  // Variável para armazenar o retorno de chCondWait

    while (true) {
        chMtxLock(&buffer_mutex);  // Trava o mutex

        // Espera enquanto o buffer está vazio
        while (buffer_count == 0) {
            result = chCondWait(&buffer_not_empty);  // Aguarda até haver dados
            if (result != MSG_OK) {
                // Tratar erros se necessário (por exemplo, interrupção)
                chMtxUnlock(&buffer_mutex);  // Libera o mutex em caso de erro
                continue;
            }
        }

        // Lê o dado do buffer
        received_data = *read_ptr;
        if (++read_ptr >= buffer + BUFFER_SIZE) {
            read_ptr = buffer;  // Volta para o início do buffer
        }
        buffer_count--;

        // Sinaliza que o buffer não está mais cheio
        chCondSignal(&buffer_not_full);

        chMtxUnlock(&buffer_mutex);  // Libera o mutex

        // Simula o processamento do dado recebido
        palTogglePad(IOPORT2, 5);  // Alterna o LED (PB5)
        chThdSleepMilliseconds(300);
    }
}

// Função principal (main)
int main(void) {
    halInit();    // Inicializa o HAL (Hardware Abstraction Layer)
    chSysInit();  // Inicializa o sistema ChibiOS

    // Configuração dos pinos
    palSetPadMode(IOPORT2, 5, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(IOPORT2, 5);

    // Inicializa o mutex e as variáveis de condição
    chMtxObjectInit(&buffer_mutex);
    chCondObjectInit(&buffer_not_empty);
    chCondObjectInit(&buffer_not_full);

    // Cria as threads produtora e consumidora
    chThdCreateStatic(waProducer, sizeof(waProducer), NORMALPRIO, Producer, NULL);
    chThdCreateStatic(waConsumer, sizeof(waConsumer), NORMALPRIO, Consumer, NULL);

    // Loop infinito para manter o sistema rodando
    while (true) {
        chThdSleepMilliseconds(1000);
    }
}

