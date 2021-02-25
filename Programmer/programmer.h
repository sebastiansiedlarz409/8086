#pragma once

#include "..\CPU\cpu.h"

class Programmer{
    public:
    void Program(CPU* cpu, uint8_t* byte_code, uint32_t size);
};