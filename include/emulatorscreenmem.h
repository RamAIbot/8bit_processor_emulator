#ifndef EMULATORSCREENMEM_H
#define EMULATORSCREENMEM_H

#include <stdbool.h>

struct emulator_screen_memory
{
    unsigned char screen_memory_ones[80];
    unsigned char screen_memory_tenths[80];
    unsigned char screen_memory_hundreds[80];
};


#endif