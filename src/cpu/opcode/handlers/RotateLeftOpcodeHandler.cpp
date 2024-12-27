#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class RotateLeftOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
public:
    RotateLeftOpcodeHandler(int cycles, AddressingMode *addressingMode)
        : OpcodeHandler(cycles, addressingMode) {}

    RotateLeftOpcodeHandler(int cycles, Register<uint8_t> CPU::*operationalRegister)
        : OpcodeHandler(cycles), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto value = cpu.bus.read(resolvedAddress->address);
        auto c = cpu.P.isSet(Status::Carry) ? 1 : 0;
        auto isCarry = Utils::isCarryLeft(value);

        value = (value << 1) | c;

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
        auto c = cpu.P.isSet(Status::Carry) ? 1 : 0;
        auto isCarry = Utils::isCarryLeft(value);

        value = (value << 1) | c;

        reg.write(value);

        cpu.P.setAll({
            {Status::Carry, isCarry},
            {Status::Zero, Utils::isZero(value)},
            {Status::Negative, Utils::isNegative(value)},
        });

        return cycles;
    }
};
