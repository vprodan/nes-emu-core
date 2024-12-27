#pragma once
#include <memory>
#include "cpu/opcode/addressing/AddressingMode.hpp"
using namespace std;

class ImmediateAddressingMode : public AddressingMode
{
public:
    unique_ptr<ResolvedAddress> resolve(CPU &cpu) const override
    {
        auto address = cpu.bus.read(cpu.PC.read());
        cpu.PC.increment();

        return make_unique<ResolvedAddress>(address);
    }
};