#pragma once

#include <cstdint>

union AX_R
{
    uint16_t AX_R;
    struct{
        uint8_t AL_R;
        uint8_t AH_R;
    };
};

union BX_R
{
    uint16_t BX_R;
    struct{
        uint8_t BL_R;
        uint8_t BH_R;
    };
};

union CX_R
{
    uint16_t CX_R;
    struct{
        uint8_t CL_R;
        uint8_t CH_R;
    };
};

union DX_R
{
    uint16_t DX_R;
    struct{
        uint8_t DL_R;
        uint8_t DH_R;
    };
};

struct SP_R
{
    uint16_t SP_R;
};

struct BP_R
{
    uint16_t BP_R;
};

struct SI_R
{
    uint16_t SI_R;
};

struct DI_R
{
    uint16_t DI_R;
};

struct CS_R
{
    uint16_t CS_R;
};

struct DS_R
{
    uint16_t DS_R;
};

struct SS_R
{
    uint16_t SS_R;
};

struct ES_R
{
    uint16_t ES_R;
};

struct IP_R
{
    uint16_t IP_R;
};