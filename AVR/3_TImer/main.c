#include <avr/io.h>
#include "ch.h"
#include "hal.h"

#define LED_PORT IOPORT4
#define LED_PIN 7
#define GPT_FREQUENCIA 15625
#define LED_PERIODO 1

void gpt_cb(GPTDriver* gptd){
    (void) gptd;
    palTogglePad(LED_PORT, LED_PIN);
}
        
int main(void){
    GPTConfig driver_config = {.frequency = GPT_FREQUENCIA, .callback = gpt_cb};
    
    halInit();
    chSysInit();
    
    palSetPadMode(LED_PORT, LED_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(LED_PORT, LED_PIN);

    gptStart(&GPTD1,&driver_config);
    gptStartContinuous(&GPTD1, LED_PERIODO);

    while(1){}
}


