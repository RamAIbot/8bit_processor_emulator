#ifndef EMULATOR_H
#define EMULATOR_H

#include "emulatormemory.h"
#include "emulatorregisters.h"
#include "emulatorscreenmem.h"
#include "emulatorscreen.h"

struct emulator
{
    struct emulator_memory memory;
    struct emulator_registers registers;
    struct emulator_screen_memory screen_memory;
    struct emulator_screen screen;
};

void emulator_init(struct emulator *emulator);

void emulator_load(struct emulator *emulator,const char *buf,size_t size);

bool emulator_exec(struct emulator *emulator,unsigned char opcode);

#endif