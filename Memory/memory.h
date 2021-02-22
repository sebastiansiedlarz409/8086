#pragma once

#include <cstdint>

class Memory{
    uint8_t space[1024*1024];

    public:
    uint8_t& operator[](uint16_t address);
};