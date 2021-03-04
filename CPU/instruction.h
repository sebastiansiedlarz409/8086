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
    ADD_AX_IMM16 = 0x05,    //4
    MOV_AX_IMM16 = 0xB8,    //3
    MOV_AX_RM16 = 0xA1,     //8+EA
    PUSH_AX = 0x50,         //8
    POP_AX = 0x58,          //8
    POP_CX = 0x59,          //8
};