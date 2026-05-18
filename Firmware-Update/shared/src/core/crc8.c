#include "core/crc8.h"

//volatile int x = 0;

uint8_t crc8(uint8_t* data, uint32_t length) {
    uint8_t crc = 0;

    for (uint32_t i = 0; i < length; i++) {
        crc ^= data[i]; // on debug : log message : "0x%02x 0x%02x" c'est a dire print this message as a hex with 2 decimal
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;
            } else {
                crc <<= 1;
            }
        }
        //x++; //esqe vous conaissez itm? non, "0x%02x 0x%02x" data[i] crc
    }
    return crc;
}
