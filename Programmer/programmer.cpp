#include "..\CPU\cpu.h"
#include "programmer.h"

void Programmer::Program(CPU* cpu, uint8_t* byte_code, uint32_t size){
    Memory* memory = cpu->GetMemory();
}