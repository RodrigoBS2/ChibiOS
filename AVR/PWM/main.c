#include "ch.h"
#include "hal.h"

#define PWM_frequencia F_CPU/1024
#define PWM_periodo    10000
#define pwm_periodo_cb NULL

PWMConfig   driver_config = {PWM_frequencia, 
                             PWM_periodo, 
                             pwm_periodo_cb, {{PWM_OUTPUT_HIGH,0},  
                                              {PWM_OUTPUT_DISABLE,0}}
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








