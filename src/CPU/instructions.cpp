#include "..\..\include\cpu.h"
#include "..\..\include\instructions.h"
#include "..\..\include\memory.h"

uint16_t buffer16;
uint16_t buffer16_1;
uint8_t buffer8;

void MOV_AX_IMM16_INS(CPU& cpu, Memory& mem){
    buffer16 = cpu.GetFetchedWord();
    cpu.IP+=2;
    cpu.AX = buffer16;
}

void MOV_SI_IMM16_INS(CPU& cpu, Memory& mem){
    buffer16 = cpu.GetFetchedWord();
    cpu.IP+=2;
    cpu.SI = buffer16;
}

void PUSH_AX_INS(CPU& cpu, Memory& mem){
    buffer16 = cpu.AX;
    cpu.Push(mem, buffer16);
}

void POP_AX_INS(CPU& cpu, Memory& mem){
    cpu.AX = cpu.Pop(mem);
}

void POP_CX_INS(CPU& cpu, Memory& mem){
    cpu.CX = cpu.Pop(mem);
}

void ADD_AX_IMM16_INS(CPU& cpu, Memory& mem){
    buffer16 = cpu.GetFetchedWord();
    cpu.IP+=2;
    buffer16_1 = cpu.AX;
    cpu.AX += buffer16;
    cpu.SetFLAGS(
        cpu.GetOF(buffer16, buffer16_1),
        cpu.GetSF(cpu.AX),
        cpu.GetCF(buffer16, buffer16_1),
        cpu.GetAF(buffer16, buffer16_1),
        cpu.GetPF(cpu.AX),
        cpu.GetZF(cpu.AX)
    );
}

void ADD_REG16_IMM16_INS(CPU& cpu, Memory& mem){
    buffer8 = cpu.GetFetchedByte();
    cpu.IP++;

    buffer16 = cpu.GetFetchedWord();
    cpu.IP+=2;
    buffer16_1 = cpu.GetReg16(buffer8 & 0b00000111);    //reg
    cpu.GetReg16(buffer8 & 0b00000111) += buffer16;
    cpu.SetFLAGS(
        cpu.GetOF(buffer16, buffer16_1),
        cpu.GetSF(buffer16_1),
        cpu.GetCF(buffer16, buffer16_1),
        cpu.GetAF(buffer16, buffer16_1),
        cpu.GetPF(buffer16_1),
        cpu.GetZF(buffer16_1)
    );
}

void MOV_AX_RM16_INS(CPU& cpu, Memory& mem){
    buffer16 = cpu.GetFetchedWord();
    cpu.IP+=2;
    buffer16_1 = cpu.Mem_GetWord(mem, cpu.DS, buffer16);
    cpu.AX = buffer16_1;
}

void MOV_REG16_MEM16_INS(CPU& cpu, Memory& mem){
    buffer8 = cpu.GetFetchedByte();
    cpu.IP++;

    uint8_t mod = buffer8 >> 6;
    uint16_t disp = 0;
    if(mod == 1){
        disp = cpu.GetFetchedByte();
        cpu.IP++;
    }
    else if(mod == 2){
        disp = cpu.GetFetchedWord();
        cpu.IP+=2;
    }

    cpu.MoveIns16(mem, buffer8, disp, 1);
}

void MOV_MEM16_IMM16_INS(CPU& cpu, Memory& mem){ 
    buffer8 = cpu.GetFetchedByte();
    cpu.IP++;

    uint8_t mod = buffer8 >> 6;
    uint16_t disp = 0;
    if(mod == 1){
        disp = cpu.GetFetchedByte();
        cpu.IP++;
    }
    else if(mod == 2){
        disp = cpu.GetFetchedWord();
        cpu.IP+=2;
    }
    
    cpu.MoveIns16(mem, buffer8, disp, 1);
}

void MOV_REG16_REG16_INS(CPU& cpu, Memory& mem){
    buffer8 = cpu.GetFetchedByte();
    cpu.IP++;
    
    cpu.MoveIns16(mem, buffer8, 0, 3); //3 means both operand are regs
}

void DEC_AX_INS(CPU& cpu, Memory& mem){
    cpu.AX--;
    cpu.SetFLAGS(
        cpu.GetOF(1, cpu.AX+1),
        cpu.GetSF(cpu.AX),
        cpu.CF,
        cpu.GetAF(1, cpu.AX+1),
        cpu.GetPF(cpu.AX),
        cpu.GetZF(cpu.AX)
    );
}

void INC_AX_INS(CPU& cpu, Memory& mem){
    cpu.AX++;
    cpu.SetFLAGS(
        cpu.GetOF(1, cpu.AX-1),
        cpu.GetSF(cpu.AX),
        cpu.CF,
        cpu.GetAF(1, cpu.AX-1),
        cpu.GetPF(cpu.AX),
        cpu.GetZF(cpu.AX)
    );
}

void JZ_INS(CPU& cpu, Memory& mem){
    if(cpu.ZF){
        uint8_t offset = cpu.GetFetchedByte();
        if(offset > 127){
            cpu.IP -= (255 - offset);
        }
        else{
            cpu.IP += offset+1;
        }
        cpu.ClearFetchedBuffer();
    }
    else{
        cpu.IP++; //skip rel8
    }
}

void JNZ_INS(CPU& cpu, Memory& mem){
    if(!cpu.ZF){
        uint8_t offset = cpu.GetFetchedByte();
        if(offset > 127){
            cpu.IP -= (255 - offset);
        }
        else{
            cpu.IP += offset+1;
        }
        cpu.ClearFetchedBuffer();
    }
    else{
        cpu.IP++; //skip rel8
    }
}