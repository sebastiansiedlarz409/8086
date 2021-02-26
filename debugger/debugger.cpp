#include "debugger.h"

#include <stdio.h>

Debugger::Debugger(CPU* cpu){
    this->cpu = cpu;
}

void Debugger::Registers(){
    uint16_t ax = *(((uint16_t*)cpu)+4);
    uint16_t ah = *(((uint8_t*)cpu)+10);
    uint16_t al = *(((uint8_t*)cpu)+11);
    printf("AX: %u CH: %u CL: %u\n\r", ax, ah, al);

    uint16_t bx = *(((uint16_t*)cpu)+6);
    uint16_t bh = *(((uint8_t*)cpu)+14);
    uint16_t bl = *(((uint8_t*)cpu)+15);
    printf("BX: %u CH: %u CL: %u\n\r", bx, bh, bl);
    
    uint16_t cx = *(((uint16_t*)cpu)+8);
    uint16_t ch = *(((uint8_t*)cpu)+18);
    uint16_t cl = *(((uint8_t*)cpu)+19);
    printf("CX: %u CH: %u CL: %u\n\r", cx, ch, cl);
    
    uint16_t dx = *(((uint16_t*)cpu)+10);
    uint16_t dh = *(((uint8_t*)cpu)+22);
    uint16_t dl = *(((uint8_t*)cpu)+23);
    printf("DX: %u DH: %u DL: %u\n\r", dx, dh, dl);
}