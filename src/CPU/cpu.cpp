#include "..\..\include\cpu.h"
#include "..\..\include\instructions.h"
#include "..\..\include\memory.h"

#include <cstdio>

void CPU::Reset(Memory& mem){
    DS = ES = SS = 0x3000;

    AX = BX = CX = DX = 0;

    IP = Mem_GetWord(mem, 0xFFFF, 0);

    BP = 0;
    SP = 0;

    DI = SI = 0;

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

void CPU::FetchInstruction(Memory& mem, int16_t& cycle){
    if(code_size<IP){
        cur_instruction = -1;
        return;
    }
    
    if(fetch_ip == 0){
        cur_instruction = Mem_GetByte(mem, CS, IP);
        IP++;
        for(uint8_t i = 0; i<6;i++){
            fetch_buffer.push(Mem_GetByte(mem, CS, IP+i));
        }
        fetch_ip = IP+6;
    }
    else{
        cur_instruction = fetch_buffer.front();
        IP++;
        fetch_buffer.pop();
        if(fetch_buffer.size() <= 4){
            while(fetch_buffer.size() < 6){
                fetch_buffer.push(Mem_GetByte(mem, CS, fetch_ip));
                fetch_ip++;
            }
        }
    }
    cycle--;
}

void CPU::ClearFetchedBuffer(){
    while(!fetch_buffer.empty())
        fetch_buffer.pop();
    fetch_ip = 0;
}

uint8_t CPU::GetFetchedByte(){
    uint8_t value = fetch_buffer.front();
    fetch_buffer.pop();
    return value;
}

uint16_t CPU::GetFetchedWord(){
    uint8_t lsb = GetFetchedByte();
    uint8_t msb = GetFetchedByte();
    uint16_t value = (msb<<8)|lsb;
    return value;
}

void CPU::SetFLAGS(uint8_t o, uint8_t s, uint8_t c, uint8_t a, uint8_t p, uint8_t z){
    OF = o;
    SF = s;
    CF = c;
    AF = a;
    PF = p;
    ZF = z;
}

uint8_t& CPU::GetReg8(uint8_t reg){
    if(reg == 0)
        return AL;
    else if(reg == 1)
        return CL;
    else if(reg == 2)
        return DL;
    else if(reg == 3)
        return BL;
    else if(reg == 4)
        return AH;
    else if(reg == 5)
        return CH;
    else if(reg == 6)
        return DH;
    else
        return BH;
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

uint16_t& CPU::OffsetReg(uint8_t reg){
    if(reg == 4)
        return SI;
    else if(reg == 5)
        return DI;
    else if(reg == 6)
        return BP;
    else
        return BX;
}

uint16_t& CPU::SegReg(uint8_t reg){
    if(reg == 0)
        return ES;
    else if(reg == 1)
        return CS;
    else if(reg == 2)
        return SS;
    else
        return DS;
}

void CPU::MoveIns8(Memory& mem, uint8_t modrm, uint16_t disp, uint8_t type){
    uint8_t mod = modrm >> 6;
    uint8_t reg = (modrm & 0b00111000) >> 3;
    uint8_t rm = modrm & 0b00000111;

    if(type == 3){  //reg, reg
        GetReg8(rm) = GetReg8(reg);
    }

    else if(type == 2){ //reg, mem
        if(mod == 0){ //mem -> [reg]
            if(reg <= 7) //[reg]
                GetReg16(reg) = Mem_GetWord(mem, DS, OffsetReg(rm));
            else{ //[imm16]
                GetReg16(reg) = Mem_GetWord(mem, DS, GetFetchedWord());
                IP+=2;
            }
        }
        if(mod == 1){ //mem -> [reg+disp8]
            GetReg16(reg) = Mem_GetWord(mem, DS, OffsetReg(rm)+disp);
        }
        if(mod == 2){ //mem -> [reg+disp16]
            GetReg16(reg) = Mem_GetWord(mem, DS, OffsetReg(rm)+disp);
        }
    }

    else if(type == 1) { //mem, reg
        if(mod == 0){ //mem -> [reg]
            if(reg != 0) //mem -> [reg]
                Mem_PutWord(mem, DS, GetReg16(rm), GetReg16(reg));
            else{ //mem -> [imm16]
                if(rm == 6){
                    uint16_t offset = GetFetchedWord();
                    IP+=2;
                    uint8_t value = GetFetchedByte();
                    Mem_PutWord(mem, DS, offset, value);
                    IP+=2;
                }
                else{
                    uint8_t value = GetFetchedByte();
                    Mem_PutWord(mem, DS, OffsetReg(rm), value);
                    IP+=2;
                }
            }
        }
        if(mod == 1){ //mem -> [reg+disp8]
            if(reg != 0)
                Mem_PutWord(mem, DS, GetReg16(rm)+disp, GetReg16(reg));
            else{
                uint8_t value = GetFetchedByte();
                Mem_PutWord(mem, DS, OffsetReg(rm)+disp, value);
                IP++;
            }
        }
        if(mod == 2){ //mem -> [reg+disp16]
            if(reg != 0)
                Mem_PutWord(mem, DS, OffsetReg(rm)+disp, GetReg16(reg));
            else{
                uint8_t value = GetFetchedByte();
                Mem_PutWord(mem, DS, OffsetReg(rm)+disp, value);
                IP++;   
            }
        }
    }
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
            if(reg <= 7){ //[reg]
                GetReg16(reg) = Mem_GetWord(mem, DS, OffsetReg(rm));
            }
            else{ //[imm16]
                GetReg16(reg) = Mem_GetWord(mem, DS, GetFetchedWord());
                IP+=2;
            }
        }
        if(mod == 1){ //mem -> [reg+disp8]
            GetReg16(reg) = Mem_GetWord(mem, DS, OffsetReg(rm)+disp);
        }
        if(mod == 2){ //mem -> [reg+disp16]
            GetReg16(reg) = Mem_GetWord(mem, DS, OffsetReg(rm)+disp);
        }
    }

    else if(type == 1) { //mem, reg
        if(mod == 0){ //mem -> [reg]
            if(reg != 0){ //mem -> [reg]
                Mem_PutWord(mem, DS, GetReg16(rm), GetReg16(reg));
            }
            else{ //mem -> [imm16]
                if(rm == 6){
                    uint16_t offset = GetFetchedWord();
                    IP+=2;
                    uint16_t value = GetFetchedWord();
                    Mem_PutWord(mem, DS, offset, value);
                    IP+=2;
                }
                else{
                    uint16_t value = GetFetchedWord();
                    Mem_PutWord(mem, DS, OffsetReg(rm), value);
                    IP+=2;
                }
            }
        }
        if(mod == 1){ //mem -> [reg+disp8]
            if(reg != 0)
                Mem_PutWord(mem, DS, OffsetReg(rm)+disp, GetReg16(reg));
            else{
                uint16_t value = GetFetchedWord();
                Mem_PutWord(mem, DS, OffsetReg(rm)+disp, value);
                IP+=2; 
            }    
        }
        if(mod == 2){ //mem -> [reg+disp16]
            if(reg != 0)
                Mem_PutWord(mem, DS, OffsetReg(rm)+disp, GetReg16(reg));
            else{
                uint16_t value = GetFetchedWord();
                Mem_PutWord(mem, DS, OffsetReg(rm)+disp, value);
                IP+=2; 
            }
        }
    }
}

void CPU::Execute(Memory& mem, int16_t cycle){
    while(cycle > 0){
        FetchInstruction(mem, cycle);

        switch (cur_instruction){
        case MOV_AL_IMM8:
            MOV_AL_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_CL_IMM8:
            MOV_CL_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_DL_IMM8:
            MOV_DL_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_BL_IMM8:
            MOV_BL_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_AH_IMM8:
            MOV_AH_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_CH_IMM8:
            MOV_CH_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_DH_IMM8:
            MOV_DH_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_BH_IMM8:
            MOV_BH_IMM8_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_AX_IMM16:
            MOV_AX_IMM16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_CX_IMM16:
            MOV_CX_IMM16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_DX_IMM16:
            MOV_DX_IMM16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_BX_IMM16:
            MOV_BX_IMM16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_SP_IMM16:
            MOV_SP_IMM16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_BP_IMM16:
            MOV_BP_IMM16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_SI_IMM16:
            MOV_SI_IMM16_INS(*this, mem);
            cycle-=3;
            break;
        case MOV_DI_IMM16:
            MOV_DI_IMM16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_AL_RM8:
            MOV_AL_RM8_INS(*this, mem);
            cycle-=7; //EA?
            break;
        case MOV_MEM8_AL:
            MOV_MEM8_AL_INS(*this, mem);
            cycle-=8; //EA?
            break;
        case MOV_MEM16_AX:
            MOV_MEM16_AX_INS(*this, mem);
            cycle-=8; //EA?
            break;
        case MOV_AX_RM16:
            MOV_AX_RM16_INS(*this, mem);
            cycle-=7; //EA?
            break;
        case MOV_REG8_REG8:
            MOV_REG8_REG8_INS(*this, mem);
            cycle--;
            break;
        case MOV_REG16_REG16:
            MOV_REG16_REG16_INS(*this, mem);
            cycle--;
            break;
        case MOV_REG16_MEM16:
            MOV_REG16_MEM16_INS(*this, mem);
            cycle-=8;
            break;
        case MOV_REG16_MEM8:
            MOV_REG16_MEM8_INS(*this, mem);
            cycle-=8;
            break;
        case MOV_MEM8_IMM8:
            MOV_MEM8_IMM8_INS(*this, mem);
            cycle-=9;
            break;
        case MOV_MEM16_IMM16:
            MOV_MEM16_IMM16_INS(*this, mem);
            cycle-=9;
            break;
        case MOV_SREG_REG16:
            MOV_SREG_REG16_INS(*this, mem);
            cycle-=2;
            break;
        case MOV_REG16_SREG:
            MOV_REG16_SREG_INS(*this, mem);
            cycle-=2;
            break;
        case MOVSB:
            MOVSB_INS(*this, mem);
            cycle-=17;
            break;
        case MOVSW:
            MOVSW_INS(*this, mem);
            cycle-=17;
            break;
        case STOSB:
            STOSB_INS(*this, mem);
            cycle-=10;
            break;
        case STOSW:
            STOSW_INS(*this, mem);
            cycle-=18;
            break;
        case CLD:
            CLD_INS(*this, mem);
            cycle-=2;
            break;
        case STD:
            STD_INS(*this, mem);
            cycle-=2;
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
        case ADD_AL_IMM8:
            ADD_AL_IMM8_INS(*this, mem);
            cycle-=3;
            break;
        case ADD_AX_IMM16:
            ADD_AX_IMM16_INS(*this, mem);
            cycle-=3;
            break;
        case ADD_REG16_IMM16:
            ADD_REG16_IMM16_INS(*this, mem);
            cycle-=4;
            break;
        case DEC_AX:
            DEC_AX_INS(*this, mem);
            cycle-=2;
            break;
        case INC_AX:
            INC_AX_INS(*this, mem);
            cycle-=2;
            break;
        case JZ:
            JZ_INS(*this, mem);
            cycle-=16;
            break;
        case JNZ:
            JNZ_INS(*this, mem);
            cycle-=16;
            break;
        case NOP:
            cycle--;
            break;
        default:
            cycle--;
            IP--;       //no move forward
            break;
        }
    }    
}