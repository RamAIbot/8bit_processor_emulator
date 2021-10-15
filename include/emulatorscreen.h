#ifndef EMULATORSCREEN_H
#define EMULATORSCREEN_H

#include "config.h"
#include "emulatorscreenmem.h"
#include <stdint.h>

struct emulator_screen
{
    bool pixels[EMULATOR_HEIGHT][EMULATOR_WIDTH];
};

bool emulator_screen_is_set(struct emulator_screen *screen,int x,int y);

void emulator_screen_clear(struct emulator_screen *screen);

void emulator_draw_sprite(struct emulator_screen *screen,int x,int y,int num,const char *sprite);

void emulator_screen_set(struct emulator_screen *screen,struct emulator_screen_memory *screenmem,int x,int y,int num,uint8_t index);

#endif