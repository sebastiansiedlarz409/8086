#include "..\..\include\cpu.h"
#include "..\..\include\flags.h"
#include "..\..\include\memory.h"

uint8_t GetOF8(uint8_t value1, uint8_t value2, uint8_t result){
    if(value1&0x80 && value2&0x80 && (result&0x80) == 0)
        return 1;
    if((value1&0x80) == 0 && (value2&0x80) == 0 && result&0x80)
        return 1;

    return 0;
}

uint8_t GetSF8(uint8_t value){
    return value & 0x80;
}

uint8_t GetCF8(uint8_t value1, uint8_t value2){
    return value1 + value2 > UINT8_MAX ? 1 : 0;
}

uint8_t GetZF8(uint8_t value){
    return value == 0 ? 1 : 0;
}

uint8_t GetPF8(uint8_t value){
    uint8_t counter = 0;

    for(uint8_t i = 0;i<8;i++){
        if(value & (1 << i))
            counter++;
    }

    return !(counter % 2);
}

uint8_t GetAF8(uint8_t value1, uint8_t value2){
    return (value1 & 0xF) + (value2 & 0xF) > 0xF;
}

uint8_t GetOF16(uint16_t value1, uint16_t value2, uint16_t result){
    if(value1&0x8000 && value2&0x8000 && (result&0x8000) == 0)
        return 1;
    if((value1&0x8000) == 0 && (value2&0x8000) == 0 && result&0x8000)
        return 1;

    return 0;
}

uint8_t GetSF16(uint16_t value){
    return value & 0x8000;
}

uint8_t GetCF16(uint16_t value1, uint16_t value2){
    return value1 + value2 > UINT16_MAX ? 1 : 0;
}

uint8_t GetZF16(uint16_t value){
    return value == 0 ? 1 : 0;
}

uint8_t GetPF16(uint16_t value){
    uint8_t counter = 0;

    for(uint8_t i = 0;i<8;i++){
        if(value & (1 << i))
            counter++;
    }

    return !(counter % 2);
}

uint8_t GetAF16(uint16_t value1, uint16_t value2){
    return (value1 & 0xF) + (value2 & 0xF) > 0xF;
}