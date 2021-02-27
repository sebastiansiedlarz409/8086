#pragma once

#include <cstdint>

class Memory{
    static constexpr uint32_t MemorySize = 0x10FFEF;
    uint8_t space[MemorySize];

    public:
    Memory();
    uint8_t& operator[](uint32_t address);
    uint8_t operator[](uint32_t address) const;
};