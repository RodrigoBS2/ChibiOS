/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"     // Inclui as funções relacionadas ao núcleo do sistema operacional em tempo real (RTOS).
#include "hal.h"    // Inclui as funções relacionadas ao Hardware Abstraction Layer (HAL), que facilita a manipulação do hardware.

/*
 * LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 32);     // Define o espaço de trabalho (stack) para a thread Thread1, com tamanho de 32 bytes.

static THD_FUNCTION(Thread1, arg) {         /* É a função que define a thread Thread1. Ela recebe um argumento arg que, neste caso, 
                                               não é utilizado (por isso o (void)arg). */
  (void)arg;
  chRegSetThreadName("Blinker");    //  Dá um nome à thread, útil para fins de depuração.
  while (true) {                
    palTogglePad(IOPORT4, 7);       /* Alterna o estado do pino 7 (LED ligado/desligado). Para saber das identificações das porta: /home/rodrigo/                               ChibiOS_projects/os/hal/ports/AVR/XMEGA/LLD/GPIOv1/hal_pal_lld.h*/
    chThdSleepMilliseconds(1000);   // faz a thread dormir por 1000 ms (1 segundo) antes de alternar o LED novamente. Isso cria o efeito de pisca-pisca.
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */

  halInit();    // Inicializa a HAL, configurando os drivers de dispositivos e realizando inicializações específicas da placa.
  chSysInit();  
  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  sdStart(&SD1, NULL);

  /*
   * Starts the LED blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL); // Cria e inicia a thread Thread1 que controla o LED.

  chnWrite(&SD1, (const uint8_t *)"Hello World!\r\n", 14); /* Envia a string "Hello World!\r\n" pela interface serial, onde 14 
                                                              é o número de bytes a serem enviados.*/

  while (true) {
    chThdSleepMilliseconds(1000);
  }
}

/*
     O "chThdSleepMilliseconds(1000);" no loop while (true), dentro do "int main(void)" uma prática comum em sistemas embarcados 
     para garantir que a aplicação seja eficiente em termos de energia, e para permitir que o RTOS 
     gerencie o tempo de execução das threads de forma eficaz.
*/
