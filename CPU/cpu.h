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
};