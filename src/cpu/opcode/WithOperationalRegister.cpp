#pragma once
#include <cstdint>
#include "cpu/opcode/addressing/AddressingMode.hpp"
#include "cpu/CPU.cpp"
using namespace std;

class WithOperationalRegister
{
public:
    WithOperationalRegister(Register<uint8_t> CPU::*operationalRegister = nullptr) : operationalRegister(operationalRegister) {}

    Register<uint8_t> *getOperationalRegister(CPU &cpu) const
    {
        if (operationalRegister == nullptr)
        {
            return nullptr;
        }

        return &(cpu.*operationalRegister);
    }

private:
    Register<uint8_t> CPU::*operationalRegister;
};
