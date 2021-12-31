#include "..\..\include\cpu.h"
#include "..\..\include\debugger.h"
#include "..\..\include\memory.h"

#include <stdio.h>

void Debugger::Registers(CPU& cpu, Memory& mem){
    uint16_t ax = cpu.AX;
    uint8_t ah = cpu.AH;
    uint8_t al = cpu.AL;
    printf("AX: 0x%04x \tAH: 0x%02x \tAL: 0x%02x\n\r", ax, ah, al);

    uint16_t bx = cpu.BX;
    uint8_t bh = cpu.BH;
    uint8_t bl = cpu.BL;
    printf("BX: 0x%04x \tBH: 0x%02x \tBL: 0x%02x\n\r", bx, bh, bl);
    
    uint16_t cx = cpu.CX;
    uint8_t ch = cpu.CH;
    uint8_t cl = cpu.CL;
    printf("CX: 0x%04x \tCH: 0x%02x \tCL: 0x%02x\n\r", cx, ch, cl);
    
    uint16_t dx = cpu.DX;
    uint8_t dh = cpu.DH;
    uint8_t dl = cpu.DL;
    printf("DX: 0x%04x \tDH: 0x%02x \tDL: 0x%02x\n\r", dx, dh, dl);

    uint16_t ip = cpu.IP;
    uint16_t sp = cpu.SP;
    uint16_t bp = cpu.BP;
    uint16_t di = cpu.DI;
    uint16_t si = cpu.SI;
    printf("IP: 0x%04x \tSP: 0x%04x \tBP: 0x%04x \tDI: 0x%04x \tSI: 0x%04x\n\r", ip, sp, bp, di, si);
    
    uint16_t cs = cpu.CS;
    uint16_t ds = cpu.DS;
    uint16_t es = cpu.ES;
    uint16_t ss = cpu.SS;
    printf("CS: 0x%04x \tDS: 0x%04x \tES: 0x%04x \tSS: 0x%04x\n\r", cs, ds, es, ss);
}

void Debugger::Eflags(CPU& cpu, Memory& memory){
    uint8_t OF = cpu.OF;
    uint8_t IF = cpu.IF;
    uint8_t DF = cpu.DF;
    uint8_t TF = cpu.TF;
    uint8_t SF = cpu.SF;
    uint8_t ZF = cpu.ZF;
    uint8_t AF = cpu.AF;
    uint8_t PF = cpu.PF;
    uint8_t CF = cpu.CF;
    
    printf("%s %s %s %s %s %s %s %s %s\n\r",

    OF == 1 ? "OF" : "of",
    IF == 1 ? "IF" : "if",
    DF == 1 ? "DF" : "df",
    TF == 1 ? "TF" : "tf",
    SF == 1 ? "SF" : "sf",
    ZF == 1 ? "ZF" : "zf",
    AF == 1 ? "AF" : "af",
    PF == 1 ? "PF" : "pf",
    CF == 1 ? "CF" : "cf");
}

void Debugger::ShowSegment(CPU& cpu, Memory& mem, uint16_t seg, uint16_t offset, uint16_t size){
    for(uint16_t i = 0;i<size;i++){
        uint8_t value = cpu.Mem_GetByte(mem, seg, offset+i);
        if(i%32 == 0){
            printf("\n\r0x%08x: \t",cpu.CalculateAddress(seg, offset+i));
        }
        printf("%02x ", value);
    }

    printf("\n\r");
}

void Debugger::ShowStack(CPU& cpu, Memory& mem, uint16_t size){
    printf("\n\rSTACK: \n\r");
    uint16_t sp = cpu.SP;
    for(uint16_t i = 0;i<size;i++){
        if(sp>=0xFFFF){
            break;
        }
        
        uint16_t value = cpu.Mem_GetWord(mem, cpu.SS, sp);
        printf("0x%08x:0x%08x \t0x%04x\n\r", cpu.CalculateAddress(cpu.SS, sp), cpu.CalculateAddress(cpu.SS, sp+2), value);
        
        sp+=2;
    }
}