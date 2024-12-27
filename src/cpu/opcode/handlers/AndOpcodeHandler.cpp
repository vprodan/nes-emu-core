#pragma once
#include <cstdint>
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class AndOpcodeHandler : public OpcodeHandler, WithOperationalRegister
{
public:
    AndOpcodeHandler(int cycles, AddressingMode *addressingMode, Register<uint8_t> CPU::*operationalRegister = &CPU::A)
        : OpcodeHandler(cycles, addressingMode), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto reg = *getOperationalRegister(cpu);
        auto result = reg.read() & cpu.bus.read(resolvedAddress->address);
        reg.write(result);

        cpu.P.setAll({
            {Zero, Utils::isZero(result)},
            {Negative, Utils::isNegative(result)},
        });

        return cycles + (resolvedAddress->crossedBoundary ? 1 : 0);
    }
};
