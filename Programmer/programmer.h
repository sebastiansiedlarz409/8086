#pragma once

#include <vector>

#include "..\CPU\cpu.h"
#include "..\Memory\memory.h"

class Programmer{
    public:
    void Program(CPU& cpu, Memory& mem, std::vector<uint8_t> byte_code);
};