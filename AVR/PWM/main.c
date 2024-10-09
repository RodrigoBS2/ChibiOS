#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

/*O include a seguir será necessário para fazer manipulação de bits nos registradores*/
#include <stdint.h>

#include "ch.h"
#include "hal.h"

#define Frequencia F_CPU/1024
#define PWM_periodo    15625            
#define pwm_periodo_cb NULL

PWMConfig   driver_config = {Frequencia,        
                             PWM_periodo,           // PWM_frequencia = Frequencia/PWM_periodo. Nesse caso está configurando para uma frequência de 1HZ do PWM
                             pwm_periodo_cb, {{PWM_OUTPUT_ACTIVE_HIGH,0},  
                                              {PWM_OUTPUT_ACTIVE_LOW,0}}
}; 


int main(void) {
  halInit();
  chSysInit();
  DDRB |= (1 << DDB1); // Ou DDRB |= (1 << PB5)           // Configurando os pinos como saída
  PORTB |= (1 << PB1); // Definindo os pinos como nível lógico alto 

  //palSetPadMode(IOPORT2, 1, PAL_MODE_OUTPUT_PUSHPULL);
  //palWritePad(IOPORT2, 1, PAL_HIGH);
  pwmStart(&PWMD1,&driver_config);
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 5000));

  while (true) {
    chThdSleepMilliseconds(1000);
  }
}








