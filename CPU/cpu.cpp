#include "cpu.h"
#include "..\Memory\memory.h"

CPU::CPU(Memory* memory){
    memory = memory;
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