#include "..\CPU\cpu.h"
#include "programmer.h"

void Programmer::Program(CPU* cpu, uint8_t* byte_code, uint32_t size){
    Memory* memory = cpu->GetMemory();

    uint16_t ss = (byte_code[15]<<8)|byte_code[14];
    uint16_t sp = (byte_code[17]<<8)|byte_code[16];

    uint16_t ip = (byte_code[21]<<8)|byte_code[20];
    uint16_t cs = (byte_code[23]<<8)|byte_code[22];

    cpu->SS = ss;
    cpu->SP = sp;

    cpu->CS = cs;
    cpu->IP = ip;

    for(uint32_t i = 30; i < size; i++){
        cpu->Mem_PutByte(cpu->cs, 0, byte_code[i]);
    }

    cpu->Mem_PutWord(0xFFFF, 0, 0);

    cpu->Reset();
}