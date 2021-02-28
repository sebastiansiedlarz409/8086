#pragma once

#include <cstdint>

class Registers{
    public:
    union
    {
        uint16_t AX;
        struct{
            uint8_t AL;
            uint8_t AH;
        };
    };

    union
    {
        uint16_t BX;
        struct{
            uint8_t BL;
            uint8_t BH;
        };
    };

    union
    {
        uint16_t CX;
        struct{
            uint8_t CL;
            uint8_t CH;
        };
    };

    union
    {
        uint16_t DX;
        struct{
            uint8_t DL;
            uint8_t DH;
        };
    };

    //P(22) EFLAGS
    struct{
        uint8_t NU16 : 1;
        uint8_t NU15 : 1;
        uint8_t NU14 : 1;
        uint8_t NU13 : 1;
        uint8_t NU12 : 1;
        uint8_t OF : 1; //overflow
        uint8_t DF : 1; //direction
        uint8_t IF : 1; //interrupt enable
        uint8_t TF : 1; //trap
        uint8_t SF : 1; //sign
        uint8_t ZF : 1; //zero
        uint8_t NU5 : 1;
        uint8_t AF : 1; //auxiliary
        uint8_t NU3 : 1;
        uint8_t PF : 1; //parity
        uint8_t NU1 : 1; 
        uint8_t CF : 1; //cary
    };

    //P(22)
    uint16_t IP;

    uint16_t CS;
    uint16_t DS;
    uint16_t ES;
    uint16_t SS;

    uint16_t BP;
    uint16_t SP;
    uint16_t DI;
    uint16_t SI;
};