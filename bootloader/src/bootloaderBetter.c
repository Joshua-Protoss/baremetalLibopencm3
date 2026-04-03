#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>

#define BOOTLOADER_SIZE         (0x8000U)
#define MAIN_APP_START_ADDRESS  (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void) {
    typedef void (*void_fn) (void);
    uint32_t* main_vector_table = (uint32_t*) (MAIN_APP_START_ADDRESS);
    uint32_t* reset_vector = (uint32_t*)main_vector_table[1];
    // each entry in the interrupt vector table is 4 bytes long (uint32_t)
    // the first entry in this table is not the reset_vector but the stack pointer
    // the second entry is the reset_vector (in vector table)
    //uint32_t* reset_vector_entry = (uint32_t*) (MAIN_APP_START_ADDRESS + sizeof(uint32_t));
    //uint32_t* reset_vector = (uint32_t*) (*reset_vector_entry);

    void_fn jump_fn = (void_fn) reset_vector;

    jump_fn();
}

int main(void) {
    jump_to_main();
    
    return 0;
}
