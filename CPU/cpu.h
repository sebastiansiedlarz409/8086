#pragma once

#include "..\Memory\memory.h"
#include "register.h"

class CPU : public Registers
{   
    public:
    void Reset(Memory& mem); 
    uint32_t CalculateAddress(uint16_t segment, uint16_t address);
    void Push(Memory& mem, uint16_t value);
    uint16_t Pop(Memory& mem);
    void Mem_PutByte(Memory& mem, uint16_t segment, uint16_t address, uint8_t value);
    void Mem_PutWord(Memory& mem, uint16_t segment, uint16_t address, uint16_t value);
    uint8_t Mem_GetByte(const Memory& mem, uint16_t segment, uint16_t address);
    uint16_t Mem_GetWord(const Memory& mem, uint16_t segment, uint16_t address);
    uint8_t FetchInstruction(Memory& mem, uint16_t& cycle);
    void Execute(Memory& mem, uint16_t cycle);
    void SetFLAGS(uint8_t o, uint8_t s, uint8_t c, uint8_t a, uint8_t p, uint8_t z);
    uint8_t GetOF(uint16_t value1, uint16_t value2);
    uint8_t GetSF(uint16_t value);
    uint8_t GetCF(uint16_t value1, uint16_t value2);
    uint8_t GetZF(uint16_t value);
    uint8_t GetPF(uint16_t value);
    uint8_t GetAF(uint16_t value1, uint16_t value2);
    uint16_t& GetReg16(uint8_t reg);
};