#include <cstdio>

#include "CPU\cpu.h"
#include "Debugger\debugger.h"
#include "Memory\memory.h"
#include "Programmer\programmer.h"

//https://edge.edx.org/c4x/BITSPilani/EEE231/asset/8086_family_Users_Manual_1_.pdf
//https://wiki.osdev.org/MZ

int main()
{
    Memory memory;
    CPU cpu;
    cpu.Reset(memory);
    
    printf("Created\r\n");

    uint8_t program[36] = {
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
        0xB8, 0x02, 0x00,
        0x83, 0x0C, 0x01,
        //program 1 end
    };

    Programmer programmer;
    programmer.Program(cpu, memory, program, 36);

    printf("Programmed\n\r");

    Debugger debugger;
    debugger.Registers(cpu, memory);

    printf("Done\n\r");
    return 0;
}