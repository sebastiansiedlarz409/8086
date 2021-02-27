#pragma once

#include "..\CPU\cpu.h"
#include "..\Memory\memory.h"

class Programmer{
    public:
    void Program(CPU& cpu, Memory& mem, uint8_t* byte_code, uint32_t size);
};