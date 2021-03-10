#include <cstdio>
#include <vector>

#include "include\cpu.h"
#include "include\debugger.h"
#include "include\memory.h"
#include "include\programmer.h"

//https://edge.edx.org/c4x/BITSPilani/EEE231/asset/8086_family_Users_Manual_1_.pdf
//https://wiki.osdev.org/MZ
//https://csiflabs.cs.ucdavis.edu/~ssdavis/50/8086%20Opcodes.pdf
//https://www.gabrielececchetti.it/Teaching/CalcolatoriElettronici/Docs/i8086_instruction_set.pdf

int main()
{
    Memory memory;
    CPU cpu;
    cpu.Reset(memory);

    std::vector<uint8_t> program = {
        //header start
        0x4D, 0x5A,  //MZ
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x20,  //SS = 0x2000
        0xFD, 0xFF,  //SP = 0xFFFD
        0x00, 0x00,
        0x00, 0x00,  //IP = 0x0000
        0x00, 0x10,  //CS = 0x1000
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        //header end
        //program
        0xB8, 0x01, 0x20,                           //mov ax, 0x2001            |3
        0x50,                                       //push ax                   |8
        0x59,                                       //pop cx                    |8
        0x05, 0xFF, 0x10,                           //add ax, 0x10FF            |4
        0x89, 0xC3,                                 //mov bx, ax                |2                 
        0xC7, 0x06, 0x00, 0xB8, 0x00, 0x40,         //mov word [0xb800], 0x4000 |10
        0xA1, 0x00, 0xB8,                           //mov ax, [0xb800]          |8
        0x89, 0xC2,                                 //mov dx, ax                |2
        0xBE, 0xFF, 0xb7,                           //mov si, 0xb7ff            |3
        0x8B, 0x44, 0x01,                           //mov ax, [si+1]            |8
        0x89, 0xC7,                                 //mov di, ax                |2
        0xB8, 0x0F, 0x00,                           //mov ax, 0x0F              |3
        0xBE, 0x00, 0x00,                           //mov si, 0x00              |3
        0x81, 0xC6, 0x00, 0x10,                     //add si, 0x1000            |4
        0x48,                                       //dec                       |2
        0x75, 0xF9,                                 //jnz loop(6 bytes up)      |16
        0xB8, 0x00, 0x04,                           //mov ax, 0x400             |3
        0x74, 0x03,                                 //jz +3                     |16
        0xB8, 0x00, 0x02,                           //mov ax, 0x200             |3
        0x40,                                       //inc ax                    |2
        0x40,                                       //inc ax                    |2
        0x90,                                       //nop                       |1
        0xB0, 0xEE,                                 //mov al, 0xEE              |3
        0xA0, 0x00, 0xb8,                           //mov al, [0xb800]          |3
        //program end
    };

    Programmer programmer;
    programmer.Program(cpu, memory, program);

    cpu.Execute(memory, INT16_MAX);

    Debugger debugger;
    debugger.Registers(cpu, memory);
    debugger.Eflags(cpu, memory);
    debugger.ShowSegment(cpu, memory, cpu.CS, 0x0, 256);
    debugger.ShowStack(cpu, memory, 2);
    debugger.ShowSegment(cpu, memory, cpu.DS, 0xb800, 4);
    printf("Done");
    
    return 0;
}