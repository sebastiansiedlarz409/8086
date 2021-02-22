#include "memory.h"

uint8_t& Memory::operator[](uint16_t address){
    return space[address];
}