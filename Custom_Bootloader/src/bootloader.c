#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>

// this means 8000 bytes aka the start of the application to boot
#define BOOTLOADER_SIZE (0X8000)

// start of the actual firmware the bootloader hands off
#define MAIN_APP_START_ADDR (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void)
{
    typedef void (*void_fn)(void);

    // start of the interrupt vector table
    uint32_t *reset_vector_entry = (uint32_t *)(MAIN_APP_START_ADDR + 4U);

    // the actual address of the interrupt vector table
    uint32_t *reset_vector = (uint32_t *)*reset_vector_entry;

    void_fn jump_fn = (void_fn)reset_vector;

    jump_fn();
}

int main(void)
{
    jump_to_main();

    // no return since we need to refer to the firmware
    return 0;
}