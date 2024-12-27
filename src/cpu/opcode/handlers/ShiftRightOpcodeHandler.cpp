#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class ShiftRightOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
public:
    ShiftRightOpcodeHandler(int cycles, AddressingMode *addressingMode)
        : OpcodeHandler(cycles, addressingMode) {}

    ShiftRightOpcodeHandler(int cycles, Register<uint8_t> CPU::*operationalRegister)
        : OpcodeHandler(cycles), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto value = cpu.bus.read(resolvedAddress->address);
        auto isCarry = Utils::isCarryRight(value);

        value = value >> 1;

        cpu.bus.write(resolvedAddress->address, value);

        cpu.P.setAll({
            {Status::Carry, isCarry},
            {Status::Zero, Utils::isZero(value)},
            {Status::Negative, Utils::isNegative(value)},
        });

        return cycles;
    }

    int handle(CPU &cpu) const override
    {
        auto reg = *getOperationalRegister(cpu);

        auto value = reg.read();
        auto isCarry = Utils::isCarryRight(value);

        value = value >> 1;

        reg.write(value);

        cpu.P.setAll({
            {Status::Carry, isCarry},
            {Status::Zero, Utils::isZero(value)},
            {Status::Negative, Utils::isNegative(value)},
        });

        return cycles;
    }
};
