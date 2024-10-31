#include <avr/interrupt.h>
#include "circular_buffer.h"


void buffer_init(buffer_t* buf) {
    buf->wr = buf->rd = 0;
    buf->error_buffer_full = 0;
}

void set_event(buffer_t* buf, buffer_elem_t e) {
    cli();

    set_event_i(buf, e);

    sei();
}

void set_event_i(buffer_t* buf, buffer_elem_t e) {
    uint8_t new_wr = buf->wr + 1;
    if (new_wr >= BUF_SIZE)
	new_wr = 0;
    if (new_wr != buf->rd) {
	buf->buffer[buf->wr] = e;
	buf->wr = new_wr;
    } else
	buf->error_buffer_full = 1;
}



buffer_elem_t get_event(buffer_t* buf) {
    while (buf->rd == buf->wr)
	asm("nop");

    buffer_elem_t tmp = buf->buffer[buf->rd];

    cli();
    if (++buf->rd >= BUF_SIZE)
	buf->rd = 0;
    sei();

    return tmp;
}
