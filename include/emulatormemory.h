#ifndef EMULATORMEMORY_H
#define EMUALTORMEMORY_H

#include "config.h"
#include <stdint.h>

struct emulator_memory
{
    unsigned char memory[EMULATOR_MEMORY_SIZE];
};

void emulator_memory_set(struct emulator_memory *memory,int index,unsigned char val);

unsigned char emulator_memory_get(struct emulator_memory *memory,int index);
#endif