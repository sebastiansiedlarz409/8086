#pragma once

#include "..\CPU\cpu.h"
#include "..\Memory\memory.h"

class Debugger{
    public:
    void Registers(CPU& cpu, Memory& mem);
};