#pragma once

enum Instructions{
    MOV_AX_IMM16 = 0xA1,
    PUSH_AX = 0x50,
    POP_AX = 0x58,
    POP_CX = 0x59,
};