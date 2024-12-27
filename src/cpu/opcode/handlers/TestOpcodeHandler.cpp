#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
#include "Utils.cpp"
using namespace std;

class TestOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
public:
    TestOpcodeHandler(int cycles, AddressingMode *addressingMode, Register<uint8_t> CPU::*operationalRegister = &CPU::A)
        : OpcodeHandler(cycles, addressingMode), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto reg = *getOperationalRegister(cpu);

        auto value = cpu.bus.read(resolvedAddress->address);
        auto result = reg.read() & value;

        cpu.P.setAll({
            {Status::Zero, Utils::isZero(result)},
            {Status::Negative, Utils::isNegative(value)},
            {Status::Overflow, Utils::isOverflowBit(value)},
        });

        return cycles;
    }
};
