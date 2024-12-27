#pragma once
#include <memory>
#include "OpcodeHandler.hpp"
#include "cpu/CPU.cpp"
#include "cpu/opcode/WithOperationalRegister.cpp"
using namespace std;

class StoreRegisterOpcodeHandler : public OpcodeHandler, public WithOperationalRegister
{
public:
    StoreRegisterOpcodeHandler(int cycles, AddressingMode *addressingMode, Register<uint8_t> CPU::*operationalRegister)
        : OpcodeHandler(cycles, addressingMode), WithOperationalRegister(operationalRegister) {}

protected:
    int handle(CPU &cpu, unique_ptr<ResolvedAddress> &resolvedAddress) const override
    {
        auto reg = *getOperationalRegister(cpu);

        cpu.bus.write(resolvedAddress->address, reg.read());

        return cycles;
    }
};
