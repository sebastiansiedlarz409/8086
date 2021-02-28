#pragma once

#include "..\Memory\memory.h"
#include "register.h"

#define AX AX_Register.AX_R
#define AH AX_Register.AH_R
#define AL AX_Register.AL_R
#define BX BX_Register.BX_R
#define BH BX_Register.BH_R
#define BL BX_Register.BL_R
#define CX CX_Register.CX_R
#define CH CX_Register.CH_R
#define CL CX_Register.CL_R
#define DX DX_Register.DX_R
#define DH DX_Register.DH_R
#define DL DX_Register.DL_R

class CPU
{   
    AX_R AX_Register;
    BX_R BX_Register;
    CX_R CX_Register;
    DX_R DX_Register;

    public:    
    //P(22) EFLAGS
    struct{
        uint8_t NU16 : 1;
        uint8_t NU15 : 1;
        uint8_t NU14 : 1;
        uint8_t NU13 : 1;
        uint8_t NU12 : 1;
        uint8_t OF : 1; //overflow
        uint8_t DF : 1; //direction
        uint8_t IF : 1; //interrupt enable
        uint8_t TF : 1; //trap
        uint8_t SF : 1; //sign
        uint8_t ZF : 1; //zero
        uint8_t NU5 : 1;
        uint8_t AF : 1; //auxiliary
        uint8_t NU3 : 1;
        uint8_t PF : 1; //parity
        uint8_t NU1 : 1; 
        uint8_t CF : 1; //cary
    };

    //P(22)
    uint16_t IP;

    uint16_t CS;
    uint16_t DS;
    uint16_t ES;
    uint16_t SS;

    uint16_t BP;
    uint16_t SP;
    uint16_t DI;
    uint16_t SI;
    
    void Reset(Memory& mem); 
    uint32_t CalculateAddress(uint16_t segment, uint16_t address);
    void Push(Memory& mem, uint16_t value);
    uint16_t Pop(Memory& mem);
    void Mem_PutByte(Memory& mem, uint16_t segment, uint16_t address, uint8_t value);
    void Mem_PutWord(Memory& mem, uint16_t segment, uint16_t address, uint16_t value);
    uint8_t Mem_GetByte(const Memory& mem, uint16_t segment, uint16_t address);
    uint16_t Mem_GetWord(const Memory& mem, uint16_t segment, uint16_t address);
};