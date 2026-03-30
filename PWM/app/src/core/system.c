#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>
#include "core/system.h"



static volatile uint64_t ticks = 0; // there is a problem in using 64 bit operations on 32 bit MCU
                             // it will take 2 assembly instructions, you need to disable other interrupts while in the function then turn it back on after
void sys_tick_handler(void) {
 ticks++;
}

uint64_t system_get_ticks(void) {   // static avoid compiler complaining about there is no prototype of the functions
 return ticks;
}

static void rcc_setup(void){
   rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void systick_setup(void) {
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();
}

void system_setup(void){
    rcc_setup();
    systick_setup();
}

