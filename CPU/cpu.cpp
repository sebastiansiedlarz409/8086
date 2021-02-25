#include "cpu.h"
#include "..\Memory\memory.h"

CPU::CPU(Memory* memory){
    memory = memory;
}

void CPU::Reset(){
    //default segments
    DS = ES = SS = 0;
    CS = 0xFFFF;

    AX = BX = CX = DX = 0;

    IP = Mem_GetWord(0xFFFF, 0);

    SP = 0xFFFD;
    BP = SP;

    DI = SI = 0;

    //flags
    TF = DF = IF = OF = 0;
    SF = ZF = AF = PF = CF = 0;
}

uint32_t CPU::CalculateAddress(uint16_t segment, uint16_t address){
    return (segment<<4)|address;
}

void CPU::Mem_PutByte(uint16_t segment, uint16_t address, uint8_t value){
    (*memory)[CalculateAddress(segment, address)] = value;
}

void CPU::Mem_PutWord(uint16_t segment, uint16_t address, uint16_t value){
    (*memory)[CalculateAddress(segment, address)] = (uint8_t)value&0xff;
    (*memory)[CalculateAddress(segment, ++address)] = (uint8_t)((value >> 8)&0xff);
}

uint8_t CPU::Mem_GetByte(uint16_t segment, uint16_t address){
    return (*memory)[CalculateAddress(segment, address)];
}

uint16_t CPU::Mem_GetWord(uint16_t segment, uint16_t address){
    uint8_t lsb = (*memory)[CalculateAddress(segment, address)];
    uint8_t msb = (*memory)[CalculateAddress(segment, ++address)];
    return (msb<<8)|lsb;
}

void CPU::Push(uint16_t value){
    Mem_PutWord(SS, SP, value);
    SP-=2;
}

uint16_t CPU::Pop(){
    uint16_t value = Mem_GetWord(SS, SP);
    SP+=2;
    return value;
}

Memory* CPU::GetMemory(){
    return memory;
}