#include "ch.h"     // Inclui as funções relacionadas ao núcleo do sistema operacional em tempo real (RTOS).
#include "hal.h"    // Inclui as funções relacionadas ao Hardware Abstraction Layer (HAL), que facilita a manipulação do hardware.

void gpt_cb(GPTDriver* gptd){
    (void) gptd;
    palTogglePad(IOPORT4, 7);
}

int main(void){
    GPTConfig driver_config = {.frequency = 15625, .callback = gpt_cb};
    
    halInit();
    chSysInit();
    
    palSetPadMode(IOPORT4, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(IOPORT4, 7);

    gptStart(&GPTD1,&driver_config);
    gptStartContinuous(&GPTD1, 1);

    while(1){}
}
