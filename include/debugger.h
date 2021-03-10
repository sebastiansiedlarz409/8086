#pragma once

#include "cpu.h"
#include "memory.h"

class Debugger{
    public:
    void Registers(CPU& cpu, Memory& mem);
    void Eflags(CPU& cpu, Memory& mem);
    void ShowSegment(CPU& cpu, Memory& mem, uint16_t seg, uint16_t offset, uint16_t size);
    void ShowStack(CPU& cpu, Memory& mem, uint16_t size);
};