#include <cstdio>
#include <vector>

#include "CPU\cpu.h"
#include "Debugger\debugger.h"
#include "Memory\memory.h"
#include "Programmer\programmer.h"

//https://edge.edx.org/c4x/BITSPilani/EEE231/asset/8086_family_Users_Manual_1_.pdf
//https://wiki.osdev.org/MZ
//https://csiflabs.cs.ucdavis.edu/~ssdavis/50/8086%20Opcodes.pdf
//https://www.gabrielececchetti.it/Teaching/CalcolatoriElettronici/Docs/i8086_instruction_set.pdf

int main()
{
    Memory memory;
    CPU cpu;
    cpu.Reset(memory);
    
    printf("Created\r\n");

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
        //program 1
        0xB8, 0x01, 0x20,                           //mov ax, 0x2001
        0x50,                                       //push ax
        0x59,                                       //pop cx
        0x05, 0xFF, 0x10,                           //add ax, 0x10FF
        0x89, 0xC3,                                 //mov bx, ax                                 
        0xC7, 0x06, 0x00, 0xB8, 0x00, 0x40,         //mov word [0xb800], 0x4000
        0xA1, 0x00, 0xB8,                           //mov ax, [0xb800]
        0x89, 0xC2,                                 //mov dx, ax
        0xBE, 0xFF, 0x37,                           //mov si, 0x37ff
        //program 1 end
    };

    Programmer programmer;
    programmer.Program(cpu, memory, program);
    printf("Programmed\n\r");

    cpu.Execute(memory, 52);

    Debugger debugger;
    debugger.Registers(cpu, memory);
    debugger.Eflags(cpu, memory);
    debugger.ShowSegment(cpu, memory, cpu.CS, 0x0, 256);
    debugger.ShowStack(cpu, memory, 2);
    debugger.ShowSegment(cpu, memory, cpu.DS, 0xb800, 4);
    printf("Done\n\r");
    return 0;
}