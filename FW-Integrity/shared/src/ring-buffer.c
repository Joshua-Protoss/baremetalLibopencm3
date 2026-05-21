#include "core/ring-buffer.h"

void ring_buffer_setup(ring_buffer_t* rb, uint8_t* buffer, uint32_t size){
    rb->buffer = buffer;
    rb->read_index = 0;
    rb->write_index = 0;
    rb->mask = size - 1;
}

bool ring_buffer_empty(ring_buffer_t* rb){
    return rb->read_index == rb->write_index;
}

bool ring_buffer_read(ring_buffer_t* rb, uint8_t* byte){
    uint32_t local_read_index = rb->read_index;
    uint32_t local_write_index = rb->write_index;

    if (local_read_index == local_write_index) {
        return false;
    }

    *byte = rb->buffer[local_read_index]; // make a pointer in the calling func, then save the rb->buffer data
    local_read_index = (local_read_index + 1) & rb->mask;
    rb->read_index = local_read_index;
    return true;
}

bool ring_buffer_write(ring_buffer_t* rb, uint8_t byte){
    uint32_t local_write_index = rb->write_index;
    uint32_t local_read_index = rb->read_index;
    // the reason why we take local indices : if someone else would call ring buffer read
    // any of those moment would change the value. the local copy is stable.
    // even if there are multiple readers we'll not gonna get collision
    // we don't really need it in this case. we don't expect multiple writers to our buffer

    uint32_t next_write_index = (local_write_index + 1) & rb->mask;
    // try to avoid writing on the same buffer_index as the read_index
    // meaning you avoid overwrite the data before it's being read
    if (next_write_index == local_read_index) {
        return false;
    }
    // otherwise we can write

    rb->buffer[local_write_index] = byte;
    rb->write_index = next_write_index;
    return true;
}
