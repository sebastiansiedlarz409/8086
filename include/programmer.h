#pragma once

#include <vector>

#include "cpu.h"
#include "memory.h"

class Programmer{
    public:
    void Program(CPU& cpu, Memory& mem, std::vector<uint8_t> byte_code);
};