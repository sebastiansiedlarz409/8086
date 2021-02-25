#pragma once

#include "..\Memory\memory.h"
#include "register.h"

#define AX *ax
#define AH *ah
#define AL *al
#define BX *bx
#define BH *bh
#define BL *bl
#define CX *cx
#define CH *ch
#define CL *cl
#define DX *dx
#define DH *dh
#define DL *dl
#define SP sp
#define BP bp
#define DI di
#define SI si
#define CS cs
#define DS ds
#define SS ss
#define ES es
#define IP ip

#define TF EFLAGS[4] //trap
#define DF EFLAGS[5] //direction
#define IF EFLAGS[6] //interrupt enable
#define OF EFLAGS[7] //overflow
#define SF EFLAGS[8] //sign
#define ZF EFLAGS[9] //zero
#define AF EFLAGS[11] //auxiliary
#define PF EFLAGS[13] //parity
#define CF EFLAGS[15] //carry

class CPU
{   
    AX_R AX_Register;
    BX_R BX_Register;
    CX_R CX_Register;
    DX_R DX_Register;

    uint16_t* ax = &AX_Register.AX_R;
    uint8_t* ah = &AX_Register.AH_R;
    uint8_t* al = &AX_Register.AL_R;

    uint16_t* bx = &BX_Register.BX_R;
    uint8_t* bh = &BX_Register.BH_R;
    uint8_t* bl = &BX_Register.BL_R;

    uint16_t* cx = &CX_Register.CX_R;
    uint8_t* ch = &CX_Register.CH_R;
    uint8_t* cl = &CX_Register.CL_R;

    uint16_t* dx = &DX_Register.DX_R;
    uint8_t* dh = &DX_Register.DH_R;
    uint8_t* dl = &DX_Register.DL_R;
    
    public:
    //P(22)
    uint8_t EFLAGS[16];

    //P(22)
    uint16_t ip;

    uint16_t cs;
    uint16_t ds;
    uint16_t es;
    uint16_t ss;

    uint16_t bp;
    uint16_t sp;
    uint16_t di;
    uint16_t si;

    Memory* memory;

    uint32_t CalculateAddress(uint16_t segment, uint16_t address);
    void Push(uint16_t value);
    uint16_t Pop();
    void Reset();
    Memory* GetMemory();
    void Mem_PutByte(uint16_t segment, uint16_t address, uint8_t value);
    void Mem_PutWord(uint16_t segment, uint16_t address, uint16_t value);
    uint8_t Mem_GetByte(uint16_t segment, uint16_t address);
    uint16_t Mem_GetWord(uint16_t segment, uint16_t address);
    CPU(Memory* memory);
};