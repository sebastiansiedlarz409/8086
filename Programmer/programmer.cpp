#include <vector>
#include <cstdio>

#include "..\CPU\cpu.h"
#include "programmer.h"

void Programmer::Program(CPU& cpu, Memory& mem, std::vector<uint8_t> byte_code){

    cpu.Reset(mem);

    uint16_t ss = (byte_code[15]<<8)|byte_code[14];
    uint16_t sp = (byte_code[17]<<8)|byte_code[16];

    uint16_t ip = (byte_code[21]<<8)|byte_code[20];
    uint16_t cs = (byte_code[23]<<8)|byte_code[22];

    cpu.SS = ss;
    printf("Set SS: 0x%04x\r\n", cpu.SS);
    cpu.SP = sp;
    printf("Set SP: 0x%04x\r\n", cpu.SP);

    cpu.CS = cs;
    printf("Set CS: 0x%04x\r\n", cpu.CS);

    uint16_t code_p = 0;
    for(uint32_t i = 30; i < byte_code.size(); i++){
        printf("\rPrograming: 0x%08x", cpu.CalculateAddress(cpu.CS, code_p));
        cpu.Mem_PutByte(mem, cs, code_p, byte_code[i]);
        code_p++;
    }

    cpu.Mem_PutWord(mem, 0xFFFF, 0, ip);     //reset vector
    printf("\n\rProgrammed %llu bytes\n\r", byte_code.size()-30);
}