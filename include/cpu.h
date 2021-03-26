#pragma once

#include "memory.h"
#include "register.h"

#include <queue>

class CPU : public Registers
{   
    int16_t cur_instruction = 0;
    std::queue<uint8_t> fetch_buffer;
    uint16_t fetch_ip = 0;
    uint16_t last_ip = 0;

    public:
    uint16_t code_size = 0;

    void Reset(Memory& mem); 
    uint32_t CalculateAddress(uint16_t segment, uint16_t address);
    void Push(Memory& mem, uint16_t value);
    uint16_t Pop(Memory& mem);
    void Mem_PutByte(Memory& mem, uint16_t segment, uint16_t address, uint8_t value);
    void Mem_PutWord(Memory& mem, uint16_t segment, uint16_t address, uint16_t value);
    uint8_t Mem_GetByte(const Memory& mem, uint16_t segment, uint16_t address);
    uint16_t Mem_GetWord(const Memory& mem, uint16_t segment, uint16_t address);
    void FetchInstruction(Memory& mem, int16_t& cycle);
    uint8_t GetFetchedByte();
    uint16_t GetFetchedWord();
    void ClearFetchedBuffer();
    void Execute(Memory& mem, int16_t cycle);
    void SetFLAGS(uint8_t o, uint8_t s, uint8_t c, uint8_t a, uint8_t p, uint8_t z);
    uint8_t& GetReg8(uint8_t reg);
    uint16_t& GetReg16(uint8_t reg);
    uint16_t& OffsetReg(uint8_t reg);
    uint16_t& SegReg(uint8_t reg);
    void MoveIns8(Memory& mem, uint8_t modrm, uint16_t disp, uint8_t type);
    void MoveIns16(Memory& mem, uint8_t modrm, uint16_t disp, uint8_t type);
};