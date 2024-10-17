

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
    chThdSleepMilliseconds(500);   // faz a thread dormir por 1000 ms (1 segundo) antes de alternar o LED novamente. Isso cria o efeito de pisca-pisca.
  }
}

/*
 * Application entry point.
 */
int main(void) {


  halInit();    
  chSysInit();  

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL); // Cria e inicia a thread Thread1 que controla o LED.


  while (true) {
    chThdSleepMilliseconds(1000);
  }
}

/*
     O "chThdSleepMilliseconds(1000);" no loop while (true), dentro do "int main(void)" uma prática comum em sistemas embarcados 
     para garantir que a aplicação seja eficiente em termos de energia, e para permitir que o RTOS 
     gerencie o tempo de execução das threads de forma eficaz.
*/
