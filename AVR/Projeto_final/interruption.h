#ifndef INTERRUPTION_H
#define INTERRUPTION_H

#include "main.h"

void config_interruption();

ISR(INT0_vect);
ISR(INT1_vect);
ISR(PCINT2_vect);




#endif
