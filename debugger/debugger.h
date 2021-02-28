#pragma once

#include "..\CPU\cpu.h"
#include "..\Memory\memory.h"

enum Segment{
    CS,
    DS,
    ES,
    SS
};

class Debugger{
    public:
    void Registers(CPU& cpu, Memory& mem);
    void Eflags(CPU& cpu, Memory& mem);
    void ShowSegment(CPU& cpu, Memory& mem, Segment seg, uint16_t offset, uint16_t size);
};