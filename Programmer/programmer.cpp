#include "..\CPU\cpu.h"
#include "programmer.h"

void Programmer::Program(CPU& cpu, Memory& mem, uint8_t* byte_code, uint32_t size){

    uint16_t ss = (byte_code[15]<<8)|byte_code[14];
    uint16_t sp = (byte_code[17]<<8)|byte_code[16];

    uint16_t ip = (byte_code[21]<<8)|byte_code[20];
    uint16_t cs = (byte_code[23]<<8)|byte_code[22];

    cpu.SS = ss;
    cpu.SP = sp;

    cpu.CS = cs;
    cpu.IP = ip;

    uint16_t code_p = 0;
    for(uint32_t i = 30; i < size; i++){
        cpu.Mem_PutByte(mem, cpu.cs, code_p, byte_code[i]);
        code_p++;
    }

    cpu.Mem_PutWord(mem, 0, 0, 0);     //reset vector

    cpu.Reset(mem);
}