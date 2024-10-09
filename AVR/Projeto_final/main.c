
#include "AVRincludes.h"


int main(void) {
  
  buffer b;
  
  halInit();    //  Inicialização do HAL
  chSysInit();  //  Inicialização do Kernel
  

  while (true) {
    chThdSleepMilliseconds(1000);
  }

}
