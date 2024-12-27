#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class XorOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
public:
    XorOpcodeHandler(int cycles, AddressingMode *addressingMode, Register<uint8_t> CPU::*operationalRegister = &CPU::A)
        : OpcodeHandler(cycles, addressingMode), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto reg = *getOperationalRegister(cpu);

        auto result = reg.read() ^ cpu.bus.read(resolvedAddress->address);
        reg.write(result);

        cpu.P.setAll({
            {Status::Zero, Utils::isZero(result)},
            {Status::Negative, Utils::isNegative(result)},
        });

        return cycles + (resolvedAddress->crossedBoundary ? 1 : 0);
    }
};
