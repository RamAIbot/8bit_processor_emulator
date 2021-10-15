#ifndef EMULATORREGISTERS_H
#define EMULATORREGISTERS_H

#include "config.h"
#include <stdbool.h>
#include <stdint.h>

struct emulator_registers
{
    unsigned char V[EMULATOR_TOTAL_DATA_REGISTERS];
    unsigned char I;
    unsigned short PC; 
    bool carry_flag;
    bool zero_flag;
};


#endif