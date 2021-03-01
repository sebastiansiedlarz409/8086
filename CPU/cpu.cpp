#include "cpu.h"
#include "instruction.h"
#include "..\Memory\memory.h"

void CPU::Reset(Memory& mem){
    //default segments
    DS = ES = SS = 0;

    AX = BX = CX = DX = 0;

    IP = Mem_GetWord(mem, 0xFFFF, 0);

    BP = SP;

    DI = SI = 0;

    //flags
    TF = DF = IF = OF = 0;
    SF = ZF = AF = PF = CF = 0;
}

uint32_t CPU::CalculateAddress(uint16_t segment, uint16_t address){
    return (segment<<4)+address;
}

void CPU::Mem_PutByte(Memory& mem, uint16_t segment, uint16_t address, uint8_t value){
    mem[CalculateAddress(segment, address)] = value;
}

void CPU::Mem_PutWord(Memory& mem, uint16_t segment, uint16_t address, uint16_t value){
    mem[CalculateAddress(segment, address)] = (uint8_t)value&0xff;
    mem[CalculateAddress(segment, ++address)] = (uint8_t)((value >> 8)&0xff);
}

uint8_t CPU::Mem_GetByte(const Memory& mem, uint16_t segment, uint16_t address){
    return mem[CalculateAddress(segment, address)];
}

uint16_t CPU::Mem_GetWord(const Memory& mem, uint16_t segment, uint16_t address){
    uint8_t lsb = mem[CalculateAddress(segment, address)];
    uint8_t msb = mem[CalculateAddress(segment, ++address)];
    return (msb<<8)|lsb;
}

void CPU::Push(Memory& mem, uint16_t value){
    SP-=2;
    Mem_PutWord(mem, SS, SP, value);
}

uint16_t CPU::Pop(Memory& mem){
    uint16_t value = Mem_GetWord(mem, SS, SP);
    SP+=2;
    return value;
}

uint8_t CPU::FetchInstruction(Memory& mem, uint16_t& cycle){
    uint8_t value = Mem_GetByte(mem, CS, IP);
    cycle--;
    IP++;
    return value;
}

void CPU::Execute(Memory& mem, uint16_t cycle){
    uint16_t buffer16[4];
    uint8_t buffer8[4];

    while(cycle){
        uint8_t ins = FetchInstruction(mem, cycle);

        switch (ins)
        {
        case MOV_AX_IMM16:
            buffer16[0] = Mem_GetWord(mem, CS, IP);
            IP+=2;
            cycle-=2;
            AX = buffer16[0];
            cycle--;
            break;
        case PUSH_AX:
            buffer16[0] = AX;
            cycle-=5;
            Push(mem, buffer16[0]);
            cycle-=5;
            break;
        case POP_AX:
            AX = Pop(mem);
            cycle-=8;
            break;
        case POP_CX:
            CX = Pop(mem);
            cycle-=8;
            break;
        default:
            //cycle--;
            break;
        }
    }    
}