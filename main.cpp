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
        0xA0, 0x01, 0xb8,                           //mov al, [0xb800]          |3
        0x88, 0xC8,                                 //mov al, cl                |2
        0x88, 0xFA,                                 //mov dl, bh                |2
        0xA2, 0x22, 0x22,                           //mov byte [0x2222], al     |9
        0xA3, 0x23, 0x22,                           //mov word [0x2223], ax     |9
        0xB0, 0xAA,                                 //mov al, 0xAA              |3
        0xB1, 0xCA,                                 //mov cl, 0xCA              |3
        0xB2, 0xDA,                                 //mov dl, 0xDA              |3
        0xB3, 0xBA,                                 //mov bl, 0xBA              |3
        0xB4, 0xAA,                                 //mov ah, 0xAA              |3
        0xB5, 0xCA,                                 //mov ch, 0xCA              |3
        0xB6, 0xDA,                                 //mov dh, 0xDA              |3
        0xB7, 0xBA,                                 //mov bh, 0xBA              |3
        0xB8, 0xAA, 0xAA,                           //mov ax, 0xAAAA            |3
        0xB9, 0xCA, 0xCC,                           //mov cx, 0xCCCA            |3
        0xBA, 0xDA, 0xDD,                           //mov dx, 0xDDDA            |3
        0xBB, 0xBA, 0xBB,                           //mov bx, 0xBBBA            |3
        0xBD, 0xCA, 0xBF,                           //mov bp, 0xBFCA            |3
        0xBE, 0xDA, 0xBD,                           //mov si, 0xBDDA            |3
        0xBF, 0xBA, 0xB0,                           //mov di, 0xB0BA            |3
        0xC6, 0x06, 0x02, 0xb8, 0x12,               //mov byte [0xb802], 0x12   |10
        0xBF, 0x00, 0xb8,                           //mov di, 0xb800            |3
        0xC6, 0x85, 0x03, 0x00, 0x13,               //mov byte [di+0x03], 0x13  |10
        0xBF, 0x00, 0x00,                           //mov di, 0x0               |3
        0xC6, 0x85, 0x04, 0xB8, 0x14,               //mov byte [di+0xb804], 0x14|10
        0xBF, 0x05, 0xb8,                           //mov di, 0xb805            |3
        0xC6, 0x05, 0xEE,                           //mov byte [di], 0xEE       |10
        0xC7, 0x85, 0x01, 0x00, 0x34, 0x12,         //mov word [di+0x1], 0x1234 |10
        0xBF, 0x00, 0x00,                           //mov di, 0x0               |3
        0xC7, 0x85, 0x08, 0xb8, 0x78, 0x56,         //mov word [di+0xb808], 0x5678|10
        0xBF, 0x0A, 0xB8,                           //mov di, 0xb80A            |3
        0xC7, 0x05, 0xAA, 0xEE,                     //mov word [di], 0xEEAA     |10
        0xBF, 0x0A, 0xB8,                           //mov di, 0xb80A            |3
        0xBE, 0x0A, 0xB8,                           //mov si, 0xb80A            |3
        0xBB, 0x00, 0x40,                           //mov bx, 0x4000            |3
        0x8E, 0xC3,                                 //mov es, bx                |2
        0xA4,                                       //movsb                     |18
        0xBF, 0x08, 0xB8,                           //mov di, 0xb808            |3
        0xBE, 0x08, 0xB8,                           //mov si, 0xb808            |3
        0xA5,                                       //movsw                     |18
        0xBE, 0x00, 0xB8,                           //mov si, 0xb800            |3
        0x8B, 0x1C,                                 //mov bx, [si]              |8
        0x8B, 0x4C, 0x01,                           //mov cx, [si+1]            |8
        0xBE, 0x00, 0x00,                           //mov si, 0x0000            |3
        0x8A, 0x94, 0x05, 0xB8,                     //mov dl, [si+0xb805]       |8
        0xBE, 0x06, 0xB8,                           //mov si, 0xb806            |3
        0x8A, 0x1C,                                 //mov bl, [si]              |8
        0x8A, 0x4C, 0x01,                           //mov cl, [si+1]            |8
        0x8C, 0xC2,                                 //mov dx, es                |2
        0xBF, 0x00, 0xB8,                           //mov di, 0xB800            |3
        0xB0, 0x56,                                 //mov al, 0x56              |3
        0xAA,                                       //stosb                     |11
        0xBF, 0x01, 0xB8,                           //mov di, 0xB801            |3
        0xAB,                                       //stosw                     |11
        //program end
    };

    Programmer programmer;
    programmer.Program(cpu, memory, program);

    cpu.Execute(memory, INT16_MAX);

    Debugger debugger;
    debugger.Registers(cpu, memory);
    debugger.Eflags(cpu, memory);
    debugger.ShowSegment(cpu, memory, cpu.CS, 0x0, 256);
    debugger.ShowSegment(cpu, memory, cpu.DS, 0xb800, 16);
    debugger.ShowSegment(cpu, memory, cpu.DS, 0x2222, 16);
    debugger.ShowSegment(cpu, memory, cpu.ES, 0xb800, 16);
    debugger.ShowStack(cpu, memory, 2);
    printf("Done");
    
    return 0;
}