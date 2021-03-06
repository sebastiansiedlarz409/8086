#pragma once

//EA
//Displacement                                            6
//Base or Index (BX,BP,SI,DI)                             5
//Displacement+(Base or Index)                            9
//Base+Index (BP+DI,BX+SI)                                7
//Base+Index (BP+SI,BX+DI)                                8
//Base+Index+Displacement (BP+DI,BX+SI)                  11
//Base+Index+Displacement (BP+SI+disp,BX+DI+disp)        12

//- add 4 cycles for word operands at odd addresses
//- add 2 cycles for segment override
//- 80188/80186 timings differ from those of the 8088/8086/80286

enum Instructions{
    ADD_AX_IMM16 = 0x05,        //4
    MOV_AX_IMM16 = 0xB8,        //3
    MOV_SI_IMM16 = 0xBE,        //3
    MOV_AX_RM16 = 0xA1,         //8+EA
    MOV_REG16_REG16 = 0x89,     //2
    MOV_MEM16_IMM16 = 0xC7,     //10+EA
    MOV_REG16_MEM16 = 0x8B,     //8+EA
    PUSH_AX = 0x50,             //8
    POP_AX = 0x58,              //8
    POP_CX = 0x59,              //8
};

uint16_t buffer16;
uint16_t buffer16_1;
uint8_t buffer8;

auto MOV_AX_IMM16_INS = 
[]
(CPU& cpu, Memory& mem)
{
    buffer16 = cpu.Mem_GetWord(mem, cpu.CS, cpu.IP);
    cpu.IP+=2;
    cpu.AX = buffer16;
};

auto MOV_SI_IMM16_INS = 
[]
(CPU& cpu, Memory& mem)
{
    buffer16 = cpu.Mem_GetWord(mem, cpu.CS, cpu.IP);
    cpu.IP+=2;
    cpu.SI = buffer16;
};

auto PUSH_AX_INS =
[]
(CPU& cpu, Memory& mem)
{
    buffer16 = cpu.AX;
    cpu.Push(mem, buffer16);
};

auto POP_AX_INS = 
[]
(CPU& cpu, Memory& mem)
{
    cpu.AX = cpu.Pop(mem);
};

auto POP_CX_INS = 
[]
(CPU& cpu, Memory& mem)
{
    cpu.CX = cpu.Pop(mem);
};

auto ADD_AX_IMM16_INS =
[]
(CPU& cpu, Memory& mem)
{
    buffer16 = cpu.Mem_GetWord(mem, cpu.CS, cpu.IP);
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
};

auto MOV_AX_RM16_INS = 
[]
(CPU& cpu, Memory& mem)
{
    buffer16 = cpu.Mem_GetWord(mem, cpu.CS, cpu.IP); //addr
    cpu.IP+=2;
    buffer16_1 = cpu.Mem_GetWord(mem, cpu.DS, buffer16);
    cpu.AX = buffer16_1;
};

auto MOV_REG16_MEM16_INS =
[]
(CPU& cpu, Memory& mem)
{
    buffer8 = cpu.Mem_GetByte(mem, cpu.CS, cpu.IP);
    cpu.IP++;

    uint8_t mod = buffer8 >> 6;
    uint16_t disp = 0;
    if(mod == 1){
        disp = cpu.Mem_GetByte(mem, cpu.CS, cpu.IP);
        cpu.IP++;
    }
    else if(mod == 2){
        disp = cpu.Mem_GetWord(mem, cpu.CS, cpu.IP);
        cpu.IP+=2;
    }

    cpu.MoveIns16(mem, buffer8, disp, 1);
};

auto MOV_MEM16_IMM16_INS =
[]
(CPU& cpu, Memory& mem)
{ 
    buffer8 = cpu.Mem_GetByte(mem, cpu.CS, cpu.IP);
    cpu.IP++;

    uint8_t mod = buffer8 >> 6;
    uint16_t disp = 0;
    if(mod == 1){
        disp = cpu.Mem_GetByte(mem, cpu.CS, cpu.IP);
        cpu.IP++;
    }
    else if(mod == 2){
        disp = cpu.Mem_GetWord(mem, cpu.CS, cpu.IP);
        cpu.IP+=2;
    }
    
    cpu.MoveIns16(mem, buffer8, disp, 1);
};

auto MOV_REG16_REG16_INS =
[]
(CPU& cpu, Memory& mem)
{
    buffer8 = cpu.Mem_GetByte(mem, cpu.CS, cpu.IP);
    cpu.IP++;
    cpu.MoveIns16(mem, buffer8, 0, 3); //3 means both operand are regs
};