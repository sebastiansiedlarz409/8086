#include "debugger.h"
#include "..\Cpu\cpu.h"
#include "..\Memory\memory.h"

#include <stdio.h>

void Debugger::Registers(CPU& cpu, Memory& mem){
    uint16_t ax = cpu.AX;
    uint8_t ah = cpu.AH;
    uint8_t al = cpu.AL;
    printf("AX: 0x%x \tAH: 0x%x \tAL: 0x%x\n\r", ax, ah, al);

    uint16_t bx = cpu.BX;
    uint8_t bh = cpu.BH;
    uint8_t bl = cpu.BL;
    printf("BX: 0x%x \tBH: 0x%x \tBL: 0x%x\n\r", bx, bh, bl);
    
    uint16_t cx = cpu.CX;
    uint8_t ch = cpu.CH;
    uint8_t cl = cpu.CL;
    printf("CX: 0x%x \tCH: 0x%x \tCL: 0x%x\n\r", cx, ch, cl);
    
    uint16_t dx = cpu.DX;
    uint8_t dh = cpu.DH;
    uint8_t dl = cpu.DL;
    printf("DX: 0x%x \tDH: 0x%x \tDL: 0x%x\n\r", dx, dh, dl);
}