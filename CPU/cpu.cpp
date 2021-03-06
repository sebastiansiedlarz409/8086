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

uint8_t CPU::GetOF(uint16_t value1, uint16_t value2){
    if(value1&0x8000 && value2&0x8000 && (AX&0x8000) == 0){
        return 1;
    }
    if((value1&0x8000) == 0 && (value2&0x8000) == 0 && AX&0x8000){
        return 1;
    }

    return 0;
}

uint8_t CPU::GetSF(uint16_t value){
    return value & 0x8000;
}

uint8_t CPU::GetCF(uint16_t value1, uint16_t value2){
    return value1 + value2 > UINT16_MAX ? 1 : 0;
}

uint8_t CPU::GetZF(uint16_t value){
    return value == 0 ? 1 : 0;
}

uint8_t CPU::GetPF(uint16_t value){
    uint8_t counter = 0;

    for(uint8_t i = 0;i<8;i++){
        if(value & (1 << i))
            counter++;
    }

    if(counter % 2){
        return 0;
    }
    else{
        return 1;
    }
}

uint8_t CPU::GetAF(uint16_t value1, uint16_t value2){
    if((value1 & 0xF) + (value2 & 0xF) > 0xF){
        return 1;
    }
    return 0;
}

void CPU::SetFLAGS(uint8_t o, uint8_t s, uint8_t c, uint8_t a, uint8_t p, uint8_t z){
    OF = o;
    SF = s;
    CF = c;
    AF = a;
    PF = p;
    ZF = z;
}

uint16_t& CPU::GetReg16(uint8_t reg){
    if(reg == 0)
        return AX;
    else if(reg == 1)
        return CX;
    else if(reg == 2)
        return DX;
    else if(reg == 3)
        return BX;
    else if(reg == 4)
        return SP;
    else if(reg == 5)
        return BP;
    else if(reg == 6)
        return SI;
    else
        return DI;
}

void CPU::MoveIns16(Memory& mem, uint8_t modrm, uint16_t disp, uint8_t type){
    uint8_t mod = modrm >> 6;
    uint8_t reg = (modrm & 0b00111000) >> 3;
    uint8_t rm = modrm & 0b00000111;

    if(type == 3){  //reg, reg
        GetReg16(rm) = GetReg16(reg);
    }

    else if(type == 2){ //reg, mem
        if(mod == 0){ //mem -> [reg]
            if(reg <= 7) //[reg]
                GetReg16(reg) = Mem_GetWord(mem, DS, GetReg16(rm));
            else{ //[imm16]
                GetReg16(reg) = Mem_GetWord(mem, DS, Mem_GetWord(mem, CS, IP));
                IP+=2;
            }
        }
        if(mod == 1){ //mem -> [reg+disp8]
            GetReg16(reg) = Mem_GetWord(mem, DS, GetReg16(rm)+disp);
        }
        if(mod == 2){ //mem -> [reg+disp16]
            GetReg16(reg) = Mem_GetWord(mem, DS, GetReg16(rm)+disp);
        }
    }

    else if(type == 1) { //mem, reg
        if(mod == 0){ //mem -> [reg]
            if(reg != 0) //mem -> [reg]
                Mem_PutWord(mem, DS, GetReg16(rm), GetReg16(reg));
            else{ //mem -> [imm16]
                Mem_PutWord(mem, DS, Mem_GetWord(mem, CS, IP), Mem_GetWord(mem, CS, IP+2));
                IP+=4;
            }
        }
        if(mod == 1){ //mem -> [reg+disp8]
            Mem_PutWord(mem, DS, GetReg16(rm)+disp, GetReg16(reg));
        }
        if(mod == 2){ //mem -> [reg+disp16]
            Mem_PutWord(mem, DS, GetReg16(rm)+disp, GetReg16(reg));
        }
    }
}

void CPU::Execute(Memory& mem, uint16_t cycle){
    while(cycle > 0){
        uint8_t ins = FetchInstruction(mem, cycle);

        switch (ins)
        {
        case MOV_AX_IMM16:
            MOV_AX_IMM16_INS(*this, mem);
            cycle-=3;
            break;
        case MOV_SI_IMM16:
            MOV_SI_IMM16_INS(*this, mem);
            cycle-=3;
            break;
        case MOV_AX_RM16:
            MOV_AX_RM16_INS(*this, mem);
            cycle-=7; //EA?
            break;
        case MOV_REG16_REG16:
            MOV_REG16_REG16_INS(*this, mem);
            cycle--;
            break;
        case MOV_REG16_MEM16:
            MOV_REG16_MEM16_INS(*this, mem);
            cycle-=8;
            break;
        case MOV_MEM16_IMM16:
            MOV_MEM16_IMM16_INS(*this, mem);
            cycle-=9;
            break;
        case PUSH_AX:
            PUSH_AX_INS(*this, mem);
            cycle-=10;
            break;
        case POP_AX:
            POP_AX_INS(*this, mem);
            cycle-=7;
            break;
        case POP_CX:
            POP_CX_INS(*this, mem);
            cycle-=7;
            break;
        case ADD_AX_IMM16:
            ADD_AX_IMM16_INS(*this, mem);
            cycle-=3;
            break;
        default:
            cycle--;
            break;
        }
    }    
}