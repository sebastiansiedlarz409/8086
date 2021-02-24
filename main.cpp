#include <cstdio>

#include "CPU\cpu.h"
#include "Memory\memory.h"

//https://edge.edx.org/c4x/BITSPilani/EEE231/asset/8086_family_Users_Manual_1_.pdf

int main()
{
    Memory memory;
    CPU cpu(&memory);
    
    return 0;
}