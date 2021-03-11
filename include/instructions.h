#pragma once

#include "cpu.h"
#include "memory.h"

//EA
//Displacement                                            6
//Base or Index (BX,BP,SI,DI)                             5
//Displacement+(Base or Index)                            9
//Base+Index (BP+DI,BX+SI)                                7
//Base+Index (BP+SI,BX+DI)                                8
//Base+Index+Displacement (BP+DI,BX+SI)                  11
//Base+Index+Displacement (BP+SI+disp,BX+DI+disp)        12

//- add 4 cycles for word operands at odd addresses
//- add 2 cycles for segment override
//- 80188/80186 timings differ from those of the 8088/8086/80286

enum Instructions{
    ADD_AX_IMM16 = 0x05,        //4
    ADD_REG16_IMM16 = 0x81,     //4
    MOV_AL_IMM8 = 0xB0,         //3
    MOV_AX_IMM16 = 0xB8,        //3
    MOV_SI_IMM16 = 0xBE,        //3
    MOV_AL_RM8 = 0xA0,          //8+EA
    MOV_AX_RM16 = 0xA1,         //8+EA
    MOV_MEM8_AL = 0xA2,         //9+EA
    MOV_MEM16_AX = 0xA3,        //9+EA
    MOV_REG8_REG8 = 0x88,       //2
    MOV_REG16_REG16 = 0x89,     //2
    MOV_MEM16_IMM16 = 0xC7,     //10+EA
    MOV_REG16_MEM16 = 0x8B,     //8+EA
    PUSH_AX = 0x50,             //8
    POP_AX = 0x58,              //8
    POP_CX = 0x59,              //8
    DEC_AX = 0x48,              //2
    INC_AX = 0x40,              //2
    JZ = 0x74,                  //16
    JNZ = 0x75,                 //16
    NOP = 0x90,                 //1
};

void MOV_AL_IMM8_INS(CPU& cpu, Memory& mem);
void MOV_AX_IMM16_INS(CPU& cpu, Memory& mem);
void MOV_SI_IMM16_INS(CPU& cpu, Memory& mem);
void PUSH_AX_INS(CPU& cpu, Memory& mem);
void POP_AX_INS(CPU& cpu, Memory& mem);
void POP_CX_INS(CPU& cpu, Memory& mem);
void ADD_AX_IMM16_INS(CPU& cpu, Memory& mem);
void ADD_REG16_IMM16_INS(CPU& cpu, Memory& mem);
void MOV_AL_RM8_INS(CPU& cpu, Memory& mem);
void MOV_AX_RM16_INS(CPU& cpu, Memory& mem);
void MOV_MEM8_AL_INS(CPU& cpu, Memory& mem);
void MOV_MEM16_AX_INS(CPU& cpu, Memory& mem);
void MOV_REG16_MEM16_INS(CPU& cpu, Memory& mem);
void MOV_MEM16_IMM16_INS(CPU& cpu, Memory& mem);
void MOV_REG8_REG8_INS(CPU& cpu, Memory& mem);
void MOV_REG16_REG16_INS(CPU& cpu, Memory& mem);
void DEC_AX_INS(CPU& cpu, Memory& mem);
void INC_AX_INS(CPU& cpu, Memory& mem);
void JZ_INS(CPU& cpu, Memory& mem);
void JNZ_INS(CPU& cpu, Memory& mem);