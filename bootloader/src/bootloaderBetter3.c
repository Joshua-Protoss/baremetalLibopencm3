#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>

#define BOOTLOADER_SIZE         (0x8000U)
#define MAIN_APP_START_ADDRESS  (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void) {
    typedef void (*void_fn) (void);
    uint32_t* main_vector_table = (uint32_t*) (MAIN_APP_START_ADDRESS);
    void_fn jump_fn = (void_fn) main_vector_table[1];

    jump_fn();
}

int main(void) {
    jump_to_main();
    
    return 0;
}
