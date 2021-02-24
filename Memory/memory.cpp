#include "memory.h"

Memory::Memory(){
    for(uint32_t i = 0;i < MemorySize;i++){
        space[i] = 0;
    }
}

uint8_t& Memory::operator[](uint16_t address){
    return space[address];
}