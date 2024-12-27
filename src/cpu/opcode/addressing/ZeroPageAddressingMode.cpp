#pragma once
#include <cstdint>
#include <memory>
#include "cpu/opcode/addressing/AddressingMode.hpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
using namespace std;

class ZeroPageAddressingMode : public AddressingMode, public WithOperationalRegister
{
public:
    explicit ZeroPageAddressingMode(Register<uint8_t> CPU::*operationalRegister = nullptr) : WithOperationalRegister(operationalRegister) {}

    unique_ptr<ResolvedAddress> resolve(CPU &cpu) const override
    {
        auto address = cpu.bus.read(cpu.PC.read());

        auto reg = getOperationalRegister(cpu);
        if (reg != nullptr)
        {
            address += reg->read();
        }

        cpu.PC.increment();

        return make_unique<ResolvedAddress>(address);
    }
};