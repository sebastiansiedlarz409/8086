#include <cstdio>

#include "CPU\cpu.h"
#include "Memory\memory.h"

int main()
{
    Memory memory;
    CPU cpu(&memory);

    return 0;
}