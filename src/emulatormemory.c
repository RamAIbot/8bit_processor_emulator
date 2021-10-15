#include "emulatormemory.h"
#include "config.h"
#include <assert.h>

static void emulator_memory_in_bounds(int index)
{
    
    assert(index >=0 && index < EMULATOR_MEMORY_SIZE);
}

void emulator_memory_set(struct emulator_memory *memory,int index,unsigned char val)
{
    emulator_memory_in_bounds(index);
    memory->memory[index] = val;
}

unsigned char emulator_memory_get(struct emulator_memory *memory,int index)
{
    emulator_memory_in_bounds(index);
    return memory->memory[index];
}