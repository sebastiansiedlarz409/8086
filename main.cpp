#include <cstdio>

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

    uint8_t program[34] = {
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
        0xA1, 0x00, 0x20,   //mov ax, 0x2000
        0x50,               //push ax
        //program 1 end
    };

    Programmer programmer;
    programmer.Program(cpu, memory, program, 34);
    printf("Programmed\n\r");

    cpu.Execute(memory, 15);

    Debugger debugger;
    debugger.Registers(cpu, memory);
    debugger.Eflags(cpu, memory);
    debugger.ShowSegment(cpu, memory, cpu.CS, 0x0, 256);
    debugger.ShowStack(cpu, memory, 2);

    printf("Done\n\r");
    return 0;
}