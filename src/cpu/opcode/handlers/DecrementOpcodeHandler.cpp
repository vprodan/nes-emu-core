#pragma once
#include <memory>
#include <stdexcept>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class DecrementOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
public:
    DecrementOpcodeHandler(int cycles, AddressingMode *addressingMode)
        : OpcodeHandler(cycles, addressingMode) {}

    DecrementOpcodeHandler(int cycles, Register<uint8_t> CPU::*operationalRegister)
        : OpcodeHandler(cycles), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        uint8_t value = cpu.bus.read(resolvedAddress->address) - 1;

        cpu.bus.write(resolvedAddress->address, value);

        cpu.P.setAll({
            {Status::Zero, Utils::isZero(value)},
            {Status::Negative, Utils::isNegative(value)},
        });

        return cycles;
    }

    int handle(CPU &cpu) const override
    {
        auto reg = *getOperationalRegister(cpu);

        uint8_t value = reg.read() - 1;

        reg.write(value);

        cpu.P.setAll({
            {Status::Zero, Utils::isZero(value)},
            {Status::Negative, Utils::isNegative(value)},
        });

        return cycles;
    }
};
