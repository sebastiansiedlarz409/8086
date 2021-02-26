#pragma once

#include "..\CPU\cpu.h"

class Debugger{
    CPU* cpu;

    public:
    Debugger(CPU* cpu);
    void Registers();
};