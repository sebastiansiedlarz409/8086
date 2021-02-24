#pragma once

#include <cstdint>

#define MemorySize 1024*1024

class Memory{
    uint8_t space[MemorySize];

    public:
    Memory();
    uint8_t& operator[](uint16_t address);
};