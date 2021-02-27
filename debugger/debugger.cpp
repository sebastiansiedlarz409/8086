#include "debugger.h"
#include "..\Cpu\cpu.h"
#include "..\Memory\memory.h"

#include <stdio.h>

void Debugger::Registers(CPU& cpu, Memory& mem){
    uint16_t ax = *(((uint16_t*)&cpu)+4);
    uint8_t ah = *(((uint8_t*)&cpu)+10);
    uint8_t al = *(((uint8_t*)&cpu)+11);
    printf("AX: 0x%x AH: 0x%x AL: 0x%x\n\r", ax, ah, al);

    uint16_t bx = *(((uint16_t*)&cpu)+6);
    uint8_t bh = *(((uint8_t*)&cpu)+14);
    uint8_t bl = *(((uint8_t*)&cpu)+15);
    printf("BX: 0x%x BH: 0x%x BL: 0x%x\n\r", bx, bh, bl);
    
    uint16_t cx = *(((uint16_t*)&cpu)+8);
    uint8_t ch = *(((uint8_t*)&cpu)+18);
    uint8_t cl = *(((uint8_t*)&cpu)+19);
    printf("CX: 0x%x CH: 0x%x CL: 0x%x\n\r", cx, ch, cl);
    
    uint16_t dx = *(((uint16_t*)&cpu)+10);
    uint8_t dh = *(((uint8_t*)&cpu)+22);
    uint8_t dl = *(((uint8_t*)&cpu)+23);
    printf("DX: 0x%x DH: 0x%x DL: 0x%x\n\r", dx, dh, dl);
}