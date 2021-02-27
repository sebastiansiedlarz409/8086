#include "memory.h"

Memory::Memory(){
    //space = new uint8_t[MemorySize];

    for(uint32_t i = 0;i < MemorySize;i++){
        space[i] = 0;
    }
}

uint8_t& Memory::operator[](uint32_t address){
    //return space[address];
    return *(space+address);
}

uint8_t Memory::operator[](uint32_t address) const{
    //return space[address];
    return *(space+address);
}