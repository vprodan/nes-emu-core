#pragma once
#include <cstdint>
#include <memory>
#include "cpu/CPU.cpp"
using namespace std;

struct ResolvedAddress
{
    uint16_t address{};
    bool crossedBoundary = false;
};

enum AddressingModeType
{
    Immediate,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    Indirect,
    IndirectX,
    IndirectY,
    Relative,
    ZeroPage,
    ZeroPageX,
    ZeroPageY,
};

class AddressingMode
{
public:
    virtual ~AddressingMode() = default;

    virtual unique_ptr<ResolvedAddress> resolve(CPU &cpu) const = 0;
};