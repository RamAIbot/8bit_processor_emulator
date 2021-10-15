#include "emulator.h"
#include "SDL2/SDL.h"
#include <memory.h>
#include <assert.h>
#include "config.h"
#include <stdbool.h>

const char emulator_default_character_set[] = {
    0xF0,0x90,0x90,0x90,0xF0,
    0x20,0x60,0x20,0x20,0x70,
    0xF0,0x10,0xF0,0x80,0xF0,
    0xF0,0x10,0xF0,0x10,0xF0,
    0x90,0x90,0xF0,0x10,0x10,
    0xF0,0x80,0xF0,0x10,0xF0,
    0xF0,0x80,0xF0,0x90,0xF0,
    0xF0,0x10,0x20,0x40,0x40,
    0xF0,0x90,0xF0,0x90,0xF0,
    0xF0,0x90,0xF0,0x10,0xF0,
    0xF0,0x90,0xF0,0x90,0x90,
    0xE0,0x90,0xE0,0x90,0xE0,
    0xF0,0x80,0x80,0x80,0xF0,
    0xE0,0x90,0x90,0x90,0xE0,
    0xF0,0x80,0xF0,0x80,0xF0,
    0xF0,0x80,0xF0,0x80,0x80

};


void emulator_init(struct emulator *emulator)
{
    memset(emulator,0,sizeof(struct emulator));

    memcpy(&emulator->screen_memory.screen_memory_ones,emulator_default_character_set,sizeof(emulator_default_character_set));

    memcpy(&emulator->screen_memory.screen_memory_tenths,emulator_default_character_set,sizeof(emulator_default_character_set));

    memcpy(&emulator->screen_memory.screen_memory_hundreds,emulator_default_character_set,sizeof(emulator_default_character_set));
}

void emulator_load(struct emulator *emulator,const char *buf,size_t size)
{
    assert(size<EMULATOR_MEMORY_SIZE);
    //printf("%s\n",buf);
    //printf("%c\n",buf[2]);
    memcpy(&emulator->memory.memory,buf,size);
    // for(int i=0;i<4;i++)
    //     printf("%d\n",emulator->memory.memory[i]);
    emulator->registers.PC = 0;
}

bool emulator_exec(struct emulator *emulator,unsigned char opcode)
{
    unsigned char instruction = opcode >> 4;
    unsigned char operand = (opcode & 0x0F);
   // printf("%x\n",instruction);
    //printf("%x\n",operand);
    bool halt = false;
    switch(instruction)
    {
        case 0x00:
            break;
        case 0x01:
        {
            //LDA 14 => Load A from Mem[14];
            emulator->registers.V[A_reg] = emulator_memory_get(&emulator->memory,(int)operand);

            //printf("%d\n",emulator->registers.V[A_reg]);

        }break;

        case 0x02:
        {
            //ADD 15 => Load A = A + B where B = Mem[15];
            //Sets Carry flag if sum > 255 and Zero flag if sum = 0
            emulator->registers.V[B_reg] = emulator_memory_get(&emulator->memory,(int)operand);
            int sum = emulator->registers.V[A_reg] + emulator->registers.V[B_reg];
            emulator->registers.V[A_reg] = sum;
           
            if(sum > 255)
                emulator->registers.carry_flag = true;
            else
                emulator->registers.carry_flag = false;
            if(sum == 0)
                emulator->registers.zero_flag = true;
            else
                emulator->registers.zero_flag = false;
           // printf("%d\n",emulator->registers.V[A_reg]);

        }break;

        case 0x03:
        {
            //SUB 15 => Load A = A - B where B = Mem[15];
            //Sets Carry Flag if sub < 0 and Zero Flag if sub = 0
            emulator->registers.V[B_reg] = emulator_memory_get(&emulator->memory,(int)operand);
            int sub = emulator->registers.V[A_reg] - emulator->registers.V[B_reg];
            emulator->registers.V[A_reg] = sub;

            if(sub < 0 || sub > 0)
                emulator->registers.carry_flag = true;
            else
                emulator->registers.carry_flag = false;
            if(sub == 0)
                emulator->registers.zero_flag = true;
            else
                emulator->registers.zero_flag = false;

        }break;

        case 0x04:
        {
            //STA 15 => RAM[15] = A;
            emulator_memory_set(&emulator->memory,operand,emulator->registers.V[A_reg]);

        }break;

        case 0x05:
        {
            //LDI 0 => Load A = 0
            emulator->registers.V[A_reg] = operand;
        }break;

        case 0x06:
        {
            //JMP 3 => Sets PC = 3
            emulator->registers.PC = operand;
        }break;

        case 0x07:
        {
            //JC 3 => Sets PC = 3 if Carry flag is set
            if(emulator->registers.carry_flag)
            {
                emulator->registers.PC = operand;
            }
        }break;

        case 0x08:
        {
            //JZ 3 => Sets PC = 3 if Zero Flag is set
            if(emulator->registers.zero_flag)
            {
                emulator->registers.PC = operand;
            }
        }break;

        case 0x0E:
        {
            //OUT => Displays the content in A register
            uint8_t ind= emulator->registers.V[A_reg];
            //printf("%d\n",emulator->registers.V[A_reg]);
            emulator_screen_clear(&emulator->screen);
            emulator_screen_set(&emulator->screen, &emulator->screen_memory,10,10,5,ind);

        }break;

        case 0x0F:
        {
            //HLT => Halts the program (PC)
            halt = true;
        }break;
    }

    return halt;
}