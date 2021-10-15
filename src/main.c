#include <stdio.h>
#include "SDL2/SDL.h"
#include "emulator.h"
#include <Windows.h> 
#include <unistd.h>  
#include <stdlib.h>

int main(int argc,char** argv)
{

    if(argc < 2)
    {
        printf("You must provide a program file\n");
        return -1;
    }

    const char *filename = argv[1];
    FILE *f = fopen(filename,"rb");
    if(!f)
    {
        printf("Cannot open file\n");
        return -1;
    }

    fseek(f,0,SEEK_END);
    long size = ftell(f);
    fseek(f,0,SEEK_SET);
    //printf("Size : %d",size);
    char buf[size];
    int res = fread(buf,size,1,f);
    if(res!=1)
    {
        printf("Failed to read from file\n");
        return -1;
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(EMULATOR_WINDOW_TITLE,
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    EMULATOR_WIDTH*EMULATOR_WINDOW_MULTIPLIER,EMULATOR_HEIGHT*EMULATOR_WINDOW_MULTIPLIER,SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_TEXTUREACCESS_TARGET);

    struct emulator emu;
    emulator_init(&emu);
    //printf("%s",buf);
    
    emulator_load(&emu,buf,size);
    fclose(f);

    //emulator_memory_set(&emu.memory,14,0x0E);
    //emulator_memory_set(&emu.memory,15,0x1C);
    

    bool stop_pc = false;

    
    // emulator_memory_set(&emu.memory,10,'R');
    // printf("%c\n",emulator_memory_get(&emu.memory,10));
    // emu.registers.V[0] = 50;
    // emu.registers.V[1] = 100;

    // printf("%d\n",emu.registers.V[0]);
    // printf("%d\n",emu.registers.V[1]);

    // emulator_screen_set(&emu.screen,&emu.screen_memory,10,10,5,123);
    // emulator_screen_clear(&emu.screen);
    // emulator_screen_set(&emu.screen,&emu.screen_memory,10,10,5,245);

    while(1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    goto out;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,0);
        for(int x=0;x<EMULATOR_WIDTH;x++)
        {
            for (int y=0;y<EMULATOR_HEIGHT;y++)
            {
                if(emulator_screen_is_set(&emu.screen,x,y))
                {
                    SDL_Rect r;
                    r.x=x * EMULATOR_WINDOW_MULTIPLIER;
                    r.y=y * EMULATOR_WINDOW_MULTIPLIER;
                    r.w=EMULATOR_WINDOW_MULTIPLIER;
                    r.h=EMULATOR_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer,&r);
                    
                }
            }
        }
        
    SDL_RenderPresent(renderer);
    //printf("%d\n",emu.registers.PC);
    unsigned char opcode = emulator_memory_get(&emu.memory,emu.registers.PC);
    printf("%x\n",opcode);
    if(!stop_pc)
        emu.registers.PC += 1;
    printf("%d\n",emu.registers.carry_flag);
    printf("%d\n",emu.registers.zero_flag);
    //printf(" Mem 13 : %d\n",emu.memory.memory[14]);
    bool hlt = emulator_exec(&emu,opcode);
    if(hlt)
        stop_pc = true;
    
    sleep(1);

    }
    

    out:
    SDL_DestroyWindow(window);
    return 0;
}