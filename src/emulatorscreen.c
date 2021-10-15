#include "emulatorscreen.h"
#include "config.h"

bool emulator_screen_is_set(struct emulator_screen *screen,int x,int y)
{
    return screen->pixels[y][x];
}

void emulator_screen_clear(struct emulator_screen *screen)
{
    for(int x=0;x<EMULATOR_WIDTH;x++)
        {
            for (int y=0;y<EMULATOR_HEIGHT;y++)
            {
                screen->pixels[y][x] = false;
            }
        }
}

void emulator_draw_sprite(struct emulator_screen *screen,int x,int y,int num,const char *sprite)
{
    for(int ly=0;ly<num;ly++)
    {
        char c = sprite[ly];
    
        for(int lx=0;lx<8;lx++)
        {
            if((c & (0b10000000 >> lx)) == 0)
                continue;
            screen->pixels[(y+ly)%EMULATOR_HEIGHT][(x+lx)%EMULATOR_WIDTH] = true;
        }
    }
}

void emulator_screen_set(struct emulator_screen *screen,struct emulator_screen_memory *screenmem,int x,int y,int num,uint8_t index)
{
    uint8_t ind = index;
    int ones = ind % 10;
    int tens = (ind / 10) % 10;
    int hundreds = (ind /100) % 100;
    //printf("%d %d %d",hundreds,tens,ones);

    const char *sprite1 = &screenmem -> screen_memory_ones[ones*5];
    const char *sprite2 = &screenmem -> screen_memory_tenths[tens*5];
    const char *sprite3 = &screenmem -> screen_memory_hundreds[hundreds*5];

    emulator_draw_sprite(screen,x,y,num,sprite3);
    emulator_draw_sprite(screen,x+20,y,num,sprite2);
    emulator_draw_sprite(screen,x+40,y,num,sprite1);

}

