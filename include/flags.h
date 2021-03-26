#pragma once

#include "cpu.h"
#include "memory.h"

uint8_t GetOF8(uint8_t value1, uint8_t value2, uint8_t result);
uint8_t GetSF8(uint8_t value);
uint8_t GetCF8(uint8_t value1, uint8_t value2);
uint8_t GetZF8(uint8_t value);
uint8_t GetPF8(uint8_t value);
uint8_t GetAF8(uint8_t value1, uint8_t value2);
uint8_t GetOF16(uint16_t value1, uint16_t value2, uint16_t result);
uint8_t GetSF16(uint16_t value);
uint8_t GetCF16(uint16_t value1, uint16_t value2);
uint8_t GetZF16(uint16_t value);
uint8_t GetPF16(uint16_t value);
uint8_t GetAF16(uint16_t value1, uint16_t value2);