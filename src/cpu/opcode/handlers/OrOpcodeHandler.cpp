#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class OrOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
public:
    OrOpcodeHandler(int cycles, AddressingMode *addressingMode, Register<uint8_t> CPU::*operationalRegister = &CPU::A)
        : OpcodeHandler(cycles, addressingMode), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto reg = *getOperationalRegister(cpu);

        uint8_t value = reg.read() | cpu.bus.read(resolvedAddress->address);

        reg.write(value);

        cpu.P.setAll({
            {Status::Zero, Utils::isZero(value)},
            {Status::Negative, Utils::isNegative(value)},
        });

        return cycles + (resolvedAddress->crossedBoundary ? 1 : 0);
    }
};
