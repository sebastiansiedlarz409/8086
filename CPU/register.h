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