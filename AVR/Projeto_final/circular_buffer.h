#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H


#define BUF_SIZE 5

typedef uint8_t buffer_elem_t;
typedef struct {
    uint8_t rd;
    uint8_t wr;
    buffer_elem_t buffer[BUF_SIZE];
    uint8_t error_buffer_full;
} buffer_t;

void buffer_init(buffer_t* buf);
void set_event(buffer_t* buf, buffer_elem_t e);
void set_event_i(buffer_t* buf, buffer_elem_t e);
buffer_elem_t get_event(buffer_t* buf);

#endif /* CIRCULAR_BUFFER_H */
