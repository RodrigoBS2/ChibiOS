#include "ch.h"
#include "hal.h"


PWMConfig driver_config = {
      .frequency = 1000000,  // 1 MHz clock for the PWM
      .period = 1000,        // PWM period of 1000 ticks (1 kHz PWM frequency)
      .callback = NULL,
      .channels = {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},   // Channel 0 
        {PWM_OUTPUT_DISABLED, NULL},      // Channel 1 
      },
      
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








