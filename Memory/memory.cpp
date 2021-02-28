#include "memory.h"

#include <assert.h>

Memory::Memory(){
    for(uint32_t i = 0;i < MemorySize;i++){
        space[i] = 0;
    }
}

uint8_t& Memory::operator[](uint32_t address){
    //too high address -> int
    return *(space+address);
}

uint8_t Memory::operator[](uint32_t address) const{
    //too high address -> int
    return *(space+address);
}