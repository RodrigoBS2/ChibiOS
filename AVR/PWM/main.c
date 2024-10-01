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
  
  pwmStart(&PWMD1,&driver_config);
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 5000));

  while (true) {
    chThdSleepMilliseconds(1000);
  }
}








